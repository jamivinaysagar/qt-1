#ifndef CEPLUGIN_H
#define CEPLUGIN_H

#include <QtCore>
#include <qtbrowserplugin.h>

class CEPlugin : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)

    Q_CLASSINFO("MIME", "trivial/very:xxx:Trivial and useless")
    //Q_CLASSINFO("ToSuperClass", "CEPlugin")
    Q_CLASSINFO("DefaultProperty", "text")

public:
    CEPlugin();

    /*
    void mousePressEvent(QMouseEvent *) {}
    void mouseMoveEvent(QMouseEvent *e) {}
    */

    QString text() const; //{return m_text;}

public slots:

    void setText(const QString &text); //{m_text = text;}

signals:
    /*
    void mouseDown();
    void mouseMove(int x, int y);
    void mouseUp();
    */

protected:

private:
    QString m_text;

};

#endif // CEPLUGIN_H
