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
	if (args.size() == 2) // eventName, eventHandlerFunction
	{
		MJSCoreObjectAbstract * eventName = dynamic_cast<MJSCoreObjectAbstract* >(args.getAt(0));
		MJSCoreObject * eventHandler = dynamic_cast<MJSCoreObject *>(args.getAt(1));
		if (eventName && eventHandler)
		{
			bool bRet = AddEventListener(eventName->toString(), eventHandler);
			resultContainer.set(MJSCoreObjectFactory::getMObject(bRet));
		}
	}
	resultContainer.set(MJSCoreObjectFactory::getMObject(false));
}


void SocketJSObject::removeEventListener(const MObjectArray& args, MObjectContainer& resultContainer)
{
	if (args.size() == 2) // eventName, eventHandlerFunction
	{
		MJSCoreObjectAbstract * eventName = dynamic_cast<MJSCoreObjectAbstract* >(args.getAt(0));
		MJSCoreObject * eventHandler = dynamic_cast<MJSCoreObject *>(args.getAt(1));
		if (eventName && eventHandler)
		{
			bool bRet = RemoveEventListener(eventName->toString(), eventHandler);
			resultContainer.set(MJSCoreObjectFactory::getMObject(bRet));
		}
	}
	resultContainer.set(MJSCoreObjectFactory::getMObject(false));
}


void SocketJSObject::Connect(const MObjectArray& args, MObjectContainer& resultContainer)
{
	if (args.size() == 2) // server, port
	{
		MJSCoreObjectAbstract* serverObj = dynamic_cast<MJSCoreObjectAbstract* >(args.getAt(0));
		MJSCoreObjectAbstract* portObj = dynamic_cast<MJSCoreObjectAbstract* >(args.getAt(1));
		string server = serverObj->toString();
		string port = portObj->toString();

		bool bResult = Connect(server, port);
		resultContainer.set(MJSCoreObjectFactory::getMObject(bResult));
	}
	resultContainer.set(MJSCoreObjectFactory::getMObject(false));
}

void SocketJSObject::Disconnect(const MObjectArray& args, MObjectContainer& resultContainer)
{
	::MessageBoxA(0, "SocketJSObject.Disconnect called.", "test", MB_OK);
	bool bResult = false;
	if (args.size() == 0) // No Arguments
	{
		bResult = Disconnect();
	}
	resultContainer.set(MJSCoreObjectFactory::getMObject(bResult));
}


void SocketJSObject::Send(const MObjectArray& args, MObjectContainer& resultContainer)
{
	bool bResult = false;
	if(args.size() == 1) // data
	{
		MJSCoreObjectAbstract* dataObj = dynamic_cast<MJSCoreObjectAbstract* >(args.getAt(0));
		string data = dataObj->toString();
		bResult = Send(data);
	}
	resultContainer.set(MJSCoreObjectFactory::getMObject(bResult));
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


bool SocketJSObject::AddEventListener(const string & eventName, MJSCoreObject * eventHandler)
{
	eventMap[eventName] = eventHandler;
	eventMap[eventName]->protect();
	return true;
}


MJSCoreObject * SocketJSObject::GetEventListener(const string & eventName) const
{
	map<string, MJSCoreObject *>::const_iterator iter = eventMap.find(eventName);
	if (iter != eventMap.end())
	{
		return iter->second;
	}
	return NULL;
}


bool SocketJSObject::RemoveEventListener(const string & eventName, MJSCoreObject * eventHandler)
{
	map<string, MJSCoreObject *>::iterator iter = eventMap.find(eventName);
	if (iter != eventMap.end() && iter->second == eventHandler)
	{
		iter->second->unprotect();
		delete iter->second;
		eventMap.erase(iter);
		return true;
	}
	return false;
}


void SocketJSObject::handleReadData(const string &data)
{
	JSContextRef ctx = MJSCoreObjectFactory::getJSContext();
	JSObjectRef global = JSContextGetGlobalObject(ctx);
	MJSCoreObject * eventObj = dynamic_cast<MJSCoreObject *>(MJSCoreObjectFactory::getMObject());
	eventObj->setProperty("data", MJSCoreObjectFactory::getMObject(data));

	MJSCoreObject * handler = GetEventListener(READ_DATA_EVENT_NAME);
	if (handler)
	{
		JSValueRef eventObject = eventObj->getJSValue();
		JSObjectCallAsFunction(ctx, handler->getJSObject(), global, 1, &eventObject, 0);
	}
}


void SocketJSObject::onConnectComplete(const string & hostname, const string & port, bool bConnected)
{
	JSContextRef ctx = MJSCoreObjectFactory::getJSContext();
	JSObjectRef global = JSContextGetGlobalObject(ctx);
	MJSCoreObject * eventObj = dynamic_cast<MJSCoreObject *>(MJSCoreObjectFactory::getMObject());
	eventObj->setProperty("hostname", MJSCoreObjectFactory::getMObject(hostname));
	eventObj->setProperty("port", MJSCoreObjectFactory::getMObject(port));
	eventObj->setProperty("connected", MJSCoreObjectFactory::getMObject(bConnected));

	MJSCoreObject * handler = GetEventListener(CONNECTED_EVENT_NAME);
	if (handler)
	{
		JSValueRef eventObject = eventObj->getJSValue();
		JSObjectCallAsFunction(ctx, handler->getJSObject(), global, 1, &eventObject, 0);
	}
}