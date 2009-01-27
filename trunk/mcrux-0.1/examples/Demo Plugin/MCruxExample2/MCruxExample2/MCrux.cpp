#include "StdAfx.h"
#include "MCrux.h"

#include <JavaScriptCore/JSContextRef.h>
#include <JavaScriptCore/JSRetainPtr.h>
#include <JavaScriptCore/JSStringRefCF.h>
#include <JavaScriptCore/RetainPtr.h>



MCrux::MCrux()
: mcruxPluginHandler()
{

	prepareMCruxClassDefinition();
}

MCrux::~MCrux()
{
}


void MCrux::prepareMCruxClassDefinition()
{
	static JSStaticFunction mcruxDefaultFunctions[]
		= {
			{"initialize", MCrux::initialize, 0},
			{0, 0, 0}
		};

	MCruxNameSpace.version = 0;
	MCruxNameSpace.attributes = 0;
	MCruxNameSpace.className = "mcrux";
	MCruxNameSpace.parentClass = 0;
	MCruxNameSpace.staticValues = 0;
	MCruxNameSpace.staticFunctions = mcruxDefaultFunctions;
	MCruxNameSpace.initialize = mcruxInitialize;
	MCruxNameSpace.finalize = mcruxFinalize;
	MCruxNameSpace.hasProperty = 0;
	MCruxNameSpace.getProperty = 0;
	MCruxNameSpace.setProperty = 0;
	MCruxNameSpace.deleteProperty = 0;
	MCruxNameSpace.getPropertyNames = 0;
	MCruxNameSpace.callAsFunction = 0;
	MCruxNameSpace.callAsConstructor = 0;
	MCruxNameSpace.hasInstance = 0;
	MCruxNameSpace.convertToType = 0;
}


JSObjectRef MCrux::createJSWrapper(JSContextRef context)
{
	JSClassRef mcruxRef = JSClassCreate(&MCruxNameSpace);
	return JSObjectMake(context, mcruxRef, this);
}

MCruxPluginHandler* MCrux::getPluginHandler()
{
	return &mcruxPluginHandler;
}


JSValueRef MCrux::initialize(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception)
{
	::MessageBoxA(0, "initialize called", "test", MB_OK);
	JSStringRef myString = JSValueToStringCopy(ctx, arguments[0], 0);

	string str = getStringValueFrom(myString);
	list<string> plugins;
	plugins.push_back(str);

	MCrux * mcruxObj = (MCrux *) JSObjectGetPrivate(thisObject);
	MCruxPluginHandler* mcruxPluginHandler = mcruxObj->getPluginHandler();
	mcruxPluginHandler->initialize(plugins, ctx);

	return 0;
}


void MCrux::mcruxInitialize(JSContextRef ctx, JSObjectRef object)
{
}

void MCrux::mcruxFinalize(JSObjectRef object)
{
	// TODO: delete the objects at appropriate time
	::MessageBoxA(0, "mcruxFinalize called", "test", MB_OK);
}


string MCrux::getStringValueFrom(JSStringRef str)
{
	size_t length = JSStringGetMaximumUTF8CStringSize(str);
	char* buffer = new char[length];
	JSStringGetUTF8CString(str, buffer, length);
	string stdStr = buffer;
	delete[] buffer;
	return stdStr;
}