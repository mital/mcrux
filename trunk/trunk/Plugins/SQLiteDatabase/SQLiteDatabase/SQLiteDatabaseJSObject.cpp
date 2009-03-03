#include "StdAfx.h"
#include "SQLiteDatabaseJSObject.h"

list<SQLiteDatabaseJSObject *> SQLiteDatabaseJSObject::sqliteObjects;

SQLiteDatabaseJSObject::SQLiteDatabaseJSObject()
{
}

SQLiteDatabaseJSObject::SQLiteDatabaseJSObject(JSContextRef ctx,
											   JSObjectRef constructor,
											   size_t argumentCount,
											   const JSValueRef arguments[],
											   JSValueRef* exception)
{
}


SQLiteDatabaseJSObject::~SQLiteDatabaseJSObject()
{
}

const char * SQLiteDatabaseJSObject::getName() const
{
	static string name = "sqlite_database";
	return name.c_str();
}

JSObjectCallAsConstructorCallback SQLiteDatabaseJSObject::getConstructor() const
{
	return SQLiteDatabaseJSObject::ConstructorCallback;
}


JSStaticFunction * SQLiteDatabaseJSObject::getStaticFunctions() const
{
	static JSStaticFunction JSDefaultFunctions[]
	= {
		//{"someFunction", SQLiteDatabaseJSObject::someFunction, 0},
		{0, 0, 0}
	};
	return JSDefaultFunctions;
}


JSObjectRef SQLiteDatabaseJSObject::ConstructorCallback(JSContextRef ctx,
														JSObjectRef constructor,
														size_t argumentCount,
														const JSValueRef arguments[],
														JSValueRef* exception)
{
	// check for required arguments before creating the object
	if(argumentCount == 0)
	{
		SQLiteDatabaseJSObject * newObj
			= new SQLiteDatabaseJSObject(ctx, constructor, argumentCount, arguments, exception);
		sqliteObjects.push_back(newObj);
		return newObj->createJSObject(ctx);
	}
	return 0;
	//return JSValueMakeNull(ctx);
	//return JSValueMakeUndefined(ctx);
	//return JSObjectMake(ctx, NULL, NULL);
}


JSStaticFunction * SQLiteDatabaseJSObject::getJSObjectFunctions() const
{
	static JSStaticFunction JSDefaultFunctions[]
	= {
		{"someFunction", SQLiteDatabaseJSObject::someFunction, 0},
		{0, 0, 0}
	};
	return JSDefaultFunctions;
}