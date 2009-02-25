#include "StdAfx.h"
#include "SocketJSObject.h"
#include <JavaScriptCore/JSContextRef.h>
#include <JavaScriptCore/JSRetainPtr.h>
#include <JavaScriptCore/JSStringRefCF.h>
#include <JavaScriptCore/RetainPtr.h>
#include "mcrux/JSStringUtils.h"


list<SocketJSObject *> SocketJSObject::socketObjects;

SocketJSObject::SocketJSObject()
: stanzaHandler(NULL),
  ctx(NULL),
  socket(this)
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
						   : stanzaHandler(NULL),
						     ctx(NULL),
							 socket(this)
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


JSStaticFunction * SocketJSObject::getJSObjectStaticFunctions() const
{
	static JSStaticFunction JSDefaultFunctions[]
	= {
		{"Connect", SocketJSObject::Connect, 0},
		{"setStanzaHandler", SocketJSObject::setStanzaHandler, 0},
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
	::MessageBoxA(0, "SocketJSObject.Send called.", "test", MB_OK);
	if(argumentCount == 1) // data
	{
		string data = getStringValueFrom(ctx, arguments[0]);
		SocketJSObject * socketObj = (SocketJSObject *) JSObjectGetPrivate(thisObject);
		if(socketObj)
		{
			bool bResult = socketObj->Send(data);
			return JSValueMakeBoolean(ctx, bResult);
		}
	}
	return JSValueMakeBoolean(ctx, false);
}


JSValueRef SocketJSObject::setStanzaHandler(JSContextRef ctx,
										  JSObjectRef function,
										  JSObjectRef thisObject,
										  size_t argumentCount,
										  const JSValueRef arguments[],
										  JSValueRef *exception)
{
	::MessageBoxA(0, "setStanzaHandler called", "setStanzaHandler", MB_OK);
	if(argumentCount == 1) // handler function
	{
		SocketJSObject * socketObj = (SocketJSObject *) JSObjectGetPrivate(thisObject);
		if(socketObj)
		{
			bool bResult = socketObj->setStanzaHandler(ctx, JSValueToObject(ctx, arguments[0], exception));
			return JSValueMakeBoolean(ctx, bResult);
		}
	}
	return JSValueMakeBoolean(ctx, false);
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
	socket.Connect(hostname, port);
	return true;
}

bool SocketJSObject::setStanzaHandler(JSContextRef _ctx, JSObjectRef _stanzaHandler)
{
	ctx = _ctx;
	stanzaHandler = _stanzaHandler;
	return true;
}
bool SocketJSObject::Disconnect()
{
	//socket.disconnect();
	return false;
}


bool SocketJSObject::Send(const string & data)
{
	socket.Write(data);
	return false;
}


bool SocketJSObject::startTLS()
{
	return socket.startTLS();
}
/*

HRESULT StartTLS();
HRESULT StartSC();
HRESULT Disconnect();

*/

bool SocketJSObject::callStanzaHandler(const string &data)
{
	if(ctx && stanzaHandler)
	{
		JSValueRef dataValue[1];
		dataValue[0] = JSValueMakeString(ctx, JSStringCreateWithUTF8CString(data.c_str()));

		JSObjectRef global = JSContextGetGlobalObject(ctx);
		::JSObjectCallAsFunction(ctx,
			stanzaHandler,
			global,
			1,
			dataValue,
			0);
	}
	return true;
}
