#pragma once

#include <list>
using namespace std;

#include "mcrux/MCruxPlugin.h"

#include "Socket.h"


class XMPPJSObject :
	public MCruxPlugin
{
	JSObjectRef stanzaHandler;
	JSContextRef ctx;
	Socket socket;
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


	static JSValueRef setStanzaHandler(JSContextRef ctx,
		JSObjectRef function,
		JSObjectRef thisObject,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef *exception);

	bool Connect(const string & hostname, const string & port);
	bool setStanzaHandler(JSContextRef _sctx, JSObjectRef _stanzaHandler);
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

	bool callStanzaHandler(const string &data);
};
