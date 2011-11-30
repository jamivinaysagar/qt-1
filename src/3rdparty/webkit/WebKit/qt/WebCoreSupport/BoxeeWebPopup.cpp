/*
 * Copyright (C) 2010 Girish Ramakrishnan <girish@forwardbias.in>
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
#include "config.h"
#include "BoxeeWebPopup.h"

#ifndef QT_NO_COMBOBOX

#include "HostWindow.h"
#include "PopupMenuClient.h"
#include "QWebPageClient.h"
#include "qgraphicswebview.h"
#include <QAbstractItemView>
#include <QApplication>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QInputContext>
#include <QMouseEvent>
#include <QStandardItemModel>
#include <qwebpage.h>
#include <qwebframe.h>
#include <qwebelement.h>
#include <QTimer>
#include "qjson/parser.h"

#if ENABLE(SYMBIAN_DIALOG_PROVIDERS)
#include <BrCtlDialogsProvider.h>
#include <BrowserDialogsProvider.h> // S60 platform private header file
#include <e32base.h>
#endif
#include <stdio.h>

namespace WebCore {


BoxeeWebPopup::BoxeeWebPopup(QWebPage *webPage)
    : QtAbstractWebPopup()
    , m_popupVisible(false)
    , m_combo(0)
    , m_page(webPage)
{
}

BoxeeWebPopup::~BoxeeWebPopup()
{
    destroyPopup();
}

void BoxeeWebPopup::callBoxee()
{
  QWebElement doc = m_page->currentFrame()->documentElement();

  QVariantMap request;
  QVariantList params1;

  for (int i = 0; i < itemCount(); ++i) {
    QVariantMap params;
      switch (itemType(i)) {
      case Separator:
          params.insert("type", QVariant("separator"));
          break;
      case Group:
          params.insert("type", QVariant("group"));
          params.insert("value", QVariant(itemText(i)));
          break;
      case Option:
          params.insert("type", QVariant("option"));
          params.insert("value", QVariant(itemText(i)));
          if (itemIsSelected(i))
            params.insert("selected", QVariant(true));
          else
            params.insert("selected", QVariant(false));
          break;
      }
      params1.append(QVariant(params));
  }

  request.insert("command", QVariant("DROPDOWN.Choose"));
  request.insert("parameters", params1);
  QByteArray serialized = m_serializer.serialize(request);
  QString s(serialized);
  QByteArray  encoded = QUrl::toPercentEncoding(s);
  s = encoded;
  QString js;
  js = "boxee.exec2('boxee.handleBrowserCommandResponse(\\'";
  js += s;
  js += "\\');')";

  //fprintf(stderr, "callBoxee: %s\n", js.toLocal8Bit().constData());

  QVariant result;
  result = doc.webFrame()->evaluateJavaScript(js);
  //fprintf(stderr, "callBoxee: %s\n", result.toString().toUtf8().data());

  m_replyTimer = new QTimer(this);
  connect(m_replyTimer, SIGNAL(timeout()), this, SLOT(checkForReply()));
  m_replyTimer->start(1000);
}

void BoxeeWebPopup::checkForReply()
{
  QWebElement doc = m_page->currentFrame()->documentElement();

  QVariantMap request;
  QVariantList params;

  request.insert("command", QVariant("DROPDOWN.Reply"));
  request.insert("parameters", params);
  QByteArray serialized = m_serializer.serialize(request);

 // javascript call for: boxeePlayer.handleRequest()
  QString js;
  js = "boxee.exec2('boxee.handleBrowserCommandResponse(\\'";
  js += QString(serialized);
  js += "\\');')";

  //fprintf(stderr, "checkForReply request: %s\n", js.toLocal8Bit().constData());

  QVariant response = doc.webFrame()->evaluateJavaScript(js);
  //fprintf(stderr, "checkForReply response: %s\n", response.toString().toUtf8().data());

  QJson::Parser parser;
  bool ok;
  QVariantMap res = parser.parse(response.toByteArray(), &ok).toMap();

  if (!ok)
  {
    fprintf(stderr, "checkForReply: Could not parse Boxees response");
    valueChanged(-1);
    popupDidHide();
    m_replyTimer->stop();
  }

  if (res["chosen"].toString() == "true")
  {
    //fprintf(stderr, "checkForReply: Boxee chose\n");
    QVariantList values = res["values"].toList();
    QString str = values[0].toString();
    int selectedItem = -1;
    for (int i = 0; i < itemCount(); ++i) {
      if (itemType(i) == Option && str == itemText(i))
      {
        //fprintf(stderr, "checkForReply: Boxee chose (value \"%s\") (index %u)\n", str.toUtf8().data(), i);
        selectedItem = i;
        break;
      }
    }
    valueChanged(selectedItem);
    popupDidHide();
    m_replyTimer->stop();
  }
}

void BoxeeWebPopup::show()
{
  QTimer::singleShot(200, this, SLOT(callBoxee()));
}

void BoxeeWebPopup::hide()
{
    // Destroying the QComboBox here cause problems if the popup is in the
    // middle of its show animation. Instead we rely on the fact that the
    // Qt::Popup window will hide itself on mouse events outside its window.
}

void BoxeeWebPopup::destroyPopup()
{
    if (m_combo) {
        m_combo->deleteLater();
        m_combo = 0;
    }
}


}

#endif // QT_NO_COMBOBOX
