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
#include "FileUtils.h"

#include <JavaScriptCore/JSContextRef.h>
#include <JavaScriptCore/JSRetainPtr.h>
#include <JavaScriptCore/JSStringRef.h>
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
		{"copyFile", FileSystemJSObject::copyFile, 0},
		{"readDir", FileSystemJSObject::readDir, 0},
		{"getFileInfo", FileSystemJSObject::getFileInfo, 0},
		{0, 0, 0}
	};
	return JSDefaultFunctions;
}

JSValueRef FileSystemJSObject::copyFile(JSContextRef ctx,
										JSObjectRef function,
										JSObjectRef thisObject,
										size_t argumentCount,
										const JSValueRef arguments[],
										JSValueRef *exception)
{
	::MessageBoxA(0, "filesystem.copyFile called.", "test", MB_OK);
	JSStringRef jssourceFile = JSValueToStringCopy(ctx, arguments[0], 0);
	string sourceFile = getStringValueFrom(jssourceFile);
	JSStringRef jsdestinationFile = JSValueToStringCopy(ctx, arguments[1], 0);
	string destinationFile = getStringValueFrom(jsdestinationFile);

	if(FileUtils::Copy(sourceFile, destinationFile))
	{
		return JSValueMakeBoolean(ctx, true);
	}
	return JSValueMakeBoolean(ctx, false);
}

JSValueRef FileSystemJSObject::readDir(JSContextRef ctx,
										JSObjectRef function,
										JSObjectRef thisObject,
										size_t argumentCount,
										const JSValueRef arguments[],
										JSValueRef *exception)
{
	::MessageBoxA(0, "filesystem.readDir called.", "test", MB_OK);
	if(argumentCount != 1)
	{
		::MessageBoxA(0, "please enter valid Number of Arguments", "error", MB_OK);
		return JSValueMakeNull(ctx);
	}
	JSStringRef jsDirectory = JSValueToStringCopy(ctx, arguments[0], 0);
	string dir = getStringValueFrom(jsDirectory);
	FileInfo * info = FileUtils::getFileInfo(dir);
	if(!info)
	{
		::MessageBoxA(0, "Path does not exist", "error", MB_OK);
		return JSValueMakeNull(ctx);
		JSValueMakeUndefined(ctx);
	}

	if(info->fileType != FILETYPE_DIRECTORY)
	{
		MessageBoxA(0, "this is not a directory.", "error", MB_OK);
		delete info;
		return JSValueMakeNull(ctx);
	}
	delete info;


	vector<string> files;
	FileUtils::readDirectory(dir, files);

	if(files.size() > 0)
	{
		JSValueRef * fileJSStrings = new JSValueRef[files.size()];
		for(unsigned int i = 0; i < files.size(); i++)
		{
			fileJSStrings[i] = JSValueMakeString(ctx,
				JSStringCreateWithUTF8CString(files[i].c_str()));
		}
		return JSObjectMakeArray(ctx, files.size(), fileJSStrings, NULL);
	}	
	return JSValueMakeNull(ctx);
}

JSValueRef FileSystemJSObject::getFileInfo(JSContextRef ctx,
										JSObjectRef function,
										JSObjectRef thisObject,
										size_t argumentCount,
										const JSValueRef arguments[],
										JSValueRef *exception)
{
	::MessageBoxA(0, "filesystem.getFileSize called.", "test", MB_OK);
	JSStringRef jsFile = JSValueToStringCopy(ctx, arguments[0], 0);
	string fileName = getStringValueFrom(jsFile);
	FileInfo * info = FileUtils::getFileInfo(fileName);

	int arraySize = 4;
	JSValueRef * fileJSStrings = new JSValueRef[arraySize];

	string fileType = (info->fileType == FILETYPE_FILE) ? "file" : "dir";
	fileJSStrings[0] = JSValueMakeString(ctx,
		JSStringCreateWithUTF8CString(fileType.c_str()));

	fileJSStrings[1] = JSValueMakeNumber(ctx, info->fileSize);
	fileJSStrings[2] = JSValueMakeNumber(ctx, (double)info->lastModifiedTime);
	fileJSStrings[3] = JSValueMakeNumber(ctx, (double)info->permissionMode);

	delete info;
	return JSObjectMakeArray(ctx, arraySize, fileJSStrings, NULL);
}
