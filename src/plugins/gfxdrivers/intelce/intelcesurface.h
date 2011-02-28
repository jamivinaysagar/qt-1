#ifndef INTELCESURFACE_H
#define INTELCESURFACE_H

#include <private/qglwindowsurface_qws_p.h>

class IntelCESurface : public QWSGLWindowSurface
{
public:
    IntelCESurface();
    IntelCESurface(QWidget *w);
    ~IntelCESurface();
    bool isValid() const;
    QString key() const;
    QImage image() const;
    QPaintDevice *paintDevice();
private:
	QPaintDevice *pdevice;
	QImage img;
};

#endif
