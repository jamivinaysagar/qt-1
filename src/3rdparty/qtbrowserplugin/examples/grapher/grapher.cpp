/****************************************************************************
**
** Copyright (C) 2003-2008 Trolltech ASA. All rights reserved.
**
** This file is part of a Qt Solutions component.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://www.trolltech.com/products/qt/opensource.html
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://www.trolltech.com/products/qt/licensing.html or contact the
** Trolltech sales department at sales@trolltech.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#include <QtGui>
#include <qtbrowserplugin.h>

#ifdef QAXSERVER
#include <ActiveQt/QAxBindable>
#endif

class Graph : public QWidget, public QtNPBindable
#ifdef QAXSERVER
            , public QAxBindable
#endif
{
    Q_OBJECT
    Q_ENUMS(GraphStyle)
    Q_PROPERTY(GraphStyle graphStyle READ graphStyle WRITE setGraphStyle)

    Q_CLASSINFO("ClassID", "{2e5b2715-46b2-4831-ba9b-6a3b195d5ec8}")
    Q_CLASSINFO("InterfaceID", "{94581136-3c0c-46cc-97a1-066061356d43}")
    Q_CLASSINFO("EventsID", "{8c191b77-1894-45c7-9d6b-201dede95410}")

    Q_CLASSINFO("MIME", "application/x-graphable:g1n:Graphable ASCII numeric data")
public:
    Graph(QWidget *parent = 0);
    ~Graph();

    enum GraphStyle
    {
        Pie,
        Bar
    };
    void setGraphStyle(GraphStyle style);
    GraphStyle graphStyle() const;

    bool readData(QIODevice *source, const QString &format);
    bool writeData(QIODevice *sink);

    void transferComplete(const QString &url, int id, Reason r);

protected:
    void timerEvent(QTimerEvent*);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *me);

    void paintWait();
    void paintBar(QPaintEvent*);
    void paintPie(QPaintEvent*);

private slots:
    void stylePie();
    void styleBar();
    void aboutPlugin();
    void aboutData();
    void aboutQt();
    void aboutTrolltech();

private:
    struct Datum {
        double value;
        QString label;
    };
    QList<Datum> data;
    void processData(QTextStream &in);

    QMenu *menu;
    QStatusBar *statusbar;
    QAction *pie, *bar;

    int pieRotation;
    int pieTimer;
    GraphStyle m_style;

    int lastReqId, lastConfId;
    QString lastConfUrl;
    Reason lastConfReason;
};


Graph::Graph(QWidget *parent)
: QWidget(parent), pieRotation(0), pieTimer(0)
{
    menu = new QMenu(this);
    QMenu *styles = menu->addMenu("&Styles");

    pie = styles->addAction("&Pie",this,SLOT(stylePie()));
    pie->setShortcut(QString("Ctrl+P"));
    pie->setCheckable(true);

    bar = styles->addAction("&Bar", this, SLOT(styleBar()));
    bar->setShortcut(QString("Ctrl+B"));
    bar->setCheckable(true);

    QActionGroup *group = new QActionGroup(this);
    group->setExclusive(true);

    group->addAction(pie);
    group->addAction(bar);

    QMenu* help = menu->addMenu("&Help");
    help->addAction("About &plugin...", this, SLOT(aboutPlugin()))->setShortcut(QString("Ctrl+A"));
    help->addAction("About &data...", this, SLOT(aboutData()));
    help->addAction("About &Qt...", this, SLOT(aboutQt()));
    help->addAction("About &Trolltech...", this, SLOT(aboutTrolltech()));

    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+F5"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(aboutQt()));

    statusbar = new QStatusBar(this);

    setFocusPolicy(Qt::StrongFocus);
    setGraphStyle(Pie);

    QPalette pal = palette();
    pal.setColor(QPalette::Window,Qt::white);
    setPalette(pal);

    lastReqId = 0;
    lastConfId = 0;
    lastConfReason = ReasonUnknown;
}

Graph::~Graph()
{
}

void Graph::setGraphStyle(GraphStyle style)
{
    if (style==m_style)
        return;

    if (pieTimer)
        killTimer(pieTimer);

    m_style = style;
    switch(m_style) {
    case Pie:
        pieTimer = startTimer(50);
        pie->setChecked(true);
        break;
    case Bar:
        bar->setChecked(true);
        break;
    }

    repaint();
}

Graph::GraphStyle Graph::graphStyle() const
{
    return m_style;
}

void Graph::aboutPlugin()
{
    openUrl("http://www.trolltech.com/products/solutions/catalog/4/Utilities/qtbrowserplugin/");
}

void Graph::aboutData()
{
    QString page = parameters().value("datapage").toString();
    if (!page.isEmpty()) {
	openUrl(page);
    } else {
        QByteArray table("<b>This data has been loaded with streammode = '");
        table += parameters().contains("streammode") ? parameters().value("streammode").toByteArray() : QByteArray("Default");
        table += "'</b>\n";
        table += "<table>\n";
        for (int i = 0; i < data.count(); ++i) {
            Datum datum = data.at(i);
            table += "<tr><td>" + datum.label + "</td><td>" + QString::number(datum.value) + "</td></tr>\n";
        }
        table += "</table>\n";

        table += "<p>Last OpenURL request id: " + QString::number(lastReqId);
        table += "<br>Last confirmation id: " + QString::number(lastConfId);
        table += " Reason: " + QString::number((int)lastConfReason);
        table += "<br>URL: " + lastConfUrl;
        QMessageBox::information(this, "Data information", QLatin1String(table));
    }
}

void Graph::transferComplete(const QString &url, int id, Reason r)
{
    lastConfId = id;
    lastConfUrl = url;
    lastConfReason = r;
}

void Graph::aboutQt()
{
    QMessageBox::aboutQt(this);
}

void Graph::aboutTrolltech()
{
    lastReqId = openUrl("http://www.trolltech.com");
}

void Graph::stylePie()
{
    setGraphStyle(Pie);
}

void Graph::styleBar()
{
    setGraphStyle(Bar);
}

bool Graph::readData(QIODevice *source, const QString &/*format*/)
{
    if (!source->open(QIODevice::ReadOnly|QIODevice::Text))
        return false;

    QTextStream in(source);
    processData(in);

    update();
    return true;
}

void Graph::processData(QTextStream &in)
{
    while (!in.atEnd()) {
        Datum datum;
        QString value;
        in >> value;
        in >> datum.label;
        bool ok;
        datum.value = value.toDouble(&ok);
        if (ok)
            data += datum;
    }
}

bool Graph::writeData(QIODevice *target)
{
    if (!target->open(QIODevice::WriteOnly|QIODevice::Text))
        return false;

    QTextStream out(target);
    foreach(Datum datum, data) {
        out << datum.value << "\t" << datum.label << endl;
    }

    return true;
}

void Graph::timerEvent(QTimerEvent *e)
{
    if (e->timerId() == pieTimer) {
        pieRotation = (pieRotation + 1) % 360;
        update();
    }
    QWidget::timerEvent(e);
}

void Graph::enterEvent(QEvent *)
{
    statusbar->showMessage(QString("Qt Grapher plugin [%1]").arg(mimeType()));
}

void Graph::leaveEvent(QEvent *)
{
    if (!QApplication::activePopupWidget()) {
        statusbar->clearMessage();
    }
}

void Graph::paintEvent(QPaintEvent* event)
{
    if (!data.count()) {
	paintWait();
    } else {
        switch (m_style) {
        case Pie:
            paintPie(event);
            break;
        default:
            paintBar(event);
            break;
        }
    }
}

void Graph::mousePressEvent(QMouseEvent *me)
{
    menu->exec(me->globalPos());
}

void Graph::paintWait()
{
    QPainter p(this);
    p.drawText(rect(), Qt::AlignCenter, "Loading...");
}

void Graph::paintBar(QPaintEvent* event)
{
    const int count = data.count();
    double max = 0.0;
    for (int i = 0; i < count; ++i) {
        double value = data.at(i).value;
        if (value > max)
            max = value;
    }

    QPainter painter(this);
    painter.setClipRect(event->rect());
    painter.save();
    painter.setWindow(0, qRound(max), count * 20, qRound(-max));
    painter.setViewport(20, 5, width() - 40, height() - 40);

    for (int i = 0; i < count; ++i) {
        double value = data.at(i).value;
	QColor c;
	c.setHsv((i * 255)/count, 255, 255);// rainbow effect
        painter.setBrush(c);

        painter.drawRect(i * 20, 0, 20, qRound(value));
    }
    painter.restore();
    painter.setClipRect(QRect());
}

void Graph::paintPie(QPaintEvent* event)
{
    const int count = data.count();
    double total = 0.0;

    for (int i = 0; i < count; ++i) {
        double value = data.at(i).value;
        total += value;
    }

    int apos = (pieRotation-90)*16;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setClipRect(event->rect());
    QRect r(rect());
    r.adjust(10, 10, -10, -10);

    for (int i = 0; i < count; ++i) {
        double value = data.at(i).value;
	QColor c;
	c.setHsv((i * 255)/count, 255, 255);// rainbow effect
	painter.setBrush( c );

	int a = int((value * 360.0) / total * 16.0 + 0.5);
	painter.drawPie(r, -apos, -a);
	apos += a;
    }
}

#include "grapher.moc"

QTNPFACTORY_BEGIN("Qt-based Graph Plugin", "A Qt-based LiveConnected plug-in that graphs numeric data");
    QTNPCLASS(Graph)
QTNPFACTORY_END()

#ifdef QAXSERVER
#include <ActiveQt/QAxFactory>
QAXFACTORY_BEGIN("{89ab08da-df8c-4bd0-8327-72f73741c1a6}", "{082bd921-0832-4ca7-ab5a-ec06ca7f3350}")
    QAXCLASS(Graph)
QAXFACTORY_END()
#endif
