/*
* Copyright (C) 2006, 2007 Apple Inc.  All rights reserved.
* Copyright (C) 2008 Collabora Ltd. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
* PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "config.h"
#include "PluginView.h"
#include "PluginEvents.h"

#include "Document.h"
#include "DocumentLoader.h"
#include "Element.h"
#include "EventNames.h"
#include "FocusController.h"
#include "FrameLoader.h"
#include "FrameLoadRequest.h"
#include "FrameTree.h"
#include "Frame.h"
#include "FrameView.h"
#include "GraphicsContext.h"
#include "Image.h"
#include "HTMLNames.h"
#include "HTMLPlugInElement.h"
#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "NotImplemented.h"
#include "Page.h"
#include "PlatformKeyboardEvent.h"
#include "PlatformMouseEvent.h"
#include "PluginDebug.h"
#include "PluginPackage.h"
#include "RenderLayer.h"
#include "Settings.h"
#include "JSDOMBinding.h"
#include "ScriptController.h"
#include "npruntime_impl.h"
#include "PluginMainThreadScheduler.h"
//#include "runtime.h"
//#include "runtime_root.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <QPainter>
#include <QPaintDevice>
#include <QImage>
#include <QPixmap>
#include <QWidget>
#include <QScreen>
#include <QMouseEvent>
#include <QMutex>
#include <QTime>
#include <QUrl>

#include <runtime/JSLock.h>
#include <execinfo.h>
#include <sys/time.h>

#include "gdl.h"
#include "libgma.h"
#include "srb.h"
#include "x86_cache.h"

#define CHECK_GDL_RC(RC,MSG) \
    if(GDL_SUCCESS != (RC)) { \
        fprintf(stderr, "%s \tReturn: 0x%08x:%s %s()-%s:%d\n", (MSG), \
                (RC), gdl_get_error_string((RC)),__FUNCTION__,__FILE__,__LINE__); \
    } \

#define CHECK_GMA_RC(RC,MSG) \
    if(GMA_SUCCESS != (RC)) { \
        fprintf(stderr, "%s \tReturn: 0x%08x %s()-%s:%d\n", (MSG), \
                (RC), __FUNCTION__,__FILE__,__LINE__); \
    } \

#define CHECK_NULL(PTR,MSG) \
    if(NULL == (PTR)) { \
        fprintf(stderr, "%s \tNull pointer %s()-%s:%d\n", (MSG), \
                __FUNCTION__,__FILE__,__LINE__); \
    } \

#ifdef __cplusplus
extern "C" {
#endif
  extern bool GetBrowserOffsets(int* offsetX, int* offsetY);
  extern bool GetBrowserPluginFullscreen(void** pluginView);
  extern bool SetBrowserPluginFullscreen(void* pluginView, bool isFullScreen);
  extern bool GetBrowserSize(int* width, int* height);
#ifdef __cplusplus
} // extern C
#endif


//#define TRACE_INFO fprintf
#define TRACE_INFO(...)
#define TRACE_DEBUG(...)


using JSC::ExecState;
using JSC::Interpreter;
using JSC::JSObject;
using JSC::UString;

using std::min;

using namespace WTF;


namespace WebCore {

//---------------------------------- UTILITY FUNCTIONS -----------------------------------------
//

void
print_trace (void)
{
  void *array[10];
  size_t size;
  char **strings;
  size_t i;

  size = backtrace (array, 10);
  strings = backtrace_symbols (array, size);

  fprintf (stderr, "Obtained %zd stack frames.\n", size);

  for (i = 0; i < size; i++)
     fprintf (stderr, "%s\n", strings[i]);

  free (strings);
}

void displayMemory(char *address, int length) {
        int i = 0; //used to keep track of line lengths
        char *line = (char*)address; //used to print char version of data
        unsigned char ch; // also used to print char version of data
        fprintf(stderr, "%08X | ", (int)address); //Print the address we are pulling from
        while (length-- > 0) {
                fprintf(stderr, "%02X ", (unsigned char)*address++); //Print each char
                if (!(++i % 16) || (length == 0 && i % 16)) { //If we come to the end of a line...
                        //If this is the last line, print some fillers.
                        if (length == 0) { while (i++ % 16) { fprintf(stderr, "__ "); } }
                        fprintf(stderr, "| ");
                        while (line < address) {  // Print the character version
                                ch = *line++;
                                fprintf(stderr, "%c", (ch < 33 || ch == 255) ? 0x2E : ch);
                        }
                        // If we are not on the last line, prefix the next line with the address.
                        if (length > 0) { fprintf(stderr, "\n%08X | ", (int)address); }
                }
        }
        puts("");
}
//
//-------------------------------------------------------------------------------------

class BXSurface
{
public:
  BXSurface() : m_dirty(false), m_painter(NULL), m_lock(QMutex::Recursive) {}
  virtual ~BXSurface() { }
  QImage  m_image;
  bool    m_dirty;
  int     m_width;
  int     m_height;
  QPainter *m_painter;
  QMutex  m_lock;
};

static void* GLCreateSurface(int width, int height, int depth)
{
  BXSurface *s = new BXSurface;
  s->m_width  = width;
  s->m_height = height;
  return s;
}

static bool GLFreeSurface(void * pSurface)
{
  BXSurface *s = (BXSurface*) pSurface;
  delete s;
  return TRUE;
}

static bool GLLockSurface(void * pSurface)
{
  BXSurface* s= (BXSurface*)pSurface;
  s->m_lock.lock();
  return TRUE;
}

static bool GLUnlockSurface(void * pSurface)
{
  BXSurface* s= (BXSurface*)pSurface;
  s->m_dirty = true;
  s->m_lock.unlock();
  return TRUE;
}

static void* GLGetPixels(void * pSurface)
{
  BXSurface* s= (BXSurface*)pSurface;
  if (s->m_image.isNull())
      s->m_image = QImage(s->m_width, s->m_height, QImage::Format_ARGB32_Premultiplied);

  return s->m_image.bits();
}

static int GLGetPitch(void * pSurface)
{
  BXSurface* s= (BXSurface*)pSurface;
  if (s->m_image.isNull())
      s->m_image = QImage(s->m_width, s->m_height, QImage::Format_ARGB32_Premultiplied);

  return s->m_image.bytesPerLine();
}

static bool GLDrawRect(void * pSurface, uint32_t color, const PluginRect* rect)
{
  fprintf(stderr, "drawing rect %d*%d %d*%d color %x\n",
          rect->left, rect->top, rect->right - rect->left, rect->bottom - rect->top, color);

  BXSurface* s= (BXSurface*)pSurface;
  if (s->m_image.isNull())
      s->m_image = QImage(s->m_width, s->m_height, QImage::Format_ARGB32_Premultiplied);
  QPainter p(&(s->m_image));
  p.fillRect(rect->left, rect->top, rect->right - rect->left, rect->bottom - rect->top, QColor(color));
  return TRUE;
}

static bool GLBlit(void * pSurface, void* pTargetSurface, const int nTargetPitch, const PluginRect* src_rect,
                   const PluginRect* dest_rect, bool bSourceAlpha)
{
//  fprintf(stderr, "glblit %x %x %d %d*%d %d*%d %d*%d %d*%d %d\n",
//          pSurface, pTargetSurface, nTargetPitch,
//          src_rect->left, src_rect->top, src_rect->right, src_rect->bottom,
//          dest_rect->left, dest_rect->top, dest_rect->right, dest_rect->bottom,
//          bSourceAlpha);

  QRectF srcRect(QPoint(src_rect->left, src_rect->top), QPoint(src_rect->right, src_rect->bottom));
  QRectF destRect(QPoint(dest_rect->left, dest_rect->top), QPoint(dest_rect->right, dest_rect->bottom));

  BXSurface* srcSurface = (BXSurface*)pSurface;
  BXSurface* destSurface= (BXSurface*)pTargetSurface;
  if (destSurface->m_dirty) // this is just in case - the target surface is never dirty.
    fprintf(stderr, "destSurface->m_dirty\n");

  if (destSurface->m_painter)
  {
    QPainter::CompositionMode mode = destSurface->m_painter->compositionMode();
    if (!bSourceAlpha)
      destSurface->m_painter->setCompositionMode(QPainter::CompositionMode_Source);
//#define TIME_DRAW
#ifdef TIME_DRAW
    QTime t;
    t.start();
#endif
    if ( destRect.size() != srcRect.size() )
    {
      // we have to disable SmoothPixmapTransform cause its killing the machine on upscale
      destSurface->m_painter->setRenderHint(QPainter::SmoothPixmapTransform, false);
    }
    if (!srcSurface->m_image.isNull())
    {
      destSurface->m_painter->drawImage(destRect, srcSurface->m_image, srcRect, 0);
    }
#ifdef TIME_DRAW
    fprintf(stderr,"-------(%p,%p) took %d ms to draw %dx%d . destrect: %d,%d %dx%d. source: %d,%d %dx%d\n",
            srcSurface->m_pixmap,
            destSurface->m_pixmap,
            t.elapsed(),srcSurface->m_image.width(),srcSurface->m_image.height(),
            dest_rect->left, dest_rect->top, dest_rect->right - dest_rect->left, dest_rect->bottom - dest_rect->top, src_rect->left, src_rect->top,
            src_rect->right - src_rect->left, src_rect->bottom - src_rect->top);
#endif
    destSurface->m_painter->setCompositionMode(mode);
  }
  else
    fprintf(stderr, "destSurface->m_painter is null\n");


  return TRUE;
}

bool GLGetFuncs(GL_FuncTable **table)
{

  static GL_FuncTable drawingFuncs = { 0, 0, 0, 0, 0, 0, 0, 0 };

  if(!drawingFuncs.pfCreateSurface)
  {
    bool bUseAcceleratedPluginBlit = TRUE;

    // Get the blit acceleration status from environment variable
    String strUseBlitAccel(getenv("PLUGIN_USE_ACCEL_BLIT"));
    if(strUseBlitAccel.contains("false"))
    {
      bUseAcceleratedPluginBlit = FALSE;
    }

    if(bUseAcceleratedPluginBlit == TRUE) {
      drawingFuncs.pfCreateSurface = GLCreateSurface;
      drawingFuncs.pfFreeSurface  = GLFreeSurface;
      drawingFuncs.pfLockSurface  = GLLockSurface;
      drawingFuncs.pfUnlockSurface = GLUnlockSurface;
      drawingFuncs.pfGetPixels  = GLGetPixels;
      drawingFuncs.pfGetPitch   = GLGetPitch;
      drawingFuncs.pfDrawRect   = GLDrawRect;
      drawingFuncs.pfBlit    = GLBlit;
    }
  }

  if(drawingFuncs.pfCreateSurface == NULL) {
    *table = NULL;
    return FALSE;
  }

  *table = &drawingFuncs;
  return TRUE;
}

void PluginView::updatePluginWidget()
{
    // Sync state with the containing frame view
    if (!parent() || !m_isWindowed)
        return;

    ASSERT(parent()->isFrameView());
    FrameView* frameView = static_cast<FrameView*>(parent());

    IntRect oldWindowRect = m_windowRect;
    IntRect oldClipRect = m_clipRect;

    m_windowRect = IntRect(frameView->contentsToWindow(frameRect().location()), frameRect().size());
    m_clipRect = windowClipRect();
    m_clipRect.move(-m_windowRect.x(), -m_windowRect.y());
}

void PluginView::setFocus()
{
    // Nothing to do here for our platform
    Widget::setFocus();
}

void PluginView::show()
{
    LOG(Plugins, "PluginView::show\n");
    setSelfVisible(true);

    Widget::show();
}

void PluginView::hide()
{
    LOG(Plugins, "PluginView::hide\n");
    setSelfVisible(false);

    Widget::hide();
}

static     QMutex  l;

//#define TIME_PAINT
void PluginView::paint(GraphicsContext* context, const IntRect& rect)
{
  LOG(Plugins, "PluginView::paint %d, %d, %d, %d\n", rect.x(), rect.y(), rect.width(), rect.height());

    if (!m_isStarted || m_status !=  PluginStatusLoadedSuccessfully) {
        // Draw the "missing plugin" image
        paintMissingPluginIcon(context, rect);
        return;
    }

#ifdef TIME_PAINT
    QTime t;
    t.start();
#endif

    IntRect scrollOffset(0,0,0,0);

    PluginEvent event;
    //PluginView * pluginView = NULL;
    memset(&event, 0, sizeof(PluginEvent));

    // From BoxeeBrowser::requestRepaint, we know that the
    // paint device is in fact a QPixmap.
    QPainter* painter = context->platformContext();
    if (!painter)
      return;

    QPaintDevice* image = static_cast<QPaintDevice*>(painter->device());

    const QTransform &keepTransform = painter->transform();

    BXSurface *destSurface = NULL;

    event.paint.depth   = 4;
    event.paint.pitch   = event.paint.w * event.paint.depth;

    QWidget *widget = NULL;

    // Are we using accelerated GL functions hosted by the browser?
    GL_FuncTable *table = NULL;
    GLGetFuncs(&table);     // Set the passed in surface/memory based on the result.
    if(table != NULL)
    {
      QImage* image = static_cast<QImage*>(painter->device());
        // Using internal GL functions
        //LOG(Plugins, "PluginView::paint() using internal GL functions");
      event.paint.bUseAccelBlit = true;
      destSurface = (BXSurface*)GLCreateSurface(image->width(), image->height(), 32);
      destSurface->m_painter = painter;
      event.paint.pixels = (uint8_t*)destSurface;
      event.paint.w = image->width()  ;
      event.paint.h = image->height()  ;
      event.paint.pitch   = image->bytesPerLine();
    }
    else
    {
        // Passing in a memory bitmap
        //LOG(Plugins, "PluginView::paint() using memory bitmap");

        QImage* image = static_cast<QImage*>(painter->device());
        if (!image->bits())
          return;
        event.paint.bUseAccelBlit = false;
        event.paint.pixels = (uint8_t*)(image->bits());
        event.paint.pitch   = image->bytesPerLine();
        event.paint.w    = image->width();
        event.paint.h    = image->height();
    }


    for (WebCore::ScrollView* p = parent(); p; p = p->parent())
    {
        int x = scrollOffset.x();
        int y = scrollOffset.y();
        scrollOffset.setX(x + p->x() - p->scrollX());
        scrollOffset.setY(y + p->y() - p->scrollY());
    }

    LOG(Plugins, "PluginView::paint scroll offset x -> %d, y -> %d\n", scrollOffset.x(), scrollOffset.y());

    bool xxxxxx = false;
    PluginView * pluginView = NULL;
    IntRect invalRect(0,0,0,0);
    event.type = PluginPaintEventType;
    if (GetBrowserPluginFullscreen((void**)&pluginView) == true && pluginView != NULL)
    {
      if(pluginView == this)
      {
        painter->resetTransform();
        //painter->scale((double)image->width() / (double)frameRect().width(), (double)image->height() / (double)frameRect().height() );

        for (unsigned i = 0; i < m_invalidRects.size(); i++)
        {
          // coalesce the existing rectangles
          invalRect.unite(m_invalidRects[i]);
        }

        m_fullScreenInvalidRect = invalRect;

        FloatRect fRect((float)invalRect.x(), (float)invalRect.y(), (float)invalRect.width(), (float)invalRect.height());
        context->clearRect(fRect);

        event.paint.inval.left 		= invalRect.x();
        event.paint.inval.top 		= invalRect.y();
        event.paint.inval.right 	= invalRect.x() + invalRect.width();
        event.paint.inval.bottom 	= invalRect.y() + invalRect.height();

        m_invalidRects.clear();
        event.paint.xoffset   = 0;
        event.paint.yoffset   = 0;

        if (painter && m_shouldClearFullscreen)
        {
            painter->fillRect(0, 0, image->width(), image->height(), QColor(0,0,0,0));
#ifdef USE_PIXMAP
            if (!widget)
              ((QPixmap*)image)->fill(QColor(0,0,0,0));
#endif

            m_shouldClearFullscreen = false;
            m_fullScreenInvalidRect = IntRect(0, 0, image->width(),  image->height());
        }
      }
    }
    else
    {
      IntRect rectWidget = frameRect();
      event.paint.inval.left    = rect.x();
      event.paint.inval.top     = rect.y();
      event.paint.inval.right   = event.paint.inval.left + rect.width();
      event.paint.inval.bottom  = event.paint.inval.top + rect.height();
      event.paint.xoffset     = rectWidget.x();
      event.paint.yoffset     = rectWidget.y();
      setNPWindowRect(rectWidget);
      event.paint.w    = rect.width()  ;
      event.paint.h    = rect.height() ;
    }

    NPEvent pEvt    = &event; // NPEvent is typedef'd as void*

    // Finally call into the plugin
    PluginView::setCurrentPluginView(this);
    JSC::JSLock::DropAllLocks dropAllLocks(JSC::SilenceAssertionsOnly);
    setCallingPlugin(true);
    //fprintf(stderr,"----- paint: %d %d %d %d / %d %d %d %d\n",event.paint.xoffset, event.paint.yoffset, event.paint.w,event.paint.h,  event.paint.inval.left, event.paint.inval.top, event.paint.inval.right, event.paint.inval.bottom);


    m_plugin->pluginFuncs()->event(m_instance, pEvt);
    setCallingPlugin(false);
    PluginView::setCurrentPluginView(0);

    if (destSurface)
      GLFreeSurface(destSurface);

    painter->setTransform(keepTransform);

#ifdef TIME_PAINT
    fprintf(stderr,"****** paint (%dx%d) took %d ms\n",rect.width(), rect.height(), t.elapsed());
#endif

}

//
// this function causes the plugin (only flash) to toggle its fullscreen state.
// it is important to also set the plugin's window to the right size by calling "setNPWindow"
//
void PluginView::sendFullscreenEventToPlugin()
{
  TRACE_INFO(stderr, "m_isFakeFullscreen %d m_actualFullscreen %d m_isFullscreen %d \n", m_isFakeFullscreen, m_actualFullscreen, m_isFullscreen);
  PluginEvent evt;
  memset(&evt, 0, sizeof(PluginEvent));
  evt.type = PluginPaintEventType + 1; // hack. we dont have the constant yet...
  NPEvent pEvt = &evt;

  LOG(Plugins, "Sending Fullscreen Event\n");
  //TRACE_INFO(stderr, "before Sending Fullscreen Event\n");
  setCallingPlugin(true);
  m_sentWindowEvent = true;
  m_plugin->pluginFuncs()->event(m_instance, pEvt);
  m_sentWindowEvent = false;
  setCallingPlugin(false);
  //TRACE_INFO(stderr, "after Sending Fullscreen Event\n");

  m_actualFullscreen = m_isFullscreen;
}

void PluginView::handleKeyboardEvent(KeyboardEvent* event)
{
    if (m_isWindowed)
        return;

    String key = event->keyEvent()->keyIdentifier();
    if (key == "F1" || key == "F2" || key == "F3" || key == "F4" ||
        key == "F5" || key == "F6" || key == "F7" || key == "F8" ||
        key == "F9" || key == "F10" || key == "F11" || key == "F12") {
        return;
    }

    PluginEvent evt;
    memset(&evt, 0, sizeof(PluginEvent));
    evt.type = PluginKeyEventType;

    switch (event->keyEvent()->type()) {
    case PlatformKeyboardEvent::RawKeyDown:
        evt.key.state = PluginKeyDown;
        break;
    case PlatformKeyboardEvent::KeyUp:
        evt.key.state = PluginKeyUp;
        break;
    default:
        return;
    }


    QKeyEvent* qtKeyEvent = event->keyEvent()->qtEvent();
    TRACE_INFO(stderr, "qt key event unicode %d char code %d key code %d window vk %d native vk %d\n", qtKeyEvent->text().unicode()[0].unicode(),
               event->charCode(), event->keyCode(), event->keyEvent()->windowsVirtualKeyCode(), event->keyEvent()->nativeVirtualKeyCode());

    evt.key.unicode = qtKeyEvent->text().unicode()[0].unicode();
    if (event->keyEvent()->nativeVirtualKeyCode())
        evt.key.sym = event->keyEvent()->nativeVirtualKeyCode();
    else if (event->keyEvent()->windowsVirtualKeyCode())
      evt.key.sym = event->keyEvent()->windowsVirtualKeyCode();

    TRACE_INFO(stderr, "plugin keyboard event state %d sym %d unicode %d\n",
            (int)evt.key.state,
            (int)evt.key.sym,
            (int)evt.key.unicode);

    NPEvent pEvt  = &evt;

    LOG(Plugins, "Sending Keyboard Event\n");
    PluginView::setCurrentPluginView(this);
    JSC::JSLock::DropAllLocks dropAllLocks(JSC::SilenceAssertionsOnly);
    setCallingPlugin(true);
    bool ret = m_plugin->pluginFuncs()->event(m_instance, pEvt);
    setCallingPlugin(false);
    PluginView::setCurrentPluginView(0);
    if (ret)
        event->setDefaultHandled();
}

void PluginView::handleMouseEvent(MouseEvent* event)
{
    PluginEvent evt;
    memset(&evt, 0, sizeof(PluginEvent));
    evt.type = PluginMouseEventType;

    int state = PluginMouseButtonMove;
    if(event->type() == eventNames().mouseoverEvent) {
        state = PluginMouseButtonMove;
    }
    else if(event->type() == eventNames().mousedownEvent) {
        state = PluginMouseButtonDown;
        if (Page* page = m_parentFrame->page())
            page->focusController()->setFocusedFrame(m_parentFrame);
        m_parentFrame->document()->setFocusedNode(m_element);
    }
    else if(event->type() == eventNames().mouseupEvent) {
        state = PluginMouseButtonUp;
    }

    evt.mouse.state  = state;
    evt.mouse.xrel  = 0;
    evt.mouse.yrel  = 0;
    evt.mouse.which  = 0; // Device index
    evt.mouse.button = event->button();

    IntRect scrollOffset(0,0,0,0);
    IntPoint p(0,0);

    //
    // Don't modify the mouse position if we're full-screen.
    //
    p = static_cast<FrameView*>(parent())->contentsToWindow(IntPoint(event->pageX(), event->pageY()));
    for (WebCore::ScrollView* pt = parent();
    pt; pt = pt->parent()) {
        int x = scrollOffset.x();
        int y = scrollOffset.y();
        scrollOffset.setX(x + pt->x() - pt->scrollX());
        scrollOffset.setY(y + pt->y() - pt->scrollY());
    }

    float zoomFactor = (event->view() && event->view()->frame()) ? event->view()->frame()->pageZoomFactor() : 1.0f;
    evt.mouse.x   = p.x() * zoomFactor - frameRect().x() - scrollOffset.x() * zoomFactor;
    evt.mouse.y   = p.y() * zoomFactor - frameRect().y() - scrollOffset.y() * zoomFactor;

    NPEvent pEvt  = &evt;

    //    LOG(Plugins, "Sending Mouse Event state = %d, x,y = %d, %d\n", evt.mouse.state, evt.mouse.x, evt.mouse.y);
    PluginView::setCurrentPluginView(this);
    JSC::JSLock::DropAllLocks dropAllLocks(JSC::SilenceAssertionsOnly);
    setCallingPlugin(true);
    bool ret = m_plugin->pluginFuncs()->event(m_instance, pEvt);
    setCallingPlugin(false);
    PluginView::setCurrentPluginView(0);
    if (ret)
        event->setDefaultHandled();
}

void PluginView::setParent(ScrollView* parent)
{
    Widget::setParent(parent);

    if (parent)
        init();
}

void PluginView::init()
{
    if (m_haveInitialized)
        return;

    m_haveInitialized = true;

    if (!m_plugin) {
        ASSERT(m_status == PluginStatusCanNotFindPlugin);
        return;
    }

    LOG(Plugins, "PluginView::init(): Initializing plug-in '%s'", m_plugin->name().utf8().data());
    fprintf(stderr, "PluginView::init(): Initializing plug-in '%s'\n", m_plugin->name().utf8().data());

    if (!m_plugin->load()) {
        m_plugin = 0;
        m_status = PluginStatusCanNotLoadPlugin;
        return;
    }

    if (!startOrAddToUnstartedList()) {
        m_status = PluginStatusCanNotLoadPlugin;
        return;
    }

    m_status = PluginStatusLoadedSuccessfully;
}

bool PluginView::start()
{
    LOG(Plugins, "PluginView::start()");
    if (m_isStarted)
        return false;

    m_isWaitingToStart = false;

    PluginMainThreadScheduler::scheduler().registerPlugin(m_instance);

    ASSERT(m_plugin);
    ASSERT(m_plugin->pluginFuncs()->newp);

    NPError npErr;
    {
        PluginView::setCurrentPluginView(this);
        JSC::JSLock::DropAllLocks dropAllLocks(JSC::SilenceAssertionsOnly);
        setCallingPlugin(true);
        npErr = m_plugin->pluginFuncs()->newp((NPMIMEType)m_mimeType.utf8().data(), m_instance, m_mode, m_paramCount, m_paramNames, m_paramValues, NULL);
        setCallingPlugin(false);
        LOG_NPERROR(npErr);
        PluginView::setCurrentPluginView(0);
    }

    if (npErr != NPERR_NO_ERROR) {
        m_status = PluginStatusCanNotLoadPlugin;
        PluginMainThreadScheduler::scheduler().unregisterPlugin(m_instance);
        return false;
    }

    // Set the Browser GL Drawing Funcs
    // this has to be done after the plugin is initialized but before its window has been set
    if (m_plugin->pluginFuncs()->setvalue) {
        GL_FuncTable *table = 0;
        GLGetFuncs(&table);
        if(table) {
            setCallingPlugin(true);
            m_plugin->pluginFuncs()->setvalue(m_instance, (NPNVariable)NPPVpluginDrawingFunctions, table);
            setCallingPlugin(false);
        }
    }

    m_isStarted = true;

    if (!m_url.isEmpty() && !m_loadManually) {
        FrameLoadRequest frameLoadRequest;
        frameLoadRequest.resourceRequest().setHTTPMethod("GET");
        frameLoadRequest.resourceRequest().setURL(m_url);
        QUrl url(m_url.string());
        frameLoadRequest.resourceRequest().setHTTPHeaderField("Referer", QString(url.scheme() + "://" + url.host()).toUtf8().data());
        load(frameLoadRequest, false, 0);
    }

    m_status = PluginStatusLoadedSuccessfully;

    if (!platformStart())
        m_status = PluginStatusCanNotLoadPlugin;

    if (m_status != PluginStatusLoadedSuccessfully)
        return false;

    if (parentFrame()->page())
        parentFrame()->page()->didStartPlugin(this);

    return true;
}

void PluginView::setNPWindowRect(const IntRect& rect)
{
    //LOG(Plugins, "PluginView::setNPWindowRect(%d, %d, %d, %d)", rect.x(), rect.y(), rect.width(), rect.height());
    //TRACE_INFO(stderr, "\nPluginView::setNPWindowRect(%d, %d, %d, %d)\n", rect.x(), rect.y(), rect.width(), rect.height());
    if (!m_isStarted || !parent()) {
        LOG(Plugins, "PluginView::setNPWindowRect() RETURNING WITHOUT DOING NOTHING");
        return;
    }

    int offsetX = 0;
    int offsetY = 0;
    ::GetBrowserOffsets(&offsetX, &offsetY);

    IntPoint p(0,0);

    if (!m_isFullscreen) 
    {
      //TRACE_INFO(stderr, " %s %d - not in full screen, translating rect location to content\n", __FUNCTION__, __LINE__);
      p = static_cast<FrameView*>(parent())->contentsToWindow(rect.location());
    }

    if(m_npWindow.x == (p.x() + offsetX) &&
       m_npWindow.y == (p.y() + offsetY) &&
       m_npWindow.width == rect.width() &&
       m_npWindow.height == rect.height()) {
        // This is the same data as already exists
        return;
    }

    m_npWindow.x = p.x();
    m_npWindow.y = p.y();
    m_npWindow.x += offsetX;
    m_npWindow.y += offsetY;

    m_npWindow.width = rect.width();
    m_npWindow.height = rect.height();

    m_npWindow.clipRect.left = 0;
    m_npWindow.clipRect.top = 0;
    m_npWindow.clipRect.right = rect.width();
    m_npWindow.clipRect.bottom =  rect.height();

    if (m_npWindow.width <= 0 || m_npWindow.height <= 0)
        return;

    if (m_plugin->pluginFuncs()->setwindow) 
    {
      TRACE_DEBUG(stderr, "%s %d - plugin has a window size callback\n", __FUNCTION__, __LINE__);
      PluginView::setCurrentPluginView(this);
      JSC::JSLock::DropAllLocks dropAllLocks(JSC::SilenceAssertionsOnly);
      //fprintf(stderr,"$$$$$$$$$$$ calling setwindow. %d %d %d %d / %d %d %d %d\n",  m_npWindow.x,  m_npWindow.y,  m_npWindow.width,  m_npWindow.height, m_npWindow.clipRect.left, m_npWindow.clipRect.top, m_npWindow.clipRect.right, m_npWindow.clipRect.bottom);
      setCallingPlugin(true);
      m_plugin->pluginFuncs()->setwindow(m_instance, &m_npWindow);
      setCallingPlugin(false);
      PluginView::setCurrentPluginView(0);
    }
}

void PluginView::invalidateRegion(NPRegion)
{
    notImplemented();
}

NPError PluginView::handlePostReadFile(Vector<char>& buffer, uint32 len, const char* buf)
{
    return NPERR_NO_ERROR;
}

// Used before the plugin view has been initialized properly, and as a
// fallback for variables that do not require a view to resolve.
bool PluginView::platformGetValueStatic(NPNVariable variable, void* value, NPError* out)
{
    LOG(Plugins, "PluginView::platformGetValueStatic(%s)", prettyNameForNPNVariable(variable).data());

    switch (variable) {
    case NPNVToolkit:
        *static_cast<uint32*>(value) = 0;
        *out = NPERR_NO_ERROR;
        return true;

    case NPNVjavascriptEnabledBool:
        *static_cast<NPBool*>(value) = true;
        *out = NPERR_NO_ERROR;
        return true;


    default:
        *out = NPERR_GENERIC_ERROR;
        return false;
    }
}

bool PluginView::platformGetValue(NPNVariable variable, void* value, NPError* out)
{
    return false;
}

void PluginView::invalidateRect(const IntRect& r)
{
//    LOG(Plugins, "PluginView::invalidateRect(const IntRect&) %d, %d, %d, %d\n", r.x(), r.y(), r.width(), r.height());
    ASSERT(!m_isWindowed); // We're not gonna be windowed in this port

    // Windowless plugin
    // No need to send an event this is generated by the invalidateWindowlessPluginRect call
    invalidateWindowlessPluginRect(r);

    // If the plugin is in FS mode then save the invalidate rectangle
    PluginView * pluginView = 0;
    if(::GetBrowserPluginFullscreen((void**)&pluginView) == true && pluginView) {
        if(pluginView == this) {
            // This is the plugin that is currently in FS
            m_invalidRects.append(r);
        }
    }
}

void PluginView::invalidateRect(NPRect* rect)
{
    if (!rect) {
//        LOG(Plugins, "PluginView::invalidateRect(NPRect*) NULL\n");
        invalidate();
        return;
    }
//    LOG(Plugins, "PluginView::invalidateRect(NPRect*) %d, %d, %d, %d\n", rect->left, rect->top, rect->right - rect->left, rect->bottom - rect->top);
    IntRect r(rect->left, rect->top, rect->right - rect->left, rect->bottom - rect->top);
    invalidateRect(r);
}

void PluginView::forceRedraw()
{
    LOG(Plugins, "PluginView::forceRedraw()");
}

bool PluginView::platformStart()
{
    LOG(Plugins, "PluginView::platformStart()");
    ASSERT(m_isStarted);
    ASSERT(m_status == PluginStatusLoadedSuccessfully);

    LOG(Plugins, "PluginView::platformStart() 1");
    if (m_plugin->pluginFuncs()->getvalue) {
        /*PluginView::setCurrentPluginView(this);
    setCallingPlugin(true);
    m_plugin->pluginFuncs()->getvalue(m_instance, NPPVpluginNeedsXEmbed, &m_needsXEmbed);
    setCallingPlugin(false);
    PluginView::setCurrentPluginView(0);*/
    }

    if (m_isWindowed)
        m_npWindow.type = NPWindowTypeWindow;
    else {
        m_npWindow.type = NPWindowTypeDrawable;
        m_npWindow.window = 0;
    }

    LOG(Plugins, "PluginView::platformStart() 2");

    //if (!(m_plugin->quirks().contains(PluginQuirkDeferFirstSetWindowCall)))
    setNPWindowRect(frameRect());

    setPlatformPluginWidget(0/*m_parentFrame->view()->hostWindow()->platformWindow()*/);

    show();

    return true;
}

void PluginView::platformDestroy()
{
}

void PluginView::setParentVisible(bool visible)
{
    if (isParentVisible() == visible)
        return;

    Widget::setParentVisible(visible);
}

NPError PluginView::platformSetValue(NPPVariable variable, void* value)
{
    // this method will be called both if user clicked the fullscreen and if full screen was activated manually.
    // if its a manual (by boxee browser) activation - we do not want/need to do anything.
    if (!m_fullscreenByPlugin) 
    {
      m_fullscreenByPlugin = true;
      return NPERR_NO_ERROR;
    }

    NPRect* rect = (NPRect*)value;
    int width, height;
    LOG(Plugins, "PluginView::setValue received NPPVpluginWindowSize event size(l,t,r,b) = %d, %d, %d, %d", rect->left, rect->top, rect->right, rect->bottom);
    TRACE_INFO(stderr, "%s %d - window size event [(l,t,r,b) = %d, %d, %d, %d] is full screen by plugin - %d\n", __FUNCTION__, __LINE__, rect->left, rect->top, rect->right, rect->bottom, m_fullscreenByPlugin);
    TRACE_INFO(stderr, "%s %d - window size event m_fullscreenByPlugin = %d, m_sentWindowEvent = %d\n", __FUNCTION__, __LINE__, m_fullscreenByPlugin, m_sentWindowEvent);

    // Is this the full screen?
    ::GetBrowserSize(&width, &height);

    if (width <= (rect->right - rect->left + 1) && height <= (rect->bottom - rect->top + 1) ) 
    {
      LOG(Plugins, "PluginView::setValue set FULLSCREEN mode to ON\n");
      showFullscreen(!m_isFullscreen, false, true);
    } 
    else 
    {
      LOG(Plugins, "PluginView::setValue set FULLSCREEN mode to OFF");
      showFullscreen(false, false, true);

      IntRect r(0, 0, width, height);
      ScrollView* rootView = root();
      if (rootView)
        rootView->invalidateRect(r);
    }

    return NPERR_NO_ERROR;
}

void PluginView::halt()
{
}

void PluginView::restart()
{
}

//
// this function is called either directly by the boxee browser, or by "platformSetValue" - if the user went and clicked the fullscreen button by himself.
//
void PluginView::showFullscreen(bool isFullscreen, bool fakeFullscreen, bool fullscreenByPlugin /* who called. if "true" - its the plugin. if "false" - its boxee browser*/ )
{
  TRACE_INFO(stderr, "%s %d - isFullscreen = %d, fakeFullScreen = %d, fullscreenByPlugin = %d\n", __FUNCTION__, __LINE__, isFullscreen, fakeFullscreen, fullscreenByPlugin);

  if (m_isFullscreen && m_isFakeFullscreen != fakeFullscreen)
  {
    // if fullscreen is not fake, we can't change the state as if it's fake
    fakeFullscreen = m_isFakeFullscreen;
    TRACE_INFO(stderr, "%s %d - setting isFakeFullscreen to current value %d\n", __FUNCTION__, __LINE__, m_isFakeFullscreen);
  }

  // we need some protective coding here because boxee browser sometimes ends up calling this method again
  bool bWindowChanged = (isFullscreen != m_isFullscreen);
  bool bNeedManualSet = (bWindowChanged && !fullscreenByPlugin && !fakeFullscreen); // boxee browser called and state needs to be changed manually

  // keep the state
  m_isFakeFullscreen = fakeFullscreen;
  m_isFullscreen = isFullscreen;
  m_shouldClearFullscreen = !fakeFullscreen;
  m_fullscreenByPlugin = fullscreenByPlugin;

  if (bNeedManualSet)
    sendFullscreenEventToPlugin();

  if (bWindowChanged)
  {
    ::SetBrowserPluginFullscreen(this, isFullscreen); // call back to boxee to sync the state. this will sometimes lead to calling this function again
    if (!isFullscreen)
    {
      setNPWindowRect(frameRect());
    }
    else
    {
      int width, height;
      ::GetBrowserSize(&width, &height);
      IntRect r(0,0,width,height);
      setNPWindowRect(r);
    }
  }
}
 
void PluginView::handleEvent(QEvent* event)
{
  switch (event->type())
  {
    case QEvent::MouseButtonDblClick:
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove:
    {
      QMouseEvent *mevent =  static_cast<QMouseEvent*>(event);
      PluginEvent evt;
      memset(&evt, 0, sizeof(PluginEvent));
      evt.type = PluginMouseEventType;
 
      int state;
      if (mevent->type() == QMouseEvent::MouseButtonPress)
        state = PluginMouseButtonDown;
      else if (mevent->type() == QMouseEvent::MouseButtonRelease)
        state = PluginMouseButtonUp;
      else
        state = PluginMouseButtonMove;

      evt.mouse.state  = state;
      evt.mouse.xrel  = 0;
      evt.mouse.yrel  = 0;
      evt.mouse.which  = 0; // Device index
      evt.mouse.button = 0; // need to translate from QT::MouseButton to PluginMouseButton
      evt.mouse.x   = mevent->x();
      evt.mouse.y   = mevent->y();

      NPEvent pEvt  = &evt;

      //    LOG(Plugins, "Sending Mouse Event state = %d, x,y = %d, %d\n", evt.mouse.state, evt.mouse.x, evt.mouse.y);
      PluginView::setCurrentPluginView(this);
      JSC::JSLock::DropAllLocks dropAllLocks(JSC::SilenceAssertionsOnly);
      setCallingPlugin(true);
      m_plugin->pluginFuncs()->event(m_instance, pEvt);
      setCallingPlugin(false);
      PluginView::setCurrentPluginView(0);
    }
    break;

  case QEvent::KeyPress:
  case QEvent::KeyRelease:
    {

      QKeyEvent *kevent =  static_cast<QKeyEvent*>(event);


      PluginEvent evt;
      memset(&evt, 0, sizeof(PluginEvent));
      evt.type = PluginKeyEventType;

      switch (kevent->type()) {
      case QEvent::KeyPress:
        evt.key.state = PluginKeyDown;
        break;
      case QEvent::KeyRelease:
        evt.key.state = PluginKeyUp;
        break;
      default:
        return;
      }
      TRACE_INFO(stderr, "kevent->key() %d native vk %d unicode %d\n", kevent->key(), kevent->nativeVirtualKey(), kevent->text().unicode()[0].unicode());

      evt.key.mod   = kevent->modifiers();// event->keyEvent()->modifiers();

      if (!kevent->key() || kevent->key() == kevent->text().unicode()[0].unicode())
      {
        evt.key.sym = kevent->text().unicode()[0].unicode(); evt.key.unicode = kevent->text().unicode()[0].unicode();
      }
      else if (kevent->text().unicode()[0].unicode() == 0)
      {
        evt.key.unicode = kevent->key();
      }
      else
      {
        evt.key.unicode = kevent->text().unicode()[0].unicode();
      }

      if (kevent->nativeVirtualKey())
          evt.key.sym = kevent->nativeVirtualKey();

      TRACE_INFO(stderr, "handle event - keyboard event state %d sym %d unicode %d\n", (int)evt.key.state, (int)evt.key.sym, (int)evt.key.unicode);

      NPEvent pEvt  = &evt;

      LOG(Plugins, "Sending Keyboard Event\n");
      PluginView::setCurrentPluginView(this);
      JSC::JSLock::DropAllLocks dropAllLocks(JSC::SilenceAssertionsOnly);
      setCallingPlugin(true);
      m_plugin->pluginFuncs()->event(m_instance, pEvt);
      setCallingPlugin(false);
      PluginView::setCurrentPluginView(0);
    }
    break;

  default:
      break;
  }
}

} // namespace WebCore
