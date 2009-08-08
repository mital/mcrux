#include "StdAfx.h"
#include <process.h>

#include "SocketJSObject.h"
#include <JavaScriptCore/JSContextRef.h>
#include <JavaScriptCore/JSRetainPtr.h>
#include <JavaScriptCore/JSStringRefCF.h>
#include <jscore/JSStringUtils.h>


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


const char * SocketJSObject::getName() const
{
	static string name = "socket";
	return name.c_str();
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
		{"connect", SocketJSObject::Connect, 0},
		{"disconnect", SocketJSObject::Disconnect, 0},
		{"send", SocketJSObject::Send, 0},
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
			bool bRet = saxObj->addEventListener(ctx, eventName, eventHandler);
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
			bool bRet = saxObj->removeEventListener(ctx, eventName, eventHandler);
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


bool SocketJSObject::Connect(const string & hostname, const string & port)
{
	socket.setConnectParams(hostname, port);
	_beginthread(StartSocketThread, 0, &socket);

//	socket.Connect(hostname, port);
	return true;
}

bool SocketJSObject::Disconnect()
{
	socket.Disconnect();
	return false;
}


bool SocketJSObject::Send(const string & data)
{
	return socket.Write(data);
}



bool SocketJSObject::addEventListener(JSContextRef ctx, const string & eventName, JSObjectRef eventHandler)
{
	eventMap[eventName] = eventHandler;
	JSValueProtect(ctx, eventMap[eventName]);
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


bool SocketJSObject::removeEventListener(JSContextRef ctx, const string & eventName, JSObjectRef eventHandler)
{
	map<string, JSObjectRef>::iterator iter = eventMap.find(eventName);
	if (iter != eventMap.end() && iter->second == eventHandler)
	{
		JSValueUnprotect(ctx, iter->second);
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


void SocketJSObject::onConnectComplete(const string & hostname, const string & port, bool bConnected)
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
			JSStringRef portStr = JSStringCreateWithUTF8CString("port");
			JSStringRef connected = JSStringCreateWithUTF8CString("connected");

			JSObjectSetProperty(ctx, eventObj, host, JSValueMakeString(ctx, hostName), 0, 0);
			JSObjectSetProperty(ctx, eventObj, portStr, JSValueMakeNumber(ctx, atof(port.c_str())), 0, 0);
			JSObjectSetProperty(ctx, eventObj, connected, JSValueMakeBoolean(ctx, bConnected), 0, 0);

			JSObjectRef handler = getEventListener(CONNECTED_EVENT_NAME);
			if(handler)
			{
				JSObjectCallAsFunction(ctx, handler, global, 1, &eventObj, 0);
			}
		}
	}
}