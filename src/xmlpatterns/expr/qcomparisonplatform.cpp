/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtXmlPatterns module of the Qt Toolkit.
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

/**
 * @file
 * @short This file is included by qcomparisonplatform_p.h.
 * If you need includes in this file, put them in qcomparisonplatform_p.h, outside of the namespace.
 */

template <typename TSubClass, bool issueError,
          AtomicComparator::ComparisonType comparisonType, ReportContext::ErrorCode errorCode>
bool ComparisonPlatform<TSubClass, issueError, comparisonType, errorCode>::
flexibleCompare(const Item &it1,
                const Item &it2,
                const DynamicContext::Ptr &context) const
{
    if(m_comparator)
        /* The comparator was located at compile time. */
        return compare(it1, it2, m_comparator, operatorID());
    else
    {
        const AtomicComparator::Ptr cp(fetchComparator(it1.type(),
                                                       it2.type(),
                                                       context));

        return cp ? compare(it1, it2, cp, operatorID()) : false;
    }
}

template <typename TSubClass, bool issueError,
          AtomicComparator::ComparisonType comparisonType, ReportContext::ErrorCode errorCode>
AtomicComparator::ComparisonResult
ComparisonPlatform<TSubClass, issueError, comparisonType, errorCode>::
detailedFlexibleCompare(const Item &it1,
                        const Item &it2,
                        const DynamicContext::Ptr &context) const
{
    AtomicComparator::Ptr comp;

    if(m_comparator)
        comp = m_comparator;
    else
    {
        comp = fetchComparator(it1.type(),
                               it2.type(),
                               context);
    }

    Q_ASSERT_X(operatorID() == AtomicComparator::OperatorLessThanNaNLeast || operatorID() == AtomicComparator::OperatorLessThanNaNGreatest,
               Q_FUNC_INFO, "Only OperatorLessThan is currently supported for this function.");
    return comp->compare(it1, operatorID(), it2);
}

template <typename TSubClass, bool issueError,
          AtomicComparator::ComparisonType comparisonType, ReportContext::ErrorCode errorCode>
bool ComparisonPlatform<TSubClass, issueError, comparisonType, errorCode>::
compare(const Item &oand1,
        const Item &oand2,
        const AtomicComparator::Ptr &comp,
        const AtomicComparator::Operator op) const
{
    Q_ASSERT(oand1);
    Q_ASSERT(oand2);
    Q_ASSERT(comp);

    switch(op)
    {
        case AtomicComparator::OperatorEqual:
            return comp->equals(oand1, oand2);
        case AtomicComparator::OperatorNotEqual:
            return !comp->equals(oand1, oand2);
        case AtomicComparator::OperatorLessThanNaNLeast:
        case AtomicComparator::OperatorLessThanNaNGreatest:
        /* Fallthrough. */
        case AtomicComparator::OperatorLessThan:
            return comp->compare(oand1, op, oand2) == AtomicComparator::LessThan;
        case AtomicComparator::OperatorGreaterThan:
            return comp->compare(oand1, op, oand2) == AtomicComparator::GreaterThan;
        case AtomicComparator::OperatorLessOrEqual:
        {
            const AtomicComparator::ComparisonResult ret = comp->compare(oand1, op, oand2);
            return ret == AtomicComparator::LessThan || ret == AtomicComparator::Equal;
        }
        case(AtomicComparator::OperatorGreaterOrEqual):
        {
            const AtomicComparator::ComparisonResult ret = comp->compare(oand1, op, oand2);
            return ret == AtomicComparator::GreaterThan || ret == AtomicComparator::Equal;
        }
    }

    /* GCC unbarfer, this line should never be reached. */
    Q_ASSERT(false);
    return false;
}

template <typename TSubClass, bool issueError,
          AtomicComparator::ComparisonType comparisonType, ReportContext::ErrorCode errorCode>
AtomicComparator::Ptr ComparisonPlatform<TSubClass, issueError, comparisonType, errorCode>::
fetchComparator(const ItemType::Ptr &t1,
                const ItemType::Ptr &t2,
                const ReportContext::Ptr &context) const
{
    Q_ASSERT(t1);
    Q_ASSERT(t2);

    if(*BuiltinTypes::xsAnyAtomicType == *t1    ||
       *BuiltinTypes::xsAnyAtomicType == *t2    ||
       *BuiltinTypes::item == *t1               ||
       *BuiltinTypes::item == *t2               ||
       *BuiltinTypes::numeric == *t1            ||
       *BuiltinTypes::numeric == *t2            ||
       *CommonSequenceTypes::Empty == *t1       ||
       *CommonSequenceTypes::Empty == *t2)
    {
        /* The static type of(at least) one of the operands could not
         * be narrowed further, so we do the operator
         * lookup at runtime.
         */
        return AtomicComparator::Ptr();
    }

    const AtomicComparatorLocator::Ptr locator
        (static_cast<const AtomicType *>(t1.data())->comparatorLocator());

    if(!locator)
    {
        if(issueError)
        {
            context->error(QtXmlPatterns::tr("No comparisons can be done involving the type %1.")
                                            .arg(formatType(context->namePool(), t1)),
                                       errorCode, static_cast<const TSubClass *>(this)->actualReflection());
        }
        return AtomicComparator::Ptr();
    }

    const AtomicComparator::Ptr comp(static_cast<const AtomicType *>(t2.data())->accept(locator, operatorID(),
                                                                                       static_cast<const TSubClass *>(this)->actualReflection()));

    if(comp)
        return comp;
    else if(issueError)
    {
        context->error(QtXmlPatterns::tr("Operator %1 is not available between atomic values of type %2 and %3.")
                                        .arg(formatKeyword(AtomicComparator::displayName(operatorID(),
                                                                                         comparisonType)),
                                             formatType(context->namePool(), t1),
                                             formatType(context->namePool(), t2)),
                                   errorCode, static_cast<const TSubClass *>(this)->actualReflection());
    }

    return AtomicComparator::Ptr();
}

template <typename TSubClass, bool issueError,
          AtomicComparator::ComparisonType comparisonType, ReportContext::ErrorCode errorCode>
void ComparisonPlatform<TSubClass, issueError, comparisonType, errorCode>::
prepareComparison(const AtomicComparator::Ptr &c)
{
    m_comparator = c;
}

