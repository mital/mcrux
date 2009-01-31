#include "StdAfx.h"
#include "SQLiteDatabaseJSObject.h"

SQLiteDatabaseJSObject::SQLiteDatabaseJSObject()
{
}

SQLiteDatabaseJSObject::~SQLiteDatabaseJSObject()
{
}

string SQLiteDatabaseJSObject::getName() const
{
	static string name = "sqlite_database";
	return name;
}

JSStaticFunction * SQLiteDatabaseJSObject::getStaticFunctions() const
{
	static JSStaticFunction JSDefaultFunctions[]
	= {
		{"someFunction", SQLiteDatabaseJSObject::someFunction, 0},
		{0, 0, 0}
	};
	return JSDefaultFunctions;
}
