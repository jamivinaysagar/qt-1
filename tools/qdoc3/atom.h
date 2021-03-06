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
  atom.h
*/

#ifndef ATOM_H
#define ATOM_H

#include <qstring.h>

#define QDOC_QML

QT_BEGIN_NAMESPACE

class Atom
{
 public:
    enum Type { 
        AbstractLeft,       // 00
        AbstractRight,
        AnnotatedList,
        AutoLink,
        BaseName,
        BriefLeft,
        BriefRight,
        C,
        CaptionLeft,
        CaptionRight,
        Code,               // 10
        CodeBad,
        CodeNew,
        CodeOld,
        CodeQuoteArgument,
        CodeQuoteCommand,
        Div,
#ifdef QDOC_QML
        EndDiv,
        EndQmlText,
#endif
        FootnoteLeft,
        FootnoteRight,      // 20
        FormatElse,
        FormatEndif,
        FormatIf,
        FormattingLeft,
        FormattingRight,
        GeneratedList,
        GuidLink,
        Image,
        ImageText,
        InlineImage,        // 30
#ifdef QDOC_QML
        JavaScript,
        EndJavaScript,
#endif
        LegaleseLeft,
        LegaleseRight,
        LineBreak,
        Link,
        LinkNode,
        ListLeft,
        ListItemNumber,
        ListTagLeft,        // 40
        ListTagRight,       // 41
        ListItemLeft,       // 42
        ListItemRight,      // 43
        ListRight,          // 44
        Nop,
        ParaLeft,
        ParaRight,
#ifdef QDOC_QML
        Qml,
        QmlText,
#endif
        QuotationLeft,      // 50
        QuotationRight,
        RawString,
        SectionLeft,        // 53
        SectionRight,
        SectionHeadingLeft,
        SectionHeadingRight,
        SidebarLeft,
        SidebarRight,
        SinceList,
        SnippetCommand,     // 60
        SnippetIdentifier,
        SnippetLocation,
        String,             // 63
        TableLeft,          // 64
        TableRight,
        TableHeaderLeft,
        TableHeaderRight,
        TableRowLeft,
        TableRowRight,
        TableItemLeft,      // 70
        TableItemRight,
        TableOfContents,
        Target,             // 73
        UnhandledFormat, 
        UnknownCommand,
        Last = UnknownCommand
    };

    Atom(Type type, const QString &string = "")
	: nxt(0), typ(type), str(string) { }
    Atom(Atom *prev, Type type, const QString &string = "")
	: nxt(prev->nxt), typ(type), str(string) { prev->nxt = this; }

    void appendChar(QChar ch) { str += ch; }
    void appendString(const QString& string) { str += string; }
    void chopString() { str.chop(1); }
    void setString(const QString &string) { str = string; }
    Atom *next() { return nxt; }
    void setNext(Atom *newNext) { nxt = newNext; }

    const Atom *next() const { return nxt; }
    const Atom *next(Type t) const;
    const Atom *next(Type t, const QString& s) const;
    Type type() const { return typ; }
    QString typeString() const;
    const QString& string() const { return str; }
    void dump() const;

    static QString BOLD_;
    static QString INDEX_;
    static QString ITALIC_;
    static QString LINK_;
    static QString PARAMETER_;
    static QString SUBSCRIPT_;
    static QString SUPERSCRIPT_;
    static QString TELETYPE_;
    static QString UNDERLINE_;

    static QString BULLET_;
    static QString TAG_;
    static QString VALUE_;
    static QString LOWERALPHA_;
    static QString LOWERROMAN_;
    static QString NUMERIC_;
    static QString UPPERALPHA_;
    static QString UPPERROMAN_;

 private:
    Atom *nxt;
    Type typ;
    QString str;
};

#define ATOM_FORMATTING_BOLD            "bold"
#define ATOM_FORMATTING_INDEX           "index"
#define ATOM_FORMATTING_ITALIC          "italic"
#define ATOM_FORMATTING_LINK            "link"
#define ATOM_FORMATTING_PARAMETER       "parameter"
#define ATOM_FORMATTING_SUBSCRIPT       "subscript"
#define ATOM_FORMATTING_SUPERSCRIPT     "superscript"
#define ATOM_FORMATTING_TELETYPE        "teletype"
#define ATOM_FORMATTING_UNDERLINE       "underline"

#define ATOM_LIST_BULLET                "bullet"
#define ATOM_LIST_TAG                   "tag"
#define ATOM_LIST_VALUE                 "value"
#define ATOM_LIST_LOWERALPHA            "loweralpha"
#define ATOM_LIST_LOWERROMAN            "lowerroman"
#define ATOM_LIST_NUMERIC               "numeric"
#define ATOM_LIST_UPPERALPHA            "upperalpha"
#define ATOM_LIST_UPPERROMAN            "upperroman"

QT_END_NAMESPACE

#endif
