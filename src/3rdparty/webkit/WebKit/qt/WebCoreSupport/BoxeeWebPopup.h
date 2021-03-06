/*
 * Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */
#ifndef BoxeeWebPopup_h
#define BoxeeWebPopup_h

#include "QtAbstractWebPopup.h"
#include <QComboBox>
#include "qjson/serializer.h"
#include <qwebpage.h>

namespace WebCore {

class QtFallbackWebPopupCombo;

class BoxeeWebPopup : public QObject, public QtAbstractWebPopup {
    Q_OBJECT
public:
    BoxeeWebPopup(QWebPage*);
    ~BoxeeWebPopup();

    virtual void show();
    virtual void hide();

    void destroyPopup();

private slots:
    void callBoxee();
    void checkForReply();

private:
    friend class QtFallbackWebPopupCombo;
    bool m_popupVisible;
    QtFallbackWebPopupCombo* m_combo;
    QWebPage               * m_page;
    QTimer                 * m_replyTimer;
    QJson::Serializer m_serializer;

};

class QtFallbackWebPopupCombo : public QComboBox {
public:
    QtFallbackWebPopupCombo(BoxeeWebPopup& ownerPopup);
    virtual void showPopup();
    virtual void hidePopup();
    virtual bool eventFilter(QObject* watched, QEvent* event);

private:
    BoxeeWebPopup& m_ownerPopup;
};

}

#endif // BoxeeWebPopup_h
