#include "StdAfx.h"
#include "XMPPJSObject.h"
#include <JavaScriptCore/JSContextRef.h>
#include <JavaScriptCore/JSRetainPtr.h>
#include <JavaScriptCore/JSStringRefCF.h>
#include <JavaScriptCore/RetainPtr.h>
#include "JSStringUtils.h"


list<XMPPJSObject *> XMPPJSObject::xmppObjects;

XMPPJSObject::XMPPJSObject()
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
		{"dummy", XMPPJSObject::dummyFunc, 0},
		{0, 0, 0}
	};
	return JSDefaultFunctions;
}


JSStaticFunction * XMPPJSObject::getJSObjectStaticFunctions() const
{
	static JSStaticFunction JSDefaultFunctions[]
	= {
		{"Connect", XMPPJSObject::Connect, 0},
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
		int port = (int) JSStringUtils::getDoubleValueFrom(ctx, arguments[1]);
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


bool XMPPJSObject::Connect(const string & server, unsigned short port)
{
	::MessageBoxA(0, "xmpp actual connect called", "awesome", MB_OK);
	return false;
}
bool XMPPJSObject::Disconnect()
{
	return false;
}


bool XMPPJSObject::Send(const string & data)
{
	return false;
}

/*

HRESULT Connect( [in] BSTR server, [in] USHORT port, [in,defaultvalue(FALSE)] BOOL useSSL,
[in,defaultvalue(0)] DWORD ProxyMethod );
HRESULT StartTLS();
HRESULT StartSC();
HRESULT Disconnect();
HRESULT SendText( [in] BSTR strText );

*/