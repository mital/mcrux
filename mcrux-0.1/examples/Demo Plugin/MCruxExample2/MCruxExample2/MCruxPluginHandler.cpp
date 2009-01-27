#include "StdAfx.h"
#include "MCruxPluginHandler.h"

#include <JavaScriptCore/JSStringRef.h>

MCruxPluginHandler::MCruxPluginHandler()
{
}


MCruxPluginHandler::~MCruxPluginHandler()
{
}


bool MCruxPluginHandler::initialize(list<string> plugins, JSContextRef ctx)
{
	::MessageBoxA(0, plugins.back().c_str(), "MCruxPluginHandler called", MB_OK);

	HINSTANCE hHookDll = ::LoadLibrary(_T("DemoPlugin.dll"));
	if( hHookDll==NULL || hHookDll == INVALID_HANDLE_VALUE)
	{
		throw std::exception("Failed to load library");
	}
	JSObjectCallAsFunctionCallback myDemoFunctionPtr = (JSObjectCallAsFunctionCallback) ::GetProcAddress(hHookDll, "MyDemoPluginMethod");
	if (myDemoFunctionPtr == NULL)
	{
		throw(std::exception("Entry point not found"));
	}

	static JSStaticFunction demoDefaultFunctions[]
	= {
		{"myFunction", myDemoFunctionPtr, 0},
		{0, 0, 0}
	};


	JSClassDefinition demoNameSpace;

	demoNameSpace.version = 0;
	demoNameSpace.attributes = 0;
	demoNameSpace.className = plugins.back().c_str();
	demoNameSpace.parentClass = 0;
	demoNameSpace.staticValues = 0;
	demoNameSpace.staticFunctions = demoDefaultFunctions;
	demoNameSpace.initialize = 0;
	demoNameSpace.finalize = 0;
	demoNameSpace.hasProperty = 0;
	demoNameSpace.getProperty = 0;
	demoNameSpace.setProperty = 0;
	demoNameSpace.deleteProperty = 0;
	demoNameSpace.getPropertyNames = 0;
	demoNameSpace.callAsFunction = 0;
	demoNameSpace.callAsConstructor = 0;
	demoNameSpace.hasInstance = 0;
	demoNameSpace.convertToType = 0;

	JSClassRef demoRef = JSClassCreate(&demoNameSpace);
	JSObjectRef obj = JSObjectMake(ctx, demoRef, this);

	JSObjectRef globalObject = JSContextGetGlobalObject(ctx);

	JSStringRef fnPropName = JSStringCreateWithUTF8CString(plugins.back().c_str());
	JSObjectSetProperty(ctx, globalObject,
		fnPropName,
		obj, 0, 0);

	return false;
}

