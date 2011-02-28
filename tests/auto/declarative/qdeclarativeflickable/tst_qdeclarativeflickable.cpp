/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <qtest.h>
#include <QtTest/QSignalSpy>
#include <QtDeclarative/qdeclarativeengine.h>
#include <QtDeclarative/qdeclarativecomponent.h>
#include <QtDeclarative/qdeclarativeview.h>
#include <private/qdeclarativeflickable_p.h>
#include <private/qdeclarativevaluetype_p.h>
#include <QtGui/qgraphicswidget.h>
#include <math.h>
#include "../../../shared/util.h"

#ifdef Q_OS_SYMBIAN
// In Symbian OS test data is located in applications private dir
#define SRCDIR "."
#endif

class tst_qdeclarativeflickable : public QObject
{
    Q_OBJECT
public:
    tst_qdeclarativeflickable();

private slots:
    void create();
    void horizontalViewportSize();
    void verticalViewportSize();
    void properties();
    void boundsBehavior();
    void maximumFlickVelocity();
    void flickDeceleration();
    void pressDelay();
    void nestedPressDelay();
    void flickableDirection();
    void qgraphicswidget();
    void resizeContent();
    void returnToBounds();
    void testQtQuick11Attributes();
    void testQtQuick11Attributes_data();
    void wheel();

private:
    QDeclarativeEngine engine;

    template<typename T>
    T *findItem(QGraphicsObject *parent, const QString &objectName);
};

tst_qdeclarativeflickable::tst_qdeclarativeflickable()
{
}

void tst_qdeclarativeflickable::create()
{
    QDeclarativeEngine engine;
    QDeclarativeComponent c(&engine, QUrl::fromLocalFile(SRCDIR "/data/flickable01.qml"));
    QDeclarativeFlickable *obj = qobject_cast<QDeclarativeFlickable*>(c.create());

    QVERIFY(obj != 0);
    QCOMPARE(obj->isAtXBeginning(), true);
    QCOMPARE(obj->isAtXEnd(), false);
    QCOMPARE(obj->isAtYBeginning(), true);
    QCOMPARE(obj->isAtYEnd(), false);
    QCOMPARE(obj->contentX(), 0.);
    QCOMPARE(obj->contentY(), 0.);

    QCOMPARE(obj->horizontalVelocity(), 0.);
    QCOMPARE(obj->verticalVelocity(), 0.);

    QCOMPARE(obj->isInteractive(), true);
    QCOMPARE(obj->boundsBehavior(), QDeclarativeFlickable::DragAndOvershootBounds);
    QCOMPARE(obj->pressDelay(), 0);
    QCOMPARE(obj->maximumFlickVelocity(), 2000.);

    delete obj;
}

void tst_qdeclarativeflickable::horizontalViewportSize()
{
    QDeclarativeEngine engine;
    QDeclarativeComponent c(&engine, QUrl::fromLocalFile(SRCDIR "/data/flickable02.qml"));
    QDeclarativeFlickable *obj = qobject_cast<QDeclarativeFlickable*>(c.create());

    QVERIFY(obj != 0);
    QCOMPARE(obj->contentWidth(), 800.);
    QCOMPARE(obj->contentHeight(), 300.);
    QCOMPARE(obj->isAtXBeginning(), true);
    QCOMPARE(obj->isAtXEnd(), false);
    QCOMPARE(obj->isAtYBeginning(), true);
    QCOMPARE(obj->isAtYEnd(), false);

    delete obj;
}

void tst_qdeclarativeflickable::verticalViewportSize()
{
    QDeclarativeEngine engine;
    QDeclarativeComponent c(&engine, QUrl::fromLocalFile(SRCDIR "/data/flickable03.qml"));
    QDeclarativeFlickable *obj = qobject_cast<QDeclarativeFlickable*>(c.create());

    QVERIFY(obj != 0);
    QCOMPARE(obj->contentWidth(), 200.);
    QCOMPARE(obj->contentHeight(), 1200.);
    QCOMPARE(obj->isAtXBeginning(), true);
    QCOMPARE(obj->isAtXEnd(), false);
    QCOMPARE(obj->isAtYBeginning(), true);
    QCOMPARE(obj->isAtYEnd(), false);

    delete obj;
}

void tst_qdeclarativeflickable::properties()
{
    QDeclarativeEngine engine;
    QDeclarativeComponent c(&engine, QUrl::fromLocalFile(SRCDIR "/data/flickable04.qml"));
    QDeclarativeFlickable *obj = qobject_cast<QDeclarativeFlickable*>(c.create());

    QVERIFY(obj != 0);
    QCOMPARE(obj->isInteractive(), false);
    QCOMPARE(obj->boundsBehavior(), QDeclarativeFlickable::StopAtBounds);
    QCOMPARE(obj->pressDelay(), 200);
    QCOMPARE(obj->maximumFlickVelocity(), 2000.);

    QVERIFY(obj->property("ok").toBool() == false);
    QMetaObject::invokeMethod(obj, "check");
    QVERIFY(obj->property("ok").toBool() == true);

    delete obj;
}

void tst_qdeclarativeflickable::boundsBehavior()
{
    QDeclarativeComponent component(&engine);
    component.setData("import QtQuick 1.0; Flickable { boundsBehavior: Flickable.StopAtBounds }", QUrl::fromLocalFile(""));
    QDeclarativeFlickable *flickable = qobject_cast<QDeclarativeFlickable*>(component.create());
    QSignalSpy spy(flickable, SIGNAL(boundsBehaviorChanged()));

    QVERIFY(flickable);
    QVERIFY(flickable->boundsBehavior() == QDeclarativeFlickable::StopAtBounds);

    flickable->setBoundsBehavior(QDeclarativeFlickable::DragAndOvershootBounds);
    QVERIFY(flickable->boundsBehavior() == QDeclarativeFlickable::DragAndOvershootBounds);
    QCOMPARE(spy.count(),1);
    flickable->setBoundsBehavior(QDeclarativeFlickable::DragAndOvershootBounds);
    QCOMPARE(spy.count(),1);

    flickable->setBoundsBehavior(QDeclarativeFlickable::DragOverBounds);
    QVERIFY(flickable->boundsBehavior() == QDeclarativeFlickable::DragOverBounds);
    QCOMPARE(spy.count(),2);
    flickable->setBoundsBehavior(QDeclarativeFlickable::DragOverBounds);
    QCOMPARE(spy.count(),2);

    flickable->setBoundsBehavior(QDeclarativeFlickable::StopAtBounds);
    QVERIFY(flickable->boundsBehavior() == QDeclarativeFlickable::StopAtBounds);
    QCOMPARE(spy.count(),3);
    flickable->setBoundsBehavior(QDeclarativeFlickable::StopAtBounds);
    QCOMPARE(spy.count(),3);
}

void tst_qdeclarativeflickable::maximumFlickVelocity()
{
    QDeclarativeComponent component(&engine);
    component.setData("import QtQuick 1.0; Flickable { maximumFlickVelocity: 1.0; }", QUrl::fromLocalFile(""));
    QDeclarativeFlickable *flickable = qobject_cast<QDeclarativeFlickable*>(component.create());
    QSignalSpy spy(flickable, SIGNAL(maximumFlickVelocityChanged()));

    QVERIFY(flickable);
    QCOMPARE(flickable->maximumFlickVelocity(), 1.0);

    flickable->setMaximumFlickVelocity(2.0);
    QCOMPARE(flickable->maximumFlickVelocity(), 2.0);
    QCOMPARE(spy.count(),1);
    flickable->setMaximumFlickVelocity(2.0);
    QCOMPARE(spy.count(),1);
}

void tst_qdeclarativeflickable::flickDeceleration()
{
    QDeclarativeComponent component(&engine);
    component.setData("import QtQuick 1.0; Flickable { flickDeceleration: 1.0; }", QUrl::fromLocalFile(""));
    QDeclarativeFlickable *flickable = qobject_cast<QDeclarativeFlickable*>(component.create());
    QSignalSpy spy(flickable, SIGNAL(flickDecelerationChanged()));

    QVERIFY(flickable);
    QCOMPARE(flickable->flickDeceleration(), 1.0);

    flickable->setFlickDeceleration(2.0);
    QCOMPARE(flickable->flickDeceleration(), 2.0);
    QCOMPARE(spy.count(),1);
    flickable->setFlickDeceleration(2.0);
    QCOMPARE(spy.count(),1);
}

void tst_qdeclarativeflickable::pressDelay()
{
    QDeclarativeComponent component(&engine);
    component.setData("import QtQuick 1.0; Flickable { pressDelay: 100; }", QUrl::fromLocalFile(""));
    QDeclarativeFlickable *flickable = qobject_cast<QDeclarativeFlickable*>(component.create());
    QSignalSpy spy(flickable, SIGNAL(pressDelayChanged()));

    QVERIFY(flickable);
    QCOMPARE(flickable->pressDelay(), 100);

    flickable->setPressDelay(200);
    QCOMPARE(flickable->pressDelay(), 200);
    QCOMPARE(spy.count(),1);
    flickable->setPressDelay(200);
    QCOMPARE(spy.count(),1);
}

// QTBUG-17361
void tst_qdeclarativeflickable::nestedPressDelay()
{
    QDeclarativeView *canvas = new QDeclarativeView;
    canvas->setSource(QUrl::fromLocalFile(SRCDIR "/data/nestedPressDelay.qml"));
    canvas->show();
    canvas->setFocus();
    QVERIFY(canvas->rootObject() != 0);

    QDeclarativeFlickable *outer = qobject_cast<QDeclarativeFlickable*>(canvas->rootObject());
    QVERIFY(outer != 0);

    QDeclarativeFlickable *inner = canvas->rootObject()->findChild<QDeclarativeFlickable*>("innerFlickable");
    QVERIFY(inner != 0);

    QTest::mousePress(canvas->viewport(), Qt::LeftButton, 0, canvas->mapFromScene(QPoint(150, 150)));
    // the MouseArea is not pressed immediately
    QVERIFY(outer->property("pressed").toBool() == false);

    // The outer pressDelay will prevail (50ms, vs. 10sec)
    QTest::qWait(300);
    QVERIFY(outer->property("pressed").toBool() == true);

    QTest::mouseRelease(canvas->viewport(), Qt::LeftButton, 0, canvas->mapFromScene(QPoint(150, 150)));

    delete canvas;
}

void tst_qdeclarativeflickable::flickableDirection()
{
    QDeclarativeComponent component(&engine);
    component.setData("import QtQuick 1.0; Flickable { flickableDirection: Flickable.VerticalFlick; }", QUrl::fromLocalFile(""));
    QDeclarativeFlickable *flickable = qobject_cast<QDeclarativeFlickable*>(component.create());
    QSignalSpy spy(flickable, SIGNAL(flickableDirectionChanged()));

    QVERIFY(flickable);
    QCOMPARE(flickable->flickableDirection(), QDeclarativeFlickable::VerticalFlick);

    flickable->setFlickableDirection(QDeclarativeFlickable::HorizontalAndVerticalFlick);
    QCOMPARE(flickable->flickableDirection(), QDeclarativeFlickable::HorizontalAndVerticalFlick);
    QCOMPARE(spy.count(),1);

    flickable->setFlickableDirection(QDeclarativeFlickable::AutoFlickDirection);
    QCOMPARE(flickable->flickableDirection(), QDeclarativeFlickable::AutoFlickDirection);
    QCOMPARE(spy.count(),2);

    flickable->setFlickableDirection(QDeclarativeFlickable::HorizontalFlick);
    QCOMPARE(flickable->flickableDirection(), QDeclarativeFlickable::HorizontalFlick);
    QCOMPARE(spy.count(),3);

    flickable->setFlickableDirection(QDeclarativeFlickable::HorizontalFlick);
    QCOMPARE(flickable->flickableDirection(), QDeclarativeFlickable::HorizontalFlick);
    QCOMPARE(spy.count(),3);
}

void tst_qdeclarativeflickable::qgraphicswidget()
{
    QDeclarativeEngine engine;
    QDeclarativeComponent c(&engine, QUrl::fromLocalFile(SRCDIR "/data/flickableqgraphicswidget.qml"));
    QDeclarativeFlickable *flickable = qobject_cast<QDeclarativeFlickable*>(c.create());

    QVERIFY(flickable != 0);
    QGraphicsWidget *widget = findItem<QGraphicsWidget>(flickable->contentItem(), "widget1");
    QVERIFY(widget);
}

// QtQuick 1.1
void tst_qdeclarativeflickable::resizeContent()
{
    QDeclarativeEngine engine;
    QDeclarativeComponent c(&engine, QUrl::fromLocalFile(SRCDIR "/data/resize.qml"));
    QDeclarativeItem *root = qobject_cast<QDeclarativeItem*>(c.create());
    QDeclarativeFlickable *obj = findItem<QDeclarativeFlickable>(root, "flick");

    QVERIFY(obj != 0);
    QCOMPARE(obj->contentX(), 0.);
    QCOMPARE(obj->contentY(), 0.);
    QCOMPARE(obj->contentWidth(), 300.);
    QCOMPARE(obj->contentHeight(), 300.);

    QMetaObject::invokeMethod(root, "resizeContent");

    QCOMPARE(obj->contentX(), 100.);
    QCOMPARE(obj->contentY(), 100.);
    QCOMPARE(obj->contentWidth(), 600.);
    QCOMPARE(obj->contentHeight(), 600.);

    delete root;
}

// QtQuick 1.1
void tst_qdeclarativeflickable::returnToBounds()
{
    QDeclarativeEngine engine;
    QDeclarativeComponent c(&engine, QUrl::fromLocalFile(SRCDIR "/data/resize.qml"));
    QDeclarativeItem *root = qobject_cast<QDeclarativeItem*>(c.create());
    QDeclarativeFlickable *obj = findItem<QDeclarativeFlickable>(root, "flick");

    QVERIFY(obj != 0);
    QCOMPARE(obj->contentX(), 0.);
    QCOMPARE(obj->contentY(), 0.);
    QCOMPARE(obj->contentWidth(), 300.);
    QCOMPARE(obj->contentHeight(), 300.);

    obj->setContentX(100);
    obj->setContentY(400);
    QTRY_COMPARE(obj->contentX(), 100.);
    QTRY_COMPARE(obj->contentY(), 400.);

    QMetaObject::invokeMethod(root, "returnToBounds");

    QTRY_COMPARE(obj->contentX(), 0.);
    QTRY_COMPARE(obj->contentY(), 0.);

    delete root;
}

void tst_qdeclarativeflickable::testQtQuick11Attributes()
{
    QFETCH(QString, code);
    QFETCH(QString, warning);
    QFETCH(QString, error);

    QDeclarativeEngine engine;
    QObject *obj;

    QDeclarativeComponent invalid(&engine);
    invalid.setData("import QtQuick 1.0; Flickable { " + code.toUtf8() + " }", QUrl(""));
    QTest::ignoreMessage(QtWarningMsg, warning.toUtf8());
    obj = invalid.create();
    QCOMPARE(invalid.errorString(), error);
    delete obj;

    QDeclarativeComponent valid(&engine);
    valid.setData("import QtQuick 1.1; Flickable { " + code.toUtf8() + " }", QUrl(""));
    obj = valid.create();
    QVERIFY(obj);
    QVERIFY(valid.errorString().isEmpty());
    delete obj;
}

void tst_qdeclarativeflickable::testQtQuick11Attributes_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<QString>("warning");
    QTest::addColumn<QString>("error");

    QTest::newRow("resizeContent") << "Component.onCompleted: resizeContent(100,100,Qt.point(50,50))"
            << "<Unknown File>:1: ReferenceError: Can't find variable: resizeContent"
            << "";

    QTest::newRow("returnToBounds") << "Component.onCompleted: returnToBounds()"
            << "<Unknown File>:1: ReferenceError: Can't find variable: returnToBounds"
            << "";

}

void tst_qdeclarativeflickable::wheel()
{
    QDeclarativeView *canvas = new QDeclarativeView;
    canvas->setSource(QUrl::fromLocalFile(SRCDIR "/data/wheel.qml"));
    canvas->show();
    canvas->setFocus();
    QVERIFY(canvas->rootObject() != 0);

    QDeclarativeFlickable *flick = canvas->rootObject()->findChild<QDeclarativeFlickable*>("flick");
    QVERIFY(flick != 0);

    QGraphicsScene *scene = canvas->scene();
    QGraphicsSceneWheelEvent event(QEvent::GraphicsSceneWheel);
    event.setScenePos(QPointF(200, 200));
    event.setDelta(-120);
    event.setOrientation(Qt::Vertical);
    event.setAccepted(false);
    QApplication::sendEvent(scene, &event);

    QTRY_VERIFY(flick->contentY() > 0);
    QVERIFY(flick->contentX() == 0);

    flick->setContentY(0);
    QVERIFY(flick->contentY() == 0);

    event.setScenePos(QPointF(200, 200));
    event.setDelta(-120);
    event.setOrientation(Qt::Horizontal);
    event.setAccepted(false);
    QApplication::sendEvent(scene, &event);

    QTRY_VERIFY(flick->contentX() > 0);
    QVERIFY(flick->contentY() == 0);

    delete canvas;
}


template<typename T>
T *tst_qdeclarativeflickable::findItem(QGraphicsObject *parent, const QString &objectName)
{
    const QMetaObject &mo = T::staticMetaObject;
    //qDebug() << parent->childItems().count() << "children";
    for (int i = 0; i < parent->childItems().count(); ++i) {
        QGraphicsObject *item = qobject_cast<QGraphicsObject*>(parent->childItems().at(i));
        if(!item)
            continue;
        //qDebug() << "try" << item;
        if (mo.cast(item) && (objectName.isEmpty() || item->objectName() == objectName)) {
            return static_cast<T*>(item);
        }
        item = findItem<T>(item, objectName);
        if (item)
            return static_cast<T*>(item);
    }

    return 0;
}

QTEST_MAIN(tst_qdeclarativeflickable)

#include "tst_qdeclarativeflickable.moc"
