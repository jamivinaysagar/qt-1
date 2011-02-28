#ifndef INTELCESCREEN_H
#define INTELCESCREEN_H

#include <QtOpenGL/QGLScreen>

class IntelCEScreen : public QGLScreen
{
public:
    IntelCEScreen(int displayId);
    ~IntelCEScreen();
    bool hasOpenGL();
	bool hasOpenGLOverlays() const;
    bool chooseContext(QGLContext *context, const QGLContext *shareContext);
    bool initDevice();
    bool connect(const QString &displaySpec);
    void disconnect();
    void shutdownDevice();
    void setMode(int,int,int);
    bool supportsDepth(int) const;
    void save();
    void restore();
    void blank(bool on);
    bool onCard(const unsigned char *) const;
    bool onCard(const unsigned char *, ulong& out_offset) const;
    bool isInterlaced() const;
    int memoryNeeded(const QString&);
    int sharedRamSize(void *);
    void haltUpdates();
    void resumeUpdates();
    void blit(const QImage &img, const QPoint &topLeft, const QRegion &region);
    void solidFill(const QColor &color, const QRegion &region);
    void setDirty(const QRect&);
    QWSWindowSurface* createSurface(QWidget *widget) const;
    QWSWindowSurface* createSurface(const QString &key) const;
    QList<QScreen*> subScreens() const;
    QRegion region() const;
	virtual void getWindowSizeAndUpscale(QSize* size, QSizeF* upscale);
	virtual void* getHRMConsumerInterface();
	virtual void setHRMConsumerInterface(void* i);
private:
    bool setupGDL();
    void shutdownGDL();
    friend class IntelCEScreenSurfaceFunctions;
    bool verbose;
    EGLint nativeWindow;
	QSize windowSize;
	QSizeF windowUpscale;
	void* hrmConsumerInterface;
};

#endif // IntelCEScreen_H
