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

#if ENABLE(INSPECTOR)

#include "JSInjectedScriptHost.h"

#include "InjectedScriptHost.h"
#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSInjectedScriptHost);

/* Hash table */

static const HashTableValue JSInjectedScriptHostTableValues[2] =
{
    { "constructor", DontEnum|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsInjectedScriptHostConstructor), (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSInjectedScriptHostTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSInjectedScriptHostTableValues, 0 };
#else
    { 2, 1, JSInjectedScriptHostTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSInjectedScriptHostConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSInjectedScriptHostConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSInjectedScriptHostConstructorTableValues, 0 };
#else
    { 1, 0, JSInjectedScriptHostConstructorTableValues, 0 };
#endif

class JSInjectedScriptHostConstructor : public DOMConstructorObject {
public:
    JSInjectedScriptHostConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
        : DOMConstructorObject(JSInjectedScriptHostConstructor::createStructure(globalObject->objectPrototype()), globalObject)
    {
        putDirect(exec->propertyNames().prototype, JSInjectedScriptHostPrototype::self(exec, globalObject), None);
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

const ClassInfo JSInjectedScriptHostConstructor::s_info = { "InjectedScriptHostConstructor", 0, &JSInjectedScriptHostConstructorTable, 0 };

bool JSInjectedScriptHostConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSInjectedScriptHostConstructor, DOMObject>(exec, &JSInjectedScriptHostConstructorTable, this, propertyName, slot);
}

bool JSInjectedScriptHostConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSInjectedScriptHostConstructor, DOMObject>(exec, &JSInjectedScriptHostConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */

static const HashTableValue JSInjectedScriptHostPrototypeTableValues[16] =
{
    { "clearConsoleMessages", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsInjectedScriptHostPrototypeFunctionClearConsoleMessages), (intptr_t)0 },
    { "copyText", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsInjectedScriptHostPrototypeFunctionCopyText), (intptr_t)1 },
    { "nodeForId", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsInjectedScriptHostPrototypeFunctionNodeForId), (intptr_t)1 },
    { "pushNodePathToFrontend", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsInjectedScriptHostPrototypeFunctionPushNodePathToFrontend), (intptr_t)3 },
    { "addNodesToSearchResult", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsInjectedScriptHostPrototypeFunctionAddNodesToSearchResult), (intptr_t)1 },
    { "pushNodeByPathToFrontend", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsInjectedScriptHostPrototypeFunctionPushNodeByPathToFrontend), (intptr_t)1 },
    { "currentCallFrame", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsInjectedScriptHostPrototypeFunctionCurrentCallFrame), (intptr_t)0 },
    { "isActivation", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsInjectedScriptHostPrototypeFunctionIsActivation), (intptr_t)1 },
    { "databaseForId", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsInjectedScriptHostPrototypeFunctionDatabaseForId), (intptr_t)1 },
    { "selectDatabase", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsInjectedScriptHostPrototypeFunctionSelectDatabase), (intptr_t)1 },
    { "selectDOMStorage", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsInjectedScriptHostPrototypeFunctionSelectDOMStorage), (intptr_t)1 },
    { "didCreateWorker", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsInjectedScriptHostPrototypeFunctionDidCreateWorker), (intptr_t)3 },
    { "didDestroyWorker", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsInjectedScriptHostPrototypeFunctionDidDestroyWorker), (intptr_t)1 },
    { "nextWorkerId", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsInjectedScriptHostPrototypeFunctionNextWorkerId), (intptr_t)0 },
    { "reportDidDispatchOnInjectedScript", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsInjectedScriptHostPrototypeFunctionReportDidDispatchOnInjectedScript), (intptr_t)3 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSInjectedScriptHostPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 127, JSInjectedScriptHostPrototypeTableValues, 0 };
#else
    { 34, 31, JSInjectedScriptHostPrototypeTableValues, 0 };
#endif

const ClassInfo JSInjectedScriptHostPrototype::s_info = { "InjectedScriptHostPrototype", 0, &JSInjectedScriptHostPrototypeTable, 0 };

JSObject* JSInjectedScriptHostPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSInjectedScriptHost>(exec, globalObject);
}

bool JSInjectedScriptHostPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSInjectedScriptHostPrototypeTable, this, propertyName, slot);
}

bool JSInjectedScriptHostPrototype::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticFunctionDescriptor<JSObject>(exec, &JSInjectedScriptHostPrototypeTable, this, propertyName, descriptor);
}

const ClassInfo JSInjectedScriptHost::s_info = { "InjectedScriptHost", 0, &JSInjectedScriptHostTable, 0 };

JSInjectedScriptHost::JSInjectedScriptHost(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<InjectedScriptHost> impl)
    : DOMObjectWithGlobalPointer(structure, globalObject)
    , m_impl(impl)
{
}

JSInjectedScriptHost::~JSInjectedScriptHost()
{
    forgetDOMObject(this, impl());
}

JSObject* JSInjectedScriptHost::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSInjectedScriptHostPrototype(JSInjectedScriptHostPrototype::createStructure(globalObject->objectPrototype()));
}

bool JSInjectedScriptHost::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSInjectedScriptHost, Base>(exec, &JSInjectedScriptHostTable, this, propertyName, slot);
}

bool JSInjectedScriptHost::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSInjectedScriptHost, Base>(exec, &JSInjectedScriptHostTable, this, propertyName, descriptor);
}

JSValue jsInjectedScriptHostConstructor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSInjectedScriptHost* domObject = static_cast<JSInjectedScriptHost*>(asObject(slotBase));
    return JSInjectedScriptHost::getConstructor(exec, domObject->globalObject());
}
JSValue JSInjectedScriptHost::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSInjectedScriptHostConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

JSValue JSC_HOST_CALL jsInjectedScriptHostPrototypeFunctionClearConsoleMessages(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSInjectedScriptHost::s_info))
        return throwError(exec, TypeError);
    JSInjectedScriptHost* castedThisObj = static_cast<JSInjectedScriptHost*>(asObject(thisValue));
    InjectedScriptHost* imp = static_cast<InjectedScriptHost*>(castedThisObj->impl());

    imp->clearConsoleMessages();
    return jsUndefined();
}

JSValue JSC_HOST_CALL jsInjectedScriptHostPrototypeFunctionCopyText(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSInjectedScriptHost::s_info))
        return throwError(exec, TypeError);
    JSInjectedScriptHost* castedThisObj = static_cast<JSInjectedScriptHost*>(asObject(thisValue));
    InjectedScriptHost* imp = static_cast<InjectedScriptHost*>(castedThisObj->impl());
    const UString& text = args.at(0).toString(exec);

    imp->copyText(text);
    return jsUndefined();
}

JSValue JSC_HOST_CALL jsInjectedScriptHostPrototypeFunctionNodeForId(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSInjectedScriptHost::s_info))
        return throwError(exec, TypeError);
    JSInjectedScriptHost* castedThisObj = static_cast<JSInjectedScriptHost*>(asObject(thisValue));
    return castedThisObj->nodeForId(exec, args);
}

JSValue JSC_HOST_CALL jsInjectedScriptHostPrototypeFunctionPushNodePathToFrontend(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSInjectedScriptHost::s_info))
        return throwError(exec, TypeError);
    JSInjectedScriptHost* castedThisObj = static_cast<JSInjectedScriptHost*>(asObject(thisValue));
    return castedThisObj->pushNodePathToFrontend(exec, args);
}

JSValue JSC_HOST_CALL jsInjectedScriptHostPrototypeFunctionAddNodesToSearchResult(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSInjectedScriptHost::s_info))
        return throwError(exec, TypeError);
    JSInjectedScriptHost* castedThisObj = static_cast<JSInjectedScriptHost*>(asObject(thisValue));
    InjectedScriptHost* imp = static_cast<InjectedScriptHost*>(castedThisObj->impl());
    const UString& nodeIds = args.at(0).toString(exec);

    imp->addNodesToSearchResult(nodeIds);
    return jsUndefined();
}

JSValue JSC_HOST_CALL jsInjectedScriptHostPrototypeFunctionPushNodeByPathToFrontend(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSInjectedScriptHost::s_info))
        return throwError(exec, TypeError);
    JSInjectedScriptHost* castedThisObj = static_cast<JSInjectedScriptHost*>(asObject(thisValue));
    InjectedScriptHost* imp = static_cast<InjectedScriptHost*>(castedThisObj->impl());
    const UString& path = args.at(0).toString(exec);


    JSC::JSValue result = jsNumber(exec, imp->pushNodeByPathToFrontend(path));
    return result;
}

JSValue JSC_HOST_CALL jsInjectedScriptHostPrototypeFunctionCurrentCallFrame(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSInjectedScriptHost::s_info))
        return throwError(exec, TypeError);
    JSInjectedScriptHost* castedThisObj = static_cast<JSInjectedScriptHost*>(asObject(thisValue));
    return castedThisObj->currentCallFrame(exec, args);
}

JSValue JSC_HOST_CALL jsInjectedScriptHostPrototypeFunctionIsActivation(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSInjectedScriptHost::s_info))
        return throwError(exec, TypeError);
    JSInjectedScriptHost* castedThisObj = static_cast<JSInjectedScriptHost*>(asObject(thisValue));
    return castedThisObj->isActivation(exec, args);
}

JSValue JSC_HOST_CALL jsInjectedScriptHostPrototypeFunctionDatabaseForId(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSInjectedScriptHost::s_info))
        return throwError(exec, TypeError);
    JSInjectedScriptHost* castedThisObj = static_cast<JSInjectedScriptHost*>(asObject(thisValue));
    return castedThisObj->databaseForId(exec, args);
}

JSValue JSC_HOST_CALL jsInjectedScriptHostPrototypeFunctionSelectDatabase(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSInjectedScriptHost::s_info))
        return throwError(exec, TypeError);
    JSInjectedScriptHost* castedThisObj = static_cast<JSInjectedScriptHost*>(asObject(thisValue));
    return castedThisObj->selectDatabase(exec, args);
}

JSValue JSC_HOST_CALL jsInjectedScriptHostPrototypeFunctionSelectDOMStorage(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSInjectedScriptHost::s_info))
        return throwError(exec, TypeError);
    JSInjectedScriptHost* castedThisObj = static_cast<JSInjectedScriptHost*>(asObject(thisValue));
    return castedThisObj->selectDOMStorage(exec, args);
}

JSValue JSC_HOST_CALL jsInjectedScriptHostPrototypeFunctionDidCreateWorker(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSInjectedScriptHost::s_info))
        return throwError(exec, TypeError);
    JSInjectedScriptHost* castedThisObj = static_cast<JSInjectedScriptHost*>(asObject(thisValue));
    InjectedScriptHost* imp = static_cast<InjectedScriptHost*>(castedThisObj->impl());
    int id = args.at(0).toInt32(exec);
    const UString& url = args.at(1).toString(exec);
    bool isFakeWorker = args.at(2).toBoolean(exec);

    imp->didCreateWorker(id, url, isFakeWorker);
    return jsUndefined();
}

JSValue JSC_HOST_CALL jsInjectedScriptHostPrototypeFunctionDidDestroyWorker(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSInjectedScriptHost::s_info))
        return throwError(exec, TypeError);
    JSInjectedScriptHost* castedThisObj = static_cast<JSInjectedScriptHost*>(asObject(thisValue));
    InjectedScriptHost* imp = static_cast<InjectedScriptHost*>(castedThisObj->impl());
    int id = args.at(0).toInt32(exec);

    imp->didDestroyWorker(id);
    return jsUndefined();
}

JSValue JSC_HOST_CALL jsInjectedScriptHostPrototypeFunctionNextWorkerId(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSInjectedScriptHost::s_info))
        return throwError(exec, TypeError);
    JSInjectedScriptHost* castedThisObj = static_cast<JSInjectedScriptHost*>(asObject(thisValue));
    InjectedScriptHost* imp = static_cast<InjectedScriptHost*>(castedThisObj->impl());


    JSC::JSValue result = jsNumber(exec, imp->nextWorkerId());
    return result;
}

JSValue JSC_HOST_CALL jsInjectedScriptHostPrototypeFunctionReportDidDispatchOnInjectedScript(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSInjectedScriptHost::s_info))
        return throwError(exec, TypeError);
    JSInjectedScriptHost* castedThisObj = static_cast<JSInjectedScriptHost*>(asObject(thisValue));
    return castedThisObj->reportDidDispatchOnInjectedScript(exec, args);
}

JSC::JSValue toJS(JSC::ExecState* exec, JSDOMGlobalObject* globalObject, InjectedScriptHost* object)
{
    return getDOMObjectWrapper<JSInjectedScriptHost>(exec, globalObject, object);
}
InjectedScriptHost* toInjectedScriptHost(JSC::JSValue value)
{
    return value.inherits(&JSInjectedScriptHost::s_info) ? static_cast<JSInjectedScriptHost*>(asObject(value))->impl() : 0;
}

}

#endif // ENABLE(INSPECTOR)
