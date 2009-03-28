#pragma once

#include <map>
#include <list>
#include <string>
using namespace std;

#define CONNECTED_EVENT_NAME "onConnectComplete"
#define READ_DATA_EVENT_NAME "onRead"

#include "mcrux/MCruxPlugin.h"

#include "SocketObj.h"


class SocketJSObject :
	public MCruxPlugin
{
	map<string, JSObjectRef> eventMap;
	Socket socket;

	static list<SocketJSObject *> socketObjects;

	static JSObjectRef ConstructorCallback(JSContextRef ctx,
		JSObjectRef constructor,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef* exception);

	static JSValueRef addEventListener(JSContextRef ctx,
		JSObjectRef function,
		JSObjectRef thisObject,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef *exception);

	static JSValueRef removeEventListener(JSContextRef ctx,
		JSObjectRef function,
		JSObjectRef thisObject,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef *exception);

	static JSValueRef Connect(JSContextRef ctx,
		JSObjectRef function,
		JSObjectRef thisObject,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef *exception);

	static JSValueRef Disconnect(JSContextRef ctx,
		JSObjectRef function,
		JSObjectRef thisObject,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef *exception);

	static JSValueRef Send(JSContextRef ctx,
		JSObjectRef function,
		JSObjectRef thisObject,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef *exception);

	// event listener related methods
	bool addEventListener(const string & eventName, JSObjectRef eventHandler);
	bool removeEventListener(const string & eventName, JSObjectRef eventHandler);
	JSObjectRef getEventListener(const string & eventName) const;

	bool Connect(const string & hostname, const string & port);
	bool Disconnect();
	bool Send(const string & data);

public:

	SocketJSObject(JSContextRef ctx,
		JSObjectRef constructor,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef* exception);

	SocketJSObject();
	virtual ~SocketJSObject();

	virtual const char * getName() const;
	virtual JSStaticFunction * getStaticFunctions() const;;
	virtual JSObjectCallAsConstructorCallback getConstructor() const;
	virtual JSStaticFunction * getJSObjectFunctions() const;

	void handleReadData(const string &data);
	void onConnectComplete(const string & hostname, const string & port, bool bConnected);
};
