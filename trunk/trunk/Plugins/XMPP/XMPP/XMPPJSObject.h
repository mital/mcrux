#pragma once

#include <list>
using namespace std;

#include "mcrux/MCruxPlugin.h"


class XMPPJSObject :
	public MCruxPlugin
{
	static list<XMPPJSObject *> xmppObjects;

	static JSObjectRef ConstructorCallback(JSContextRef ctx,
		JSObjectRef constructor,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef* exception);

	static JSValueRef XMPPJSObject::Connect(JSContextRef ctx,
		JSObjectRef function,
		JSObjectRef thisObject,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef *exception);

	static JSValueRef XMPPJSObject::Disconnect(JSContextRef ctx,
		JSObjectRef function,
		JSObjectRef thisObject,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef *exception);

	static JSValueRef XMPPJSObject::Send(JSContextRef ctx,
		JSObjectRef function,
		JSObjectRef thisObject,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef *exception);


	static JSValueRef XMPPJSObject::dummyFunc(JSContextRef ctx,
		JSObjectRef function,
		JSObjectRef thisObject,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef *exception)
	{
		::MessageBoxA(0, "dummy called", "dummy", MB_OK);
		return JSValueMakeNull(ctx);
	}

	bool Connect(const string & server, unsigned short port);
	bool Disconnect();
	bool Send(const string & data);

public:

	XMPPJSObject(JSContextRef ctx,
		JSObjectRef constructor,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef* exception);

	XMPPJSObject();
	virtual ~XMPPJSObject();

	virtual string getName() const;
	virtual JSStaticFunction * getStaticFunctions() const;;
	virtual JSObjectCallAsConstructorCallback getConstructor() const;
	virtual JSStaticFunction * getJSObjectStaticFunctions() const;
};
