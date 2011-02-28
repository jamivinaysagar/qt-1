/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the tools applications of the Qt Toolkit.
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

/*
  qmlcodemarker.h
*/

#ifndef QMLCODEMARKER_H
#define QMLCODEMARKER_H

#include "private/qdeclarativejsastfwd_p.h"
#include "cppcodemarker.h"

QT_BEGIN_NAMESPACE

class QmlCodeMarker : public CppCodeMarker
{
public:
    QmlCodeMarker();
    ~QmlCodeMarker();

    virtual bool recognizeCode(const QString &code);
    virtual bool recognizeExtension(const QString &ext);
    virtual bool recognizeLanguage(const QString &language);
    virtual Atom::Type atomType() const;
    virtual QString plainName(const Node *node);
    virtual QString plainFullName(const Node *node, const Node *relative);
    virtual QString markedUpCode(const QString &code, 
                                 const Node *relative, 
                                 const Location &location);

    virtual QString markedUpName(const Node *node);
    virtual QString markedUpFullName(const Node *node, const Node *relative);
    virtual QString markedUpIncludes(const QStringList &includes);
    virtual QString functionBeginRegExp(const QString &funcName);
    virtual QString functionEndRegExp(const QString &funcName);

    /* Copied from src/declarative/qml/qdeclarativescriptparser.cpp */
    QList<QDeclarativeJS::AST::SourceLocation> extractPragmas(QString &script);

private:
    QString addMarkUp(const QString &code, const Node *relative,
                      const Location &location);
};

QT_END_NAMESPACE

#endif
