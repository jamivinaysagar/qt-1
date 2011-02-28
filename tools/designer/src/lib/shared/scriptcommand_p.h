/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Designer of the Qt Toolkit.
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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of Qt Designer.  This header
// file may change from version to version without notice, or even be removed.
//
// We mean it.
//

#ifndef QDESIGNER_SCRIPTCOMMAND_H
#define QDESIGNER_SCRIPTCOMMAND_H

#include "qdesigner_formwindowcommand_p.h"

#include <QtCore/QPair>
#include <QtCore/QList>
#include <QtCore/QPointer>

QT_BEGIN_NAMESPACE

class QDesignerFormWindowInterface;

namespace qdesigner_internal {

class QDESIGNER_SHARED_EXPORT ScriptCommand: public QDesignerFormWindowCommand
{
    ScriptCommand(const ScriptCommand &);
    ScriptCommand& operator=(const ScriptCommand &);

public:
    explicit ScriptCommand(QDesignerFormWindowInterface *formWindow);

    typedef QList<QObject *> ObjectList;
    bool init(const ObjectList &list, const QString &script);

    virtual void redo();
    virtual void undo();

private:
    typedef QPair<QPointer<QObject>, QString> ObjectScriptPair;
    typedef QList<ObjectScriptPair> ObjectScriptList;
    ObjectScriptList m_oldValues;
    QString m_script;
};

} // namespace qdesigner_internal

QT_END_NAMESPACE

#endif // QDESIGNER_SCRIPTCOMMAND_H
