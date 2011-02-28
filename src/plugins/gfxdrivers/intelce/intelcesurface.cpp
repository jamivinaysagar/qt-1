#include "intelcesurface.h"

IntelCESurface::IntelCESurface()
    : QWSGLWindowSurface()
{
    qDebug("IntelCESurface::CTOR 1 this=%p\n", this);
}

IntelCESurface::IntelCESurface(QWidget *w)
    :  QWSGLWindowSurface(w), pdevice(w)
{
    qDebug("IntelCESurface::CTOR 2 this=%p widget=%p\n", this, w);
}

IntelCESurface::~IntelCESurface()
{
}

bool IntelCESurface::isValid() const
{ 
	return true; 
}
QString IntelCESurface::key() const 
{ 
	return QLatin1String("intelce"); 
}
QImage IntelCESurface::image() const
{
	return img;
}
QPaintDevice *IntelCESurface::paintDevice()
{
	return pdevice;
}
