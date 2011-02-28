/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"
#include "JSHTMLFontElement.h"

#include "HTMLFontElement.h"
#include "KURL.h"
#include <runtime/JSString.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSHTMLFontElement);

/* Hash table */

static const HashTableValue JSHTMLFontElementTableValues[5] =
{
    { "color", DontDelete, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsHTMLFontElementColor), (intptr_t)setJSHTMLFontElementColor },
    { "face", DontDelete, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsHTMLFontElementFace), (intptr_t)setJSHTMLFontElementFace },
    { "size", DontDelete, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsHTMLFontElementSize), (intptr_t)setJSHTMLFontElementSize },
    { "constructor", DontEnum|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsHTMLFontElementConstructor), (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSHTMLFontElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSHTMLFontElementTableValues, 0 };
#else
    { 9, 7, JSHTMLFontElementTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSHTMLFontElementConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSHTMLFontElementConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLFontElementConstructorTableValues, 0 };
#else
    { 1, 0, JSHTMLFontElementConstructorTableValues, 0 };
#endif

class JSHTMLFontElementConstructor : public DOMConstructorObject {
public:
    JSHTMLFontElementConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
        : DOMConstructorObject(JSHTMLFontElementConstructor::createStructure(globalObject->objectPrototype()), globalObject)
    {
        putDirect(exec->propertyNames().prototype, JSHTMLFontElementPrototype::self(exec, globalObject), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual bool getOwnPropertyDescriptor(ExecState*, const Identifier&, PropertyDescriptor&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, StructureFlags), AnonymousSlotCount); 
    }
    
protected:
    static const unsigned StructureFlags = OverridesGetOwnPropertySlot | ImplementsHasInstance | DOMConstructorObject::StructureFlags;
};

const ClassInfo JSHTMLFontElementConstructor::s_info = { "HTMLFontElementConstructor", 0, &JSHTMLFontElementConstructorTable, 0 };

bool JSHTMLFontElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLFontElementConstructor, DOMObject>(exec, &JSHTMLFontElementConstructorTable, this, propertyName, slot);
}

bool JSHTMLFontElementConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSHTMLFontElementConstructor, DOMObject>(exec, &JSHTMLFontElementConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */

static const HashTableValue JSHTMLFontElementPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSHTMLFontElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLFontElementPrototypeTableValues, 0 };
#else
    { 1, 0, JSHTMLFontElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSHTMLFontElementPrototype::s_info = { "HTMLFontElementPrototype", 0, &JSHTMLFontElementPrototypeTable, 0 };

JSObject* JSHTMLFontElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSHTMLFontElement>(exec, globalObject);
}

const ClassInfo JSHTMLFontElement::s_info = { "HTMLFontElement", &JSHTMLElement::s_info, &JSHTMLFontElementTable, 0 };

JSHTMLFontElement::JSHTMLFontElement(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<HTMLFontElement> impl)
    : JSHTMLElement(structure, globalObject, impl)
{
}

JSObject* JSHTMLFontElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSHTMLFontElementPrototype(JSHTMLFontElementPrototype::createStructure(JSHTMLElementPrototype::self(exec, globalObject)));
}

bool JSHTMLFontElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLFontElement, Base>(exec, &JSHTMLFontElementTable, this, propertyName, slot);
}

bool JSHTMLFontElement::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSHTMLFontElement, Base>(exec, &JSHTMLFontElementTable, this, propertyName, descriptor);
}

JSValue jsHTMLFontElementColor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSHTMLFontElement* castedThis = static_cast<JSHTMLFontElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    HTMLFontElement* imp = static_cast<HTMLFontElement*>(castedThis->impl());
    JSValue result = jsString(exec, imp->color());
    return result;
}

JSValue jsHTMLFontElementFace(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSHTMLFontElement* castedThis = static_cast<JSHTMLFontElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    HTMLFontElement* imp = static_cast<HTMLFontElement*>(castedThis->impl());
    JSValue result = jsString(exec, imp->face());
    return result;
}

JSValue jsHTMLFontElementSize(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSHTMLFontElement* castedThis = static_cast<JSHTMLFontElement*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    HTMLFontElement* imp = static_cast<HTMLFontElement*>(castedThis->impl());
    JSValue result = jsString(exec, imp->size());
    return result;
}

JSValue jsHTMLFontElementConstructor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSHTMLFontElement* domObject = static_cast<JSHTMLFontElement*>(asObject(slotBase));
    return JSHTMLFontElement::getConstructor(exec, domObject->globalObject());
}
void JSHTMLFontElement::put(ExecState* exec, const Identifier& propertyName, JSValue value, PutPropertySlot& slot)
{
    lookupPut<JSHTMLFontElement, Base>(exec, propertyName, value, &JSHTMLFontElementTable, this, slot);
}

void setJSHTMLFontElementColor(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSHTMLFontElement* castedThisObj = static_cast<JSHTMLFontElement*>(thisObject);
    HTMLFontElement* imp = static_cast<HTMLFontElement*>(castedThisObj->impl());
    imp->setColor(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLFontElementFace(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSHTMLFontElement* castedThisObj = static_cast<JSHTMLFontElement*>(thisObject);
    HTMLFontElement* imp = static_cast<HTMLFontElement*>(castedThisObj->impl());
    imp->setFace(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLFontElementSize(ExecState* exec, JSObject* thisObject, JSValue value)
{
    JSHTMLFontElement* castedThisObj = static_cast<JSHTMLFontElement*>(thisObject);
    HTMLFontElement* imp = static_cast<HTMLFontElement*>(castedThisObj->impl());
    imp->setSize(valueToStringWithNullCheck(exec, value));
}

JSValue JSHTMLFontElement::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSHTMLFontElementConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}


}
