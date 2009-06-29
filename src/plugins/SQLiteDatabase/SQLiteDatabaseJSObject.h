#pragma once

#include <list>
using namespace std;

#include "mcrux/MCruxPlugin.h"


class SQLiteDatabaseJSObject :
	public MCruxPlugin
{
	static list<SQLiteDatabaseJSObject *> sqliteObjects;

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

	static JSObjectRef ConstructorCallback(JSContextRef ctx,
		JSObjectRef constructor,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef* exception);

public:

	SQLiteDatabaseJSObject(JSContextRef ctx,
		JSObjectRef constructor,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef* exception);

	SQLiteDatabaseJSObject();
	virtual ~SQLiteDatabaseJSObject();

	virtual const char * getName() const;

	virtual JSStaticFunction * getStaticFunctions() const;

	virtual JSObjectCallAsConstructorCallback getConstructor() const;
	virtual JSStaticFunction * getJSObjectFunctions() const;
};
