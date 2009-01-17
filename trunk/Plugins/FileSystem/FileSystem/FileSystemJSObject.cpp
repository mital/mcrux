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

#include "dirent.h"

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


bool FileSystemJSObject::readDirectory(const string& dirName, list<string>& files)
{
  DIR* pDir = opendir(dirName.c_str());
  if (NULL != pDir)
  {
    struct dirent * ep = NULL;
    while ((ep = readdir (pDir)))
    {
      if ((string(ep->d_name) != ".") && (string(ep->d_name) != "..") )
      {
        files.push_back(ep->d_name);
      }
    }
    closedir (pDir);
  }
  else
  {
    return false;
  }
  return true;
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
	JSStringRef jssourceFile      = JSValueToStringCopy(ctx, arguments[0], 0);
	string sourceFile = getStringValueFrom(jssourceFile);
	JSStringRef jsdestinationFile = JSValueToStringCopy(ctx, arguments[1], 0);
	string destinationFile = getStringValueFrom(jsdestinationFile);

	return 0;
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
		return 0;
	}
	JSStringRef jsDirectory = JSValueToStringCopy(ctx, arguments[0], 0);
	string dir = getStringValueFrom(jsDirectory);
	list<string> files;
	readDirectory(dir, files);

	return 0;
}