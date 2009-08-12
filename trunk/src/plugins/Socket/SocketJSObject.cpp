#include "StdAfx.h"
#include <process.h>

#include "SocketJSObject.h"
#include <jscore/JSStringUtils.h>


SocketJSObject::SocketJSObject(JSContextRef ctx, const bool hasConstructor)
: MJSCoreObject(ctx, "socket", hasConstructor),
  socket(this)
{
	if(!hasConstructor)
	{
		setProperty(ctx, "addEventListener", &SocketJSObject::addEventListener);
		setProperty(ctx, "removeEventListener", &SocketJSObject::removeEventListener);
		setProperty(ctx, "connect", &SocketJSObject::Connect);
		setProperty(ctx, "disconnect", &SocketJSObject::Disconnect);
		setProperty(ctx, "send", &SocketJSObject::Send);
	}
}


SocketJSObject::~SocketJSObject()
{
}


void SocketJSObject::construct(const MObjectArray& args, MObjectContainer& resultContainer)
{
	// check for required arguments before creating the object
	if(args.size() == 0)
	{
		JSContextRef context = MJSCoreObjectFactory::getJSContext();
		bool hasConstructor = false;
		resultContainer.set(new SocketJSObject(ctx, hasConstructor));
	}
	// TODO: throw exception.
}

void SocketJSObject::addEventListener(const MObjectArray& args, MObjectContainer& resultContainer)
{
	if(args.size() == 2) // eventName, eventHandlerFunction
	{
		//string eventName = getStringValueFrom(ctx, arguments[0]);
		//JSObjectRef eventHandler = JSValueToObject(ctx, arguments[1], exception);
		//bool bRet = true;//= saxObj->addEventListener(ctx, eventName, eventHandler);
		//resultContainer.set(MJSCoreObjectFactory::getMObject(bRet));
	}
	resultContainer.set(MJSCoreObjectFactory::getMObject(false));
}


void SocketJSObject::removeEventListener(const MObjectArray& args, MObjectContainer& resultContainer)
{
//	if(argumentCount == 2) // eventName, eventHandlerFunction
//	{
//		SocketJSObject * saxObj = (SocketJSObject*) JSObjectGetPrivate(thisObject);
//		if(saxObj)
//		{
//			string eventName = getStringValueFrom(ctx, arguments[0]);
//			JSObjectRef eventHandler = JSValueToObject(ctx, arguments[1], exception);
//			bool bRet = saxObj->removeEventListener(ctx, eventName, eventHandler);
//			return JSValueMakeBoolean(ctx, bRet);
//		}
//	}
//	return JSValueMakeBoolean(ctx, false);
}


void SocketJSObject::Connect(const MObjectArray& args, MObjectContainer& resultContainer)
{
//	if(argumentCount == 2) // server, port
//	{
//		string server = getStringValueFrom(ctx, arguments[0]);
//		string port = getStringValueFrom(ctx, arguments[1]);
//		SocketJSObject * socketObj = (SocketJSObject *) JSObjectGetPrivate(thisObject);
//		if(socketObj)
//		{
//			bool bResult = socketObj->Connect(server, port);
//			return JSValueMakeBoolean(ctx, bResult);
//		}
//	}
//	return JSValueMakeBoolean(ctx, false);
}

void SocketJSObject::Disconnect(const MObjectArray& args, MObjectContainer& resultContainer)
{
	::MessageBoxA(0, "SocketJSObject.Disconnect called.", "test", MB_OK);
//	if(argumentCount == 0) // No Arguments
//	{
//		SocketJSObject * socketObj = (SocketJSObject *) JSObjectGetPrivate(thisObject);
//		if(socketObj)
//		{
//			bool bResult = socketObj->Disconnect();
//			return JSValueMakeBoolean(ctx, bResult);
//		}
//	}
//	return JSValueMakeBoolean(ctx, false);
}


void SocketJSObject::Send(const MObjectArray& args, MObjectContainer& resultContainer)
{
//	bool bResult = false;
//	if(argumentCount == 1) // data
//	{
//		string data = getStringValueFrom(ctx, arguments[0]);
//		SocketJSObject * socketObj = (SocketJSObject *) JSObjectGetPrivate(thisObject);
//		if(socketObj)
//		{
//			bResult = socketObj->Send(data);
//		}
//	}
//	return JSValueMakeBoolean(ctx, bResult);
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
	//if (!MCruxPlugin::webView)
	//{
	//	::MessageBoxA(0, "endElementHandler webview not set", "saxparser", MB_OK);
	//	// TODO: return error
	//	return;
	//}
	//IWebFrame * frame;
	//HRESULT hr = MCruxPlugin::webView->mainFrame(&frame);
	//if(SUCCEEDED(hr))
	//{
	//	JSContextRef ctx = frame->globalContext();
	//	if(ctx)
	//	{
	//		JSObjectRef global = JSContextGetGlobalObject(ctx);
	//		JSObjectRef endElement = JSObjectMake(ctx, NULL, NULL);
	//		JSStringRef tagName = JSStringCreateWithUTF8CString((const char *)data.c_str());
	//		JSStringRef tag = JSStringCreateWithUTF8CString("data");
	//		JSObjectSetProperty(ctx, endElement, tag, JSValueMakeString(ctx, tagName), 0, 0);

	//		JSObjectRef handler = getEventListener(READ_DATA_EVENT_NAME);
	//		if(handler)
	//		{
	//			JSObjectCallAsFunction(ctx, handler, global, 1, &endElement, 0);
	//		}
	//	}
	//}
}


void SocketJSObject::onConnectComplete(const string & hostname, const string & port, bool bConnected)
{
	//if (!MCruxPlugin::webView)
	//{
	//	::MessageBoxA(0, "endElementHandler webview not set", "saxparser", MB_OK);
	//	// TODO: return error
	//	return;
	//}
	//IWebFrame * frame;
	//HRESULT hr = MCruxPlugin::webView->mainFrame(&frame);
	//if(SUCCEEDED(hr))
	//{
	//	JSContextRef ctx = frame->globalContext();
	//	if(ctx)
	//	{
	//		JSObjectRef global = JSContextGetGlobalObject(ctx);
	//		JSObjectRef eventObj = JSObjectMake(ctx, NULL, NULL);

	//		JSStringRef hostName = JSStringCreateWithUTF8CString((const char *)hostname.c_str());
	//		JSStringRef host = JSStringCreateWithUTF8CString("hostname");

	//		JSStringRef portName = JSStringCreateWithUTF8CString((const char *)port.c_str());
	//		JSStringRef portStr = JSStringCreateWithUTF8CString("port");
	//		JSStringRef connected = JSStringCreateWithUTF8CString("connected");

	//		JSObjectSetProperty(ctx, eventObj, host, JSValueMakeString(ctx, hostName), 0, 0);
	//		JSObjectSetProperty(ctx, eventObj, portStr, JSValueMakeNumber(ctx, atof(port.c_str())), 0, 0);
	//		JSObjectSetProperty(ctx, eventObj, connected, JSValueMakeBoolean(ctx, bConnected), 0, 0);

	//		JSObjectRef handler = getEventListener(CONNECTED_EVENT_NAME);
	//		if(handler)
	//		{
	//			JSObjectCallAsFunction(ctx, handler, global, 1, &eventObj, 0);
	//		}
	//	}
	//}
}