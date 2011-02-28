#include <stdio.h>

#include "intelcescreen.h"
#include "intelcesurface.h"
#include "intelcecursor.h"
#include <QVector>
#include <QVarLengthArray>
#include <QApplication>
#include <QColor>
#include <QWidget>
#include <libgdl.h>
#include <EGL/egl.h>

#define MOUSE_CURSOR_ARG "-mousecursor"

class IntelCEScreenSurfaceFunctions : public QGLScreenSurfaceFunctions
{
public:
   IntelCEScreenSurfaceFunctions( IntelCEScreen *s, int screenNum );
   virtual ~IntelCEScreenSurfaceFunctions(){}
   bool createNativeWindow(QWidget *widget, EGLNativeWindowType *native);
private:
   IntelCEScreen *screen;
   int displayId;
};

IntelCEScreenSurfaceFunctions::IntelCEScreenSurfaceFunctions( IntelCEScreen *s, int screenNum )
    : screen(s), displayId(screenNum) 
{
}

bool IntelCEScreenSurfaceFunctions::createNativeWindow(QWidget *widget, EGLNativeWindowType *native)
{
    qDebug("hssf::createNativeWindow: enter: widget=%p native=%p\n", widget, native);
    QWSWindowSurface *surface = static_cast<QWSWindowSurface *>(widget->windowSurface());
    if (!surface) {
        qDebug("hssf::createNativeWindow: no surface yet\n");
        // The widget does not have a surface yet, so give it one.
        surface = new IntelCESurface(widget);
        qDebug("hssf::createNativeWindow: new surface %p\n", surface);
        widget->setWindowSurface(surface);
    } else if (surface->key() != QLatin1String("intelce")) {
        qDebug("hssf::createNativeWindow: replace surface\n");
        // The application has attached a QGLContext to an ordinary QWidget.
        // Replace the widget's window surface with a new one that can do GL.
        QRect geometry = widget->frameGeometry();
        geometry.moveTo(widget->mapToGlobal(QPoint(0, 0)));
        surface = new IntelCESurface(widget);
        qDebug("hssf::createNativeWindow: new surface %p\n", surface);
        surface->setGeometry(geometry);
        widget->setWindowSurface(surface);
        widget->setAttribute(Qt::WA_NoSystemBackground, true);
    } else {
        qDebug("hssf::createNativeWindow: key %s\n", surface->key().toAscii().constData());
    }
    qDebug("hssf::createNativeWindow: surface %p\n", surface);
    //IntelCESurface *nsurface = static_cast<IntelCESurface*>(surface);
    *native= (EGLNativeWindowType)screen->nativeWindow;
    qDebug("hssf::createNativeWindow: *native=%p\n", *native);
    return true;
}

IntelCEScreen::IntelCEScreen(int displayId)
    : QGLScreen(displayId), windowSize(1280,720), windowUpscale(1.0f, 1.0f), hrmConsumerInterface(0)
{
   const char *env= getenv("QT_NATIVE_WINDOW");
   if ( env == 0 )
   {
      env= "C";
   }
   if ( strcmp(env, "A") == 0 )
   {
      qDebug("intelce using plane A\n");
      nativeWindow= GDL_PLANE_ID_UPP_A;
   }
   else if ( strcmp(env, "B") == 0 )
   {
      qDebug("intelce using plane B\n");
      nativeWindow= GDL_PLANE_ID_UPP_B;
   }
   else if ( strcmp(env, "C") == 0 )
   {
      qDebug("intelce using plane C\n");
      nativeWindow= GDL_PLANE_ID_UPP_C;
   }
   else if ( strcmp(env, "D") == 0 )
   {
      qDebug("intelce using plane D\n");
      nativeWindow= GDL_PLANE_ID_UPP_D;
   }

   setSurfaceFunctions(new IntelCEScreenSurfaceFunctions(this, displayId));
}

IntelCEScreen::~IntelCEScreen()
{
}

bool IntelCEScreen::hasOpenGL()
{
   return true;
}

bool IntelCEScreen::hasOpenGLOverlays() const
{
   return true;
}

bool IntelCEScreen::setupGDL()
{
   gdl_ret_t rc;
   gdl_display_info_t dinfo;
   int gfx_width, gfx_height;

   // Default to 1280x720
   gfx_width= 1280;
   gfx_height= 720;

   char *env= getenv("QT_INTELCE_SCREENSIZE");
   if ( env )
   {
      if ( strcmp( env, "720" ) == 0 )
      {
         gfx_width= 1280;
         gfx_height= 720;
      }
      else if ( strcmp( env, "1080" ) == 0 )
      {
         gfx_width= 1920;
         gfx_height= 1080;
      }
   }
   qDebug( "intelce using gfx at %dx%d\n", gfx_width, gfx_height );

   gdl_init(0);

   rc = gdl_get_display_info(GDL_DISPLAY_ID_0, &dinfo);

   if(rc == GDL_SUCCESS)
   {
      qDebug("IntelCEScreen::setupGDL dinfo.id             = GDL_DISPLAY_ID_%d\n", dinfo.id);
      qDebug("IntelCEScreen::setupGDL dinfo.tvmode.width   = %d pixels\n", dinfo.tvmode.width);
      qDebug("IntelCEScreen::setupGDL dinfo.tvmode.height  = %d pixels\n", dinfo.tvmode.height);
      qDebug("IntelCEScreen::setupGDL dinfo.tvmode.refresh = %d\n", dinfo.tvmode.refresh);
   }
   else
   {
      qFatal("IntelCEScreen::setupGDL [ERROR] gdl_get_display_info: %s\n", gdl_get_error_string(rc));
      return false;
   }

   gdl_rectangle_t src_rect;
   gdl_rectangle_t dst_rect;
   gdl_pixel_format_t pix_fmt = GDL_PF_ARGB_32;
   gdl_color_space_t color_space = GDL_COLOR_SPACE_RGB;
   gdl_plane_id_t plane = (gdl_plane_id_t)nativeWindow;

   int plane_x= 0;
   int plane_y= 0;
   int plane_width= dinfo.tvmode.width;
   int plane_height= dinfo.tvmode.height;

   windowSize = QSize(gfx_width, gfx_height);

   dst_rect.origin.x = plane_x;
   dst_rect.origin.y = plane_y;
   dst_rect.width    = plane_width;
   dst_rect.height   = plane_height;

   src_rect.origin.x = plane_x; 
   src_rect.origin.y = plane_y;
   src_rect.width    = gfx_width;
   src_rect.height   = gfx_height;

   rc = gdl_plane_reset(plane);
   if(rc != GDL_SUCCESS)
   {
      qFatal("IntelCEScreen::setupGDL [ERROR] gdl_plane_reset: %s\n", gdl_get_error_string(rc));
      return false;
   }

   rc = gdl_plane_config_begin(plane);
   if(rc != GDL_SUCCESS)
   {
      qFatal("IntelCEScreen::setupGDL [ERROR] gdl_plane_config_begin: %s\n", gdl_get_error_string(rc));
      return false;
   }

   rc = gdl_plane_set_attr(GDL_PLANE_SRC_COLOR_SPACE, &color_space);
   if(rc != GDL_SUCCESS)
   {
      qFatal("IntelCEScreen::setupGDL [ERROR] gdl_plane_set_attr color space: %s\n", gdl_get_error_string(rc));
      gdl_plane_config_end(GDL_TRUE);
      return false;
   }

   rc = gdl_plane_set_attr(GDL_PLANE_PIXEL_FORMAT, &pix_fmt);
   if(rc != GDL_SUCCESS)
   {
      qFatal("IntelCEScreen::setupGDL [ERROR] gdl_plane_set_attr pixel format: %s\n", gdl_get_error_string(rc));
      gdl_plane_config_end(GDL_TRUE);
      return false;
   }

   rc = gdl_plane_set_attr(GDL_PLANE_DST_RECT, &dst_rect);
   if(rc != GDL_SUCCESS)
   {
      qFatal("IntelCEScreen::setupGDL [ERROR] gdl_plane_set_attr dest rect: %s\n", gdl_get_error_string(rc));
      gdl_plane_config_end(GDL_TRUE);
      return false;
   }

   rc = gdl_plane_set_attr(GDL_PLANE_SRC_RECT, &src_rect);
   if(rc != GDL_SUCCESS)
   {
      qFatal("IntelCEScreen::setupGDL [ERROR] gdl_plane_set_attr source rect: %s\n", gdl_get_error_string(rc));
      gdl_plane_config_end(GDL_TRUE);
      return false;
   }

   qDebug("intelce gdl src (%d,%d) dst (%d,%d)\n", src_rect.width, src_rect.height, dst_rect.width, dst_rect.height );
   if ( (src_rect.width < dst_rect.width) || (src_rect.height < dst_rect.height) )
   {
      qDebug("intelce enable upscaler\n");
      rc = gdl_plane_set_int(GDL_PLANE_SCALE, GDL_TRUE);
      windowUpscale = QSizeF(dst_rect.width / (float)src_rect.width, dst_rect.height / (float)src_rect.height);
   }
   else
   {
      qDebug("intelce disable upscaler\n");
      rc = gdl_plane_set_int(GDL_PLANE_SCALE, GDL_FALSE);
      windowUpscale = QSizeF(1.0f,1.0f);
   }

   rc = gdl_plane_config_end(GDL_FALSE);
   if(rc != GDL_SUCCESS)
   {
      qFatal("IntelCEScreen::setupGDL [ERROR] gdl_plane_config_end: %s\n", gdl_get_error_string(rc));
      gdl_plane_config_end(GDL_TRUE);
      return false;
   }

   //FILL IN REQUIRED BASE CLASS MEMBERS
   QScreen::d = 32;//TODO read this from dinfo
   QScreen::w = QScreen::dw = plane_width;
   QScreen::h = QScreen::dh = plane_height;
   QScreen::physWidth = qRound(dw * 25.4 / 72);//TODO is 72 dpi correct for all monitors
   QScreen::physHeight = qRound(dh * 25.4 / 72);
   QScreen::lstep = QScreen::w * QScreen::d / 4;
   QScreen::data = 0;

   switch (depth())
   {
      case 32:
         setPixelFormat(QImage::Format_ARGB32_Premultiplied);
         break;
      case 24:
         setPixelFormat(QImage::Format_RGB888);
         break;
      case 16:
         setPixelFormat(QImage::Format_RGB16);
         break;
      case 15:
         setPixelFormat(QImage::Format_RGB555);
         break;
      default:
         break;
   }

   //setOffset(offset()); //TODO needed ?

   return true;
}

void IntelCEScreen::shutdownGDL()
{
   gdl_close();
}

bool IntelCEScreen::connect(const QString &displaySpec)
{
   Q_UNUSED(displaySpec);
   qDebug("IntelCEScreen::connect enter\n");

   if(!setupGDL())
   {
      qFatal("IntelCEScreen::connet exit with error\n");
      return false;
   }

   qt_screen = this;

   qDebug("IntelCEScreen::connet exit success\n");

   return true;
}

bool IntelCEScreen::initDevice()
{
   qDebug("IntelCEScreen::initDevice\n");
#ifndef QT_NO_QWS_CURSOR
   if(QCoreApplication::arguments().contains(MOUSE_CURSOR_ARG,Qt::CaseInsensitive))
      IntelCECursor::initCursor();
#endif
   return true;
}

void IntelCEScreen::shutdownDevice()
{
   qDebug("IntelCEScreen::shutdownDevice\n");
}

void IntelCEScreen::disconnect()
{
   qDebug("IntelCEScreen::disconnect\n");
   shutdownGDL();
}

bool IntelCEScreen::chooseContext(QGLContext *context, const QGLContext *shareContext)
{
   qDebug("IntelCEScreen::chooseContext\n");
   return QGLScreen::chooseContext(context, shareContext);
}

void IntelCEScreen::setDirty(const QRect& rect)
{
   Q_UNUSED(rect);
   //qDebug("IntelCEScreen::setDirty\n");
   //no impl
}

void IntelCEScreen::setMode(int w, int h, int d)
{
   qDebug("IntelCEScreen::setMode w=%d h=%d d=%d\n", w, h, d);
   //no impl
   //setDirty(region().boundingRect());
}

bool IntelCEScreen::supportsDepth(int depth) const
{
   Q_UNUSED(depth);
   qDebug("IntelCEScreen::supportsDepth\n");
   //no impl
   return false;
}

void IntelCEScreen::save()
{
   qDebug("IntelCEScreen::save\n");
   //no impl
}

void IntelCEScreen::restore()
{
   qDebug("IntelCEScreen::restore\n");
   //no impl
}

void IntelCEScreen::blank(bool on)
{
   Q_UNUSED(on);
   qDebug("IntelCEScreen::blank\n");
   //no impl
}

bool IntelCEScreen::onCard(const unsigned char *ptr) const
{
   Q_UNUSED(ptr);
   qDebug("IntelCEScreen::onCard 1\n");
   //no impl
   return false;
}

bool IntelCEScreen::onCard(const unsigned char *ptr, ulong &offset) const
{
   Q_UNUSED(ptr);
   Q_UNUSED(offset);
   qDebug("IntelCEScreen::onCard 2\n");
   //no impl
   return false;
}

bool IntelCEScreen::isInterlaced() const
{
   qDebug("IntelCEScreen::isInterlaced\n");
   //no impl
   return false;
}

int IntelCEScreen::memoryNeeded(const QString &str)
{
   int out;
   out = QGLScreen::memoryNeeded(str);
   if(out != 0)
      qDebug("IntelCEScreen::memoryNeeded =  %d\n", out);
   return out;
}

int IntelCEScreen::sharedRamSize(void *ptr)
{
   int out;
   out = QGLScreen::sharedRamSize(ptr);
   if(out != 0)
      qDebug("IntelCEScreen::sharedRamSize =  %d\n", out);
   return out;
}

void IntelCEScreen::haltUpdates()
{
   qDebug("IntelCEScreen::haltUpdates\n");
   //no impl
}

void IntelCEScreen::resumeUpdates()
{
   qDebug("IntelCEScreen::resumeUpdates\n");
   //no impl
}

void IntelCEScreen::blit(const QImage &img, const QPoint &topLeft, const QRegion &region)
{
   Q_UNUSED(img);Q_UNUSED(topLeft);Q_UNUSED(region);
   qDebug("IntelCEScreen::blit\n");
   //no impl
}

void IntelCEScreen::solidFill(const QColor &color, const QRegion &region)
{
   Q_UNUSED(color);Q_UNUSED(region);
   qDebug("IntelCEScreen::solidFill\n");
   //no impl
}

QWSWindowSurface* IntelCEScreen::createSurface(QWidget *widget) const
{
   qDebug("IntelCEScreen::createSurface: widget=%p\n", widget);
   if (!(qobject_cast<QGLWidget*>(widget)))
   {
      qDebug("IntelCEScreen::createSurface: [ERROR] not a QGLWidget\n");
      return QScreen::createSurface(widget);
   }
   return new IntelCESurface(widget);
}

QWSWindowSurface* IntelCEScreen::createSurface(const QString &key) const
{
   qDebug("IntelCEScreen::createSurface: key=%s\n", key.toLatin1().constData());
   return new IntelCESurface(0);
}

QList<QScreen*> IntelCEScreen::subScreens() const
{
   QList<QScreen*> subs = QGLScreen::subScreens();
   if(subs.length() != 0)
   {
      qWarning("IntelCEScreen::subScreens -> founds subscreens\n");
   }
   return subs;
}

QRegion IntelCEScreen::region() const
{
   static QRect brSaved = QGLScreen::region().boundingRect();
   QRegion reg = QGLScreen::region();
   if(brSaved != reg.boundingRect())
   {
      qWarning("IntelCEScreen::region -> region rectangle has changed\n");
   }
   return reg;
}

void IntelCEScreen::getWindowSizeAndUpscale(QSize* size, QSizeF* upscale)
{
   *size = windowSize;
   *upscale = windowUpscale;

   qDebug() << __func__ << size << " " << upscale;
}

void* IntelCEScreen::getHRMConsumerInterface()
{
   printf("IntelCEScreen::getHRMConsumerInterface called return %p\n", hrmConsumerInterface);
   return hrmConsumerInterface;
}

void IntelCEScreen::setHRMConsumerInterface(void* i)
{
   printf("IntelCEScreen::setHRMConsumerInterface called with %p\n", i);
   hrmConsumerInterface = i;
}

