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
#include "mcrux/JSStringUtils.h"


FileSystemJSObject::FileSystemJSObject()
{
}

FileSystemJSObject::~FileSystemJSObject()
{
}


const char * FileSystemJSObject::getName() const
{
	static string name = "filesystem";
	return name.c_str();
}

JSStaticFunction * FileSystemJSObject::getStaticFunctions() const
{
	static JSStaticFunction JSDefaultFunctions[]
	= {
		{"copyFile", FileSystemJSObject::copyFile, 0},
		{"readDir", FileSystemJSObject::readDir, 0},
		{"readFile", FileSystemJSObject::readFile, 0},
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
	string sourceFile = getStringValueFrom(ctx, arguments[0]);
	string destinationFile = getStringValueFrom(ctx, arguments[1]);

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
	if(argumentCount != 1) // directory Name
	{
		::MessageBoxA(0, "please enter valid Number of Arguments", "error", MB_OK);
		return JSValueMakeNull(ctx);
	}
	string dir = getStringValueFrom(ctx, arguments[0]);
	FileInfo * info = FileUtils::getFileInfo(dir);
	if(!info)
	{
		::MessageBoxA(0, "Path does not exist", "error", MB_OK);
		return JSValueMakeNull(ctx);
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
		JSObjectRef * fileJSStrings = new JSObjectRef[files.size()];
		for(unsigned int i = 0; i < files.size(); i++)
		{
			fileJSStrings[i] = JSObjectMake(ctx, NULL, NULL);

			JSStringRef fileNameTag = JSStringCreateWithUTF8CString((const char *)"name");
			JSStringRef fileName = JSStringCreateWithUTF8CString(files[i].c_str());
			JSObjectSetProperty(ctx, fileJSStrings[i], fileNameTag, JSValueMakeString(ctx, fileName), 0, 0);

			info = FileUtils::getFileInfo(dir + files[i]);
			if(info)
			{
				string fileTypeStr = (info->fileType == FILETYPE_FILE) ? "file" : "dir";
				JSStringRef fileTypeTag = JSStringCreateWithUTF8CString((const char *)"type");
				JSStringRef fileType = JSStringCreateWithUTF8CString(fileTypeStr.c_str());
				JSObjectSetProperty(ctx, fileJSStrings[i], fileTypeTag, JSValueMakeString(ctx, fileType), 0, 0);

				JSStringRef fileSizeTag = JSStringCreateWithUTF8CString((const char *)"size");
				JSObjectSetProperty(ctx, fileJSStrings[i], fileSizeTag, JSValueMakeNumber(ctx, info->fileSize), 0, 0);

				JSStringRef fileModTimeTag = JSStringCreateWithUTF8CString((const char *)"last_modified_time");
				JSObjectSetProperty(ctx, fileJSStrings[i], fileModTimeTag, JSValueMakeNumber(ctx, (double)info->lastModifiedTime), 0, 0);
			}
			delete info;
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
	::MessageBoxA(0, "filesystem.getFileInfo called.", "test", MB_OK);
	if(argumentCount == 1) // fileName
	{
		string fileName = getStringValueFrom(ctx, arguments[0]);
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
	return JSValueMakeNull(ctx);
}

JSValueRef FileSystemJSObject::readFile(JSContextRef ctx,
										JSObjectRef function,
										JSObjectRef thisObject,
										size_t argumentCount,
										const JSValueRef arguments[],
										JSValueRef *exception)
{
	::MessageBoxA(0, "filesystem.ReadFile called.", "test", MB_OK);
	if(argumentCount == 1) // fileName
	{
		string sourceFile = getStringValueFrom(ctx, arguments[0]);
		string fileString;

		if(FileUtils::ReadFile(sourceFile, fileString))
		{
			return JSValueMakeString(ctx, JSStringCreateWithUTF8CString(fileString.c_str()));
		}
	}
	return JSValueMakeNull(ctx);
}
