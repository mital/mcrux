#pragma once

#include <map>
#include <list>
#include <string>
using namespace std;

#define CONNECTED_EVENT_NAME "onConnectComplete"
#define READ_DATA_EVENT_NAME "onRead"

#include <abstract/MObjectContainer.h>

#include <jscore/MJSCoreObject.h>
#include <jscore/MJSCoreObjectFactory.h>

#include "SocketObj.h"


class SocketJSObject
	: public MJSCoreObject
{
	map<string, JSObjectRef> eventMap;
	Socket socket;

	void addEventListener(const MObjectArray& args, MObjectContainer& resultContainer);
	void removeEventListener(const MObjectArray& args, MObjectContainer& resultContainer);
	void Connect(const MObjectArray& args, MObjectContainer& resultContainer);
	void Disconnect(const MObjectArray& args, MObjectContainer& resultContainer);
	void Send(const MObjectArray& args, MObjectContainer& resultContainer);

	// event listener related methods
	bool addEventListener(JSContextRef ctx, const string & eventName, JSObjectRef eventHandler);
	bool removeEventListener(JSContextRef ctx, const string & eventName, JSObjectRef eventHandler);
	JSObjectRef getEventListener(const string & eventName) const;

	bool Connect(const string & hostname, const string & port);
	bool Disconnect();
	bool Send(const string & data);

	virtual void construct(const MObjectArray& args, MObjectContainer& resultContainer);

public:

	SocketJSObject(JSContextRef ctx, const bool hasConstructor = true);
	virtual ~SocketJSObject();

	void handleReadData(const string &data);
	void onConnectComplete(const string & hostname, const string & port, bool bConnected);
};
