/**
 * copyright (C) 2009 Mital Vora. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of MCrux nor the names of its contributors may be 
 *     used to endorse or promote products derived from this software 
 *     without specific prior written permission.
 *
 * @author: Mital Vora.
 **/


#include "StdAfx.h"
#include "FileSystemJSObject.h"

#include <JavaScriptCore/JSContextRef.h>
#include <JavaScriptCore/JSRetainPtr.h>
#include <JavaScriptCore/JSStringRefCF.h>
#include <JavaScriptCore/RetainPtr.h>

string getStringValueFrom(JSStringRef str)
{
	size_t length = JSStringGetMaximumUTF8CStringSize(str);
	char* buffer = new char[length];
	JSStringGetUTF8CString(str, buffer, length);
	string stdStr = buffer;
	delete[] buffer;
	return stdStr;
}

FileSystemJSObject::FileSystemJSObject()
{
}

FileSystemJSObject::~FileSystemJSObject()
{
}

string FileSystemJSObject::getName() const
{
	static string name = "filesystem";
	return name;
}

JSStaticFunction * FileSystemJSObject::getStaticFunctions() const
{
	static JSStaticFunction JSDefaultFunctions[]
	= {
		{"copyFile", FileSystemJSObject::CopyFile, 0},
		{0, 0, 0}
	};
	return JSDefaultFunctions;
}

JSValueRef FileSystemJSObject::CopyFile(JSContextRef ctx,
										JSObjectRef function,
										JSObjectRef thisObject,
										size_t argumentCount,
										const JSValueRef arguments[],
										JSValueRef *exception)
{
	::MessageBoxA(0, "filesystem.copyFile called.", "test", MB_OK);
	JSStringRef jssourceFile      = JSValueToStringCopy(ctx, arguments[0], 0);
	string sourceFile = getStringValueFrom(jssourceFile);
	JSStringRef jsdestinationFile = JSValueToStringCopy(ctx, arguments[1], 0);
	string destinationFile = getStringValueFrom(jsdestinationFile);

	return 0;
}
