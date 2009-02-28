#include "StdAfx.h"
#include <process.h>

#include "SocketJSObject.h"
#include <JavaScriptCore/JSContextRef.h>
#include <JavaScriptCore/JSRetainPtr.h>
#include <JavaScriptCore/JSStringRefCF.h>
#include <JavaScriptCore/RetainPtr.h>
#include "JSStringUtils.h"

using namespace JSStringUtils;


list<SocketJSObject *> SocketJSObject::socketObjects;

SocketJSObject::SocketJSObject()
: socket(this)
{
}


SocketJSObject::~SocketJSObject()
{
}


SocketJSObject::SocketJSObject(JSContextRef ctx,
						   JSObjectRef constructor,
						   size_t argumentCount,
						   const JSValueRef arguments[],
						   JSValueRef* exception)
						   : socket(this)
{
}


string SocketJSObject::getName() const
{
	static string name = "socket";
	return name;
}

JSObjectCallAsConstructorCallback SocketJSObject::getConstructor() const
{
	return SocketJSObject::ConstructorCallback;
}



JSStaticFunction * SocketJSObject::getStaticFunctions() const
{
	static JSStaticFunction JSDefaultFunctions[]
	= {
		{0, 0, 0}
	};
	return JSDefaultFunctions;
}


JSStaticFunction * SocketJSObject::getJSObjectFunctions() const
{
	static JSStaticFunction JSDefaultFunctions[]
	= {
		{"addEventListener", SocketJSObject::addEventListener, 0},
		{"removeEventListener", SocketJSObject::removeEventListener, 0},
		{"Connect", SocketJSObject::Connect, 0},
		{"Disconnect", SocketJSObject::Disconnect, 0},
		{"Send", SocketJSObject::Send, 0},
		{"startTLS", SocketJSObject::startTLS, 0},
		{0, 0, 0}
	};
	return JSDefaultFunctions;
}


JSObjectRef SocketJSObject::ConstructorCallback(JSContextRef ctx,
											  JSObjectRef constructor,
											  size_t argumentCount,
											  const JSValueRef arguments[],
											  JSValueRef* exception)
{
	::MessageBoxA(0, "socket constructor called", "test", MB_OK);
	// check for required arguments before creating the object
	if(argumentCount == 0)
	{
		SocketJSObject * newObj
			= new SocketJSObject(ctx, constructor, argumentCount, arguments, exception);
		socketObjects.push_back(newObj);
		return newObj->createJSObject(ctx);
	}
	// TODO: throw exception.
	return JSValueToObject(ctx, JSValueMakeUndefined(ctx), exception);
}


JSValueRef SocketJSObject::addEventListener(JSContextRef ctx,
													JSObjectRef function,
													JSObjectRef thisObject,
													size_t argumentCount,
													const JSValueRef arguments[],
													JSValueRef *exception)
{
	if(argumentCount == 2) // eventName, eventHandlerFunction
	{
		SocketJSObject * saxObj = (SocketJSObject*) JSObjectGetPrivate(thisObject);
		if(saxObj)
		{
			string eventName = getStringValueFrom(ctx, arguments[0]);
			JSObjectRef eventHandler = JSValueToObject(ctx, arguments[1], exception);
			bool bRet = saxObj->addEventListener(eventName, eventHandler);
			return JSValueMakeBoolean(ctx, bRet);
		}
	}
	return JSValueMakeBoolean(ctx, false);
}


JSValueRef SocketJSObject::removeEventListener(JSContextRef ctx,
													JSObjectRef function,
													JSObjectRef thisObject,
													size_t argumentCount,
													const JSValueRef arguments[],
													JSValueRef *exception)
{
	if(argumentCount == 2) // eventName, eventHandlerFunction
	{
		SocketJSObject * saxObj = (SocketJSObject*) JSObjectGetPrivate(thisObject);
		if(saxObj)
		{
			string eventName = getStringValueFrom(ctx, arguments[0]);
			JSObjectRef eventHandler = JSValueToObject(ctx, arguments[1], exception);
			bool bRet = saxObj->removeEventListener(eventName, eventHandler);
			return JSValueMakeBoolean(ctx, bRet);
		}
	}
	return JSValueMakeBoolean(ctx, false);
}


JSValueRef SocketJSObject::Connect(JSContextRef ctx,
								 JSObjectRef function,
								 JSObjectRef thisObject,
								 size_t argumentCount,
								 const JSValueRef arguments[],
								 JSValueRef *exception)
{
	::MessageBoxA(0, "SocketJSObject.Connect called.", "test", MB_OK);
	if(argumentCount == 2) // server, port
	{
		string server = getStringValueFrom(ctx, arguments[0]);
		string port = getStringValueFrom(ctx, arguments[1]);
		SocketJSObject * socketObj = (SocketJSObject *) JSObjectGetPrivate(thisObject);
		if(socketObj)
		{
			bool bResult = socketObj->Connect(server, port);
			return JSValueMakeBoolean(ctx, bResult);
		}
	}
	return JSValueMakeBoolean(ctx, false);
}


JSValueRef SocketJSObject::Disconnect(JSContextRef ctx,
									JSObjectRef function,
									JSObjectRef thisObject,
									size_t argumentCount,
									const JSValueRef arguments[],
									JSValueRef *exception)
{
	::MessageBoxA(0, "SocketJSObject.Disconnect called.", "test", MB_OK);
	if(argumentCount == 0) // No Arguments
	{
		SocketJSObject * socketObj = (SocketJSObject *) JSObjectGetPrivate(thisObject);
		if(socketObj)
		{
			bool bResult = socketObj->Disconnect();
			return JSValueMakeBoolean(ctx, bResult);
		}
	}
	return JSValueMakeBoolean(ctx, false);
}


JSValueRef SocketJSObject::Send(JSContextRef ctx,
							  JSObjectRef function,
							  JSObjectRef thisObject,
							  size_t argumentCount,
							  const JSValueRef arguments[],
							  JSValueRef *exception)
{
	bool bResult = false;
	::MessageBoxA(0, "SocketJSObject.Send called.", "test", MB_OK);
	if(argumentCount == 1) // data
	{
		string data = getStringValueFrom(ctx, arguments[0]);
		SocketJSObject * socketObj = (SocketJSObject *) JSObjectGetPrivate(thisObject);
		if(socketObj)
		{
			bResult = socketObj->Send(data);
		}
	}
	return JSValueMakeBoolean(ctx, bResult);
}


JSValueRef SocketJSObject::startTLS(JSContextRef ctx,
							  JSObjectRef function,
							  JSObjectRef thisObject,
							  size_t argumentCount,
							  const JSValueRef arguments[],
							  JSValueRef *exception)
{
	::MessageBoxA(0, "SocketJSObject.startTLS called.", "test", MB_OK);
	if(argumentCount == 0) // data
	{
		SocketJSObject * socketObj = (SocketJSObject *) JSObjectGetPrivate(thisObject);
		if(socketObj)
		{
			bool bResult = socketObj->startTLS();
			return JSValueMakeBoolean(ctx, bResult);
		}
	}
	return JSValueMakeBoolean(ctx, false);
}


bool SocketJSObject::Connect(const string & hostname, const string & port)
{
	socket.setConnectParams(hostname, port);
	_beginthread(StartSocketThread, 0, &socket);

//	socket.Connect(hostname, port);
	return true;
}

bool SocketJSObject::Disconnect()
{
	//socket.disconnect();
	return false;
}


bool SocketJSObject::Send(const string & data)
{
	return socket.Write(data);
}


bool SocketJSObject::startTLS()
{
	return socket.startTLS();
}


bool SocketJSObject::addEventListener(const string & eventName, JSObjectRef eventHandler)
{
	eventMap[eventName] = eventHandler;
	return true;
}


JSObjectRef SocketJSObject::getEventListener(const string & eventName) const
{
	map<string, JSObjectRef>::const_iterator iter = eventMap.find(eventName);
	if (iter != eventMap.end())
	{
		return iter->second;
	}
	return NULL;
}


bool SocketJSObject::removeEventListener(const string & eventName, JSObjectRef eventHandler)
{
	map<string, JSObjectRef>::iterator iter = eventMap.find(eventName);
	if (iter != eventMap.end() && iter->second == eventHandler)
	{
		eventMap.erase(iter);
		return true;
	}
	return false;
}


void SocketJSObject::handleReadData(const string &data)
{
	if (!MCruxPlugin::webView)
	{
		::MessageBoxA(0, "endElementHandler webview not set", "saxparser", MB_OK);
		// TODO: return error
		return;
	}
	IWebFrame * frame;
	HRESULT hr = MCruxPlugin::webView->mainFrame(&frame);
	if(SUCCEEDED(hr))
	{
		JSContextRef ctx = frame->globalContext();
		if(ctx)
		{
			JSObjectRef global = JSContextGetGlobalObject(ctx);
			JSObjectRef endElement = JSObjectMake(ctx, NULL, NULL);
			JSStringRef tagName = JSStringCreateWithUTF8CString((const char *)data.c_str());
			JSStringRef tag = JSStringCreateWithUTF8CString("data");
			JSObjectSetProperty(ctx, endElement, tag, JSValueMakeString(ctx, tagName), 0, 0);

			JSObjectRef handler = getEventListener(READ_DATA_EVENT_NAME);
			if(handler)
			{
				JSObjectCallAsFunction(ctx, handler, global, 1, &endElement, 0);
			}
		}
	}
}


void SocketJSObject::onConnected(const string & hostname, const string & port)
{
	if (!MCruxPlugin::webView)
	{
		::MessageBoxA(0, "endElementHandler webview not set", "saxparser", MB_OK);
		// TODO: return error
		return;
	}
	IWebFrame * frame;
	HRESULT hr = MCruxPlugin::webView->mainFrame(&frame);
	if(SUCCEEDED(hr))
	{
		JSContextRef ctx = frame->globalContext();
		if(ctx)
		{
			JSObjectRef global = JSContextGetGlobalObject(ctx);
			JSObjectRef eventObj = JSObjectMake(ctx, NULL, NULL);

			JSStringRef hostName = JSStringCreateWithUTF8CString((const char *)hostname.c_str());
			JSStringRef host = JSStringCreateWithUTF8CString("hostname");

			JSStringRef portName = JSStringCreateWithUTF8CString((const char *)port.c_str());
			JSStringRef port = JSStringCreateWithUTF8CString("port");

			JSObjectSetProperty(ctx, eventObj, host, JSValueMakeString(ctx, hostName), 0, 0);
			JSObjectSetProperty(ctx, eventObj, port, JSValueMakeString(ctx, portName), 0, 0);

			JSObjectRef handler = getEventListener(CONNECTED_EVENT_NAME);
			if(handler)
			{
				JSObjectCallAsFunction(ctx, handler, global, 1, &eventObj, 0);
			}
		}
	}
}