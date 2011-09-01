
#include <QtGui>

#include "qtbrowserplugin.h"
#include "qtbrowserplugin_p.h"

#include "qtnpapi.h"

#include <stdlib.h>

extern GL_FuncTable* glFuncTable; //defined in qtbrowserplugin.cpp

extern "C" bool qtns_event(QtNPInstance* instance, NPEvent* pEvt)
{
    PluginEvent* event = (PluginEvent*)pEvt;

    if(event->type != PluginPaintEventType)
    {
        fprintf(stderr, "\n%s::%s(%d)\tevent type is not PluginPaintEventType - ignoring\n", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

#if 0
    fprintf(stderr, "\n\n%s::%s(%d)\tQtNPInstance:\nfMode = %d\nwindow = %p\ngeometry.x = %d, geometry.y = %d, geometry.height = %d, geometry.width = %d\
                     \nmimetype = %s\nhtmlID = %s\nqt.widget/object = %p\n...\n\n"
                      , __FILE__, __FUNCTION__, __LINE__
                      , instance->fMode
                      , instance->window
                      , instance->geometry.x(), instance->geometry.y(), instance->geometry.height(), instance->geometry.width()
                      , instance->mimetype.toUtf8().data()
                      , instance->htmlID.data()
                      , instance->qt.widget);

    fprintf(stderr, "\n\n%s::%s(%d)\tevent.paint:\ntype=%d\nbUseAccelBlit = %d\ninval.top = %d, inval.left = %d, inval.bottom = %d, inval.right = %d\
                        \nw = %d\nh = %d\nxoffset = %d\nyoffset = %d\npitch = %d\ndepth = %d\npixels = %p\n\n" //nevent->paint.pixels->m_painter = %p\n\n"
                      , __FILE__, __FUNCTION__, __LINE__
                      , event->paint.type
                      , event->paint.bUseAccelBlit
                      , event->paint.inval.top , event->paint.inval.left, event->paint.inval.bottom, event->paint.inval.right
                      , event->paint.w
                      , event->paint.h
                      , event->paint.xoffset
                      , event->paint.yoffset
                      , event->paint.pitch
                      , event->paint.depth
                      , event->paint.pixels);
#endif

    //create surface
    void* srcSurface = NULL;
    srcSurface = glFuncTable->pfCreateSurface(instance->geometry.width(), instance->geometry.height(), 32);

    if(srcSurface == NULL)
    {
        fprintf(stderr, "\n%s::%s(%d)\tfailed to create surface\n", __FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    //draw rect
    PluginRect srcRect;
    srcRect.top = 0;
    srcRect.left = 0;
    srcRect.bottom = instance->geometry.height();
    srcRect.right = instance->geometry.width();

    if(!glFuncTable->pfDrawRect(srcSurface, 0x00FF00, &srcRect))
    {
        fprintf(stderr, "\n%s::%s(%d)\tfailed to draw rect\n", __FILE__, __FUNCTION__, __LINE__);
        //free surface
        glFuncTable->pfFreeSurface(srcSurface);
        return false;
    }

    //blit
    int targetPitch = event->paint.pitch;
    //int targetPitch = event->paint.pitch / event->paint.inval.right * instance->geometry.width();
    PluginRect destRect;
    destRect.top = instance->geometry.y();
    destRect.left = instance->geometry.x();
    destRect.bottom = destRect.top + instance->geometry.height();
    destRect.right = destRect.left + instance->geometry.width();

    if(glFuncTable->pfBlit(srcSurface, event->paint.pixels, targetPitch, &srcRect, &destRect, false))
    {
        fprintf(stderr, "\n%s::%s(%d)\tfailed to blit\n", __FILE__, __FUNCTION__, __LINE__);
        //free surface
        glFuncTable->pfFreeSurface(srcSurface);
        return false;
    }


    //free surface
    glFuncTable->pfFreeSurface(srcSurface);

    return true;
}

extern "C" void qtns_initialize(QtNPInstance* This)
{
    fprintf(stderr, "%s::%s(%d): NOT IMPLEMENTED YET\n", __FILE__, __FUNCTION__, __LINE__);
}

extern "C" void qtns_destroy(QtNPInstance* This)
{
    fprintf(stderr, "%s::%s(%d): NOT IMPLEMENTED YET\n", __FILE__, __FUNCTION__, __LINE__);
}

extern "C" void qtns_shutdown()
{
    fprintf(stderr, "%s::%s(%d): NOT IMPLEMENTED YET\n", __FILE__, __FUNCTION__, __LINE__);
}

extern "C" void qtns_embed(QtNPInstance *This)
{
    fprintf(stderr, "%s::%s(%d): NOT IMPLEMENTED YET\n", __FILE__, __FUNCTION__, __LINE__);
}

extern "C" void qtns_setGeometry(QtNPInstance *This, const QRect &rect, const QRect &)
{
    fprintf(stderr, "%s::%s(%d): NOT IMPLEMENTED YET\n", __FILE__, __FUNCTION__, __LINE__);
}

/*
extern "C" void qtns_print(QtNPInstance * This, NPPrint *printInfo)
{
    NPWindow* printWindow = &(printInfo->print.embedPrint.window);
    void* platformPrint = printInfo->print.embedPrint.platformPrint;
    // #### Nothing yet.
}
*/
