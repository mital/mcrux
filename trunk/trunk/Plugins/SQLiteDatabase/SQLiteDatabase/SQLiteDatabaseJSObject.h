#pragma once

#include "mcrux/MCruxPlugin.h"


class SQLiteDatabaseJSObject :
	public MCruxPlugin
{

	static JSValueRef someFunction(JSContextRef ctx,
		JSObjectRef function,
		JSObjectRef thisObject,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef *exception)
	{
		::MessageBoxA(0, "SQLiteDatabaseJSObject someFunction called", "test", MB_OK);
		return 0;
	}

public:
	SQLiteDatabaseJSObject();
	virtual ~SQLiteDatabaseJSObject();

	virtual string getName() const;
	virtual JSStaticFunction * getStaticFunctions() const;
};
