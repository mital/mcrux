#include "StdAfx.h"
#include "XMPPJSObject.h"
#include <JavaScriptCore/JSContextRef.h>
#include <JavaScriptCore/JSRetainPtr.h>
#include <JavaScriptCore/JSStringRefCF.h>
#include <JavaScriptCore/RetainPtr.h>
#include "JSStringUtils.h"


list<XMPPJSObject *> XMPPJSObject::xmppObjects;

XMPPJSObject::XMPPJSObject()
: stanzaHandler(NULL),
  ctx(NULL),
  socket(this)
{
}


XMPPJSObject::~XMPPJSObject()
{
}


XMPPJSObject::XMPPJSObject(JSContextRef ctx,
						   JSObjectRef constructor,
						   size_t argumentCount,
						   const JSValueRef arguments[],
						   JSValueRef* exception)
						   : stanzaHandler(NULL),
						     ctx(NULL),
							 socket(this)
{
}


string XMPPJSObject::getName() const
{
	static string name = "xmpp";
	return name;
}

JSObjectCallAsConstructorCallback XMPPJSObject::getConstructor() const
{
	return XMPPJSObject::ConstructorCallback;
}



JSStaticFunction * XMPPJSObject::getStaticFunctions() const
{
	static JSStaticFunction JSDefaultFunctions[]
	= {
		{0, 0, 0}
	};
	return JSDefaultFunctions;
}


JSStaticFunction * XMPPJSObject::getJSObjectStaticFunctions() const
{
	static JSStaticFunction JSDefaultFunctions[]
	= {
		{"Connect", XMPPJSObject::Connect, 0},
		{"setStanzaHandler", XMPPJSObject::setStanzaHandler, 0},
		{"Disconnect", XMPPJSObject::Disconnect, 0},
		{"Send", XMPPJSObject::Send, 0},
		{0, 0, 0}
	};
	return JSDefaultFunctions;
}


JSObjectRef XMPPJSObject::ConstructorCallback(JSContextRef ctx,
											  JSObjectRef constructor,
											  size_t argumentCount,
											  const JSValueRef arguments[],
											  JSValueRef* exception)
{
	::MessageBoxA(0, "xmpp constructor called", "test", MB_OK);
	// check for required arguments before creating the object
	if(argumentCount == 0)
	{
		XMPPJSObject * newObj
			= new XMPPJSObject(ctx, constructor, argumentCount, arguments, exception);
		xmppObjects.push_back(newObj);
		return newObj->createJSObject(ctx);
	}
	// TODO: throw exception.
	return JSValueToObject(ctx, JSValueMakeUndefined(ctx), exception);
}


JSValueRef XMPPJSObject::Connect(JSContextRef ctx,
								 JSObjectRef function,
								 JSObjectRef thisObject,
								 size_t argumentCount,
								 const JSValueRef arguments[],
								 JSValueRef *exception)
{
	::MessageBoxA(0, "XMPPJSObject.Connect called.", "test", MB_OK);
	if(argumentCount == 2) // server, port
	{
		string server = JSStringUtils::getStringValueFrom(ctx, arguments[0]);
		string port = JSStringUtils::getStringValueFrom(ctx, arguments[1]);
		XMPPJSObject * xmppObj = (XMPPJSObject *) JSObjectGetPrivate(thisObject);
		if(xmppObj)
		{
			bool bResult = xmppObj->Connect(server, port);
			return JSValueMakeBoolean(ctx, bResult);
		}
	}
	return JSValueMakeBoolean(ctx, false);
}


JSValueRef XMPPJSObject::Disconnect(JSContextRef ctx,
									JSObjectRef function,
									JSObjectRef thisObject,
									size_t argumentCount,
									const JSValueRef arguments[],
									JSValueRef *exception)
{
	::MessageBoxA(0, "XMPPJSObject.Disconnect called.", "test", MB_OK);
	if(argumentCount == 0) // No Arguments
	{
		XMPPJSObject * xmppObj = (XMPPJSObject *) JSObjectGetPrivate(thisObject);
		if(xmppObj)
		{
			bool bResult = xmppObj->Disconnect();
			return JSValueMakeBoolean(ctx, bResult);
		}
	}
	return JSValueMakeBoolean(ctx, false);
}


JSValueRef XMPPJSObject::Send(JSContextRef ctx,
							  JSObjectRef function,
							  JSObjectRef thisObject,
							  size_t argumentCount,
							  const JSValueRef arguments[],
							  JSValueRef *exception)
{
	::MessageBoxA(0, "XMPPJSObject.Send called.", "test", MB_OK);
	if(argumentCount == 1) // data
	{
		string data = JSStringUtils::getStringValueFrom(ctx, arguments[0]);
		XMPPJSObject * xmppObj = (XMPPJSObject *) JSObjectGetPrivate(thisObject);
		if(xmppObj)
		{
			bool bResult = xmppObj->Send(data);
			return JSValueMakeBoolean(ctx, bResult);
		}
	}
	return JSValueMakeBoolean(ctx, false);
}


JSValueRef XMPPJSObject::setStanzaHandler(JSContextRef ctx,
										  JSObjectRef function,
										  JSObjectRef thisObject,
										  size_t argumentCount,
										  const JSValueRef arguments[],
										  JSValueRef *exception)
{
	::MessageBoxA(0, "setStanzaHandler called", "setStanzaHandler", MB_OK);
	if(argumentCount == 1) // handler function
	{
		XMPPJSObject * xmppObj = (XMPPJSObject *) JSObjectGetPrivate(thisObject);
		if(xmppObj)
		{
			bool bResult = xmppObj->setStanzaHandler(ctx, JSValueToObject(ctx, arguments[0], exception));
			return JSValueMakeBoolean(ctx, bResult);
		}
	}
	return JSValueMakeBoolean(ctx, false);
}


bool XMPPJSObject::Connect(const string & hostname, const string & port)
{
	socket.Connect(hostname, port);
	return true;
}

bool XMPPJSObject::setStanzaHandler(JSContextRef _ctx, JSObjectRef _stanzaHandler)
{
	ctx = _ctx;
	stanzaHandler = _stanzaHandler;
	return true;
}
bool XMPPJSObject::Disconnect()
{
	//socket.disconnect();
	return false;
}


bool XMPPJSObject::Send(const string & data)
{
	socket.Write(data);
	return false;
}

/*

HRESULT StartTLS();
HRESULT StartSC();
HRESULT Disconnect();

*/

bool XMPPJSObject::callStanzaHandler(const string &data)
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
