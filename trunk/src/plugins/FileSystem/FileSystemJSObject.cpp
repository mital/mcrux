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
#include "FileUtils.h"
#include "FileSystemJSObject.h"

#include <abstract/MObjectContainer.h>

#include <jscore/MJSCoreObjectFactory.h>


FileSystemJSObject::FileSystemJSObject(JSContextRef ctx)
: MJSCoreObject(ctx, "fileSystem")
{
	setProperty(ctx, "copyFile", &FileSystemJSObject::copyFile);
	setProperty(ctx, "readDir", &FileSystemJSObject::readDir);
	setProperty(ctx, "getFileInfo", &FileSystemJSObject::getFileInfo);
	setProperty(ctx, "readFile", &FileSystemJSObject::readFile);
}

FileSystemJSObject::~FileSystemJSObject()
{
}

void FileSystemJSObject::copyFile(const MObjectArray& args, MObjectContainer& resultContainer)
{
	::MessageBoxA(0, "filesystem.copyFile called.", "test", MB_OK);
	if (args.size() == 2)
	{
		MObject * srcFileObj = args.getAt(0);
		MObject * destFileObj = args.getAt(1);
		MJSCoreString * srcFileString = dynamic_cast<MJSCoreString *>(srcFileObj);
		MJSCoreString * destFileString = dynamic_cast<MJSCoreString *>(destFileObj);
		if (srcFileString && destFileString)
		{
			if(FileUtils::Copy(srcFileString->getString(), destFileString->getString()))
			{
				resultContainer.set(MJSCoreObjectFactory::getMObject(true));
			}
		}
	}
	resultContainer.set(MJSCoreObjectFactory::getMObject(false));
}


void FileSystemJSObject::readDir(const MObjectArray& args, MObjectContainer& resultContainer)
{
	if (args.size() == 1)
	{
		MObject * srcFileObj = args.getAt(0);
		MJSCoreString * srcFileString = dynamic_cast<MJSCoreString *>(srcFileObj);
		if (srcFileString)
		{
			string dir = srcFileString->getString();
			FileInfo * info = FileUtils::getFileInfo(dir);
			if(info)
			{
				if(info->fileType != FILETYPE_DIRECTORY)
				{
					delete info;
					vector<string> files;
					FileUtils::readDirectory(dir, files);

					if(files.size() > 0)
					{
						// TODO: create a new return type array :P

						//JSObjectRef * fileJSStrings = new JSObjectRef[files.size()];
						//for(unsigned int i = 0; i < files.size(); i++)
						//{
						//	fileJSStrings[i] = JSObjectMake(ctx, NULL, NULL);

						//	JSStringRef fileNameTag = JSStringCreateWithUTF8CString((const char *)"name");
						//	JSStringRef fileName = JSStringCreateWithUTF8CString(files[i].c_str());
						//	JSObjectSetProperty(ctx, fileJSStrings[i], fileNameTag, JSValueMakeString(ctx, fileName), 0, 0);

						//	info = FileUtils::getFileInfo(dir + files[i]);
						//	if(info)
						//	{
						//		string fileTypeStr = (info->fileType == FILETYPE_FILE) ? "file" : "dir";
						//		JSStringRef fileTypeTag = JSStringCreateWithUTF8CString((const char *)"type");
						//		JSStringRef fileType = JSStringCreateWithUTF8CString(fileTypeStr.c_str());
						//		JSObjectSetProperty(ctx, fileJSStrings[i], fileTypeTag, JSValueMakeString(ctx, fileType), 0, 0);

						//		JSStringRef fileSizeTag = JSStringCreateWithUTF8CString((const char *)"size");
						//		JSObjectSetProperty(ctx, fileJSStrings[i], fileSizeTag, JSValueMakeNumber(ctx, info->fileSize), 0, 0);

						//		JSStringRef fileModTimeTag = JSStringCreateWithUTF8CString((const char *)"last_modified_time");
						//		JSObjectSetProperty(ctx, fileJSStrings[i], fileModTimeTag, JSValueMakeNumber(ctx, (double)info->lastModifiedTime), 0, 0);
						//	}
						//	delete info;
						//}
						//return JSObjectMakeArray(ctx, files.size(), fileJSStrings, NULL);
					}
				}
			}
			delete info;
		}
	}
}

void FileSystemJSObject::getFileInfo(const MObjectArray& args, MObjectContainer& resultContainer)
{
	::MessageBoxA(0, "filesystem.getFileInfo called.", "test", MB_OK);
	if (args.size() == 1)
	{
		MObject * fileObj = args.getAt(0);
		MJSCoreString * fileString = dynamic_cast<MJSCoreString *>(fileObj);

		if (fileString)
		{
			string fileName = fileString->getString();
			FileInfo * info = FileUtils::getFileInfo(fileName);

			string fileType = (info->fileType == FILETYPE_FILE) ? "file" : "dir";
			double fileSize = info->fileSize;
			double lastModifiedTime = info->lastModifiedTime;
			double permissionMode = info->permissionMode;
			delete info;

			MJSCoreObject * fileProps = dynamic_cast<MJSCoreObject *>(MJSCoreObjectFactory::getMObject());
			fileProps->setProperty("type", MJSCoreObjectFactory::getMObject(fileType));
			fileProps->setProperty("size", MJSCoreObjectFactory::getMObject(fileSize));
			fileProps->setProperty("last_modified_time", MJSCoreObjectFactory::getMObject(lastModifiedTime));
			fileProps->setProperty("permission_mode", MJSCoreObjectFactory::getMObject(permissionMode));
			resultContainer.set(fileProps);
		}
	}
}


void FileSystemJSObject::readFile(const MObjectArray& args, MObjectContainer& resultContainer)
{
	::MessageBoxA(0, "filesystem.ReadFile called.", "test", MB_OK);
	if (args.size() == 1)
	{
		MObject * fileObj = args.getAt(0);
		MJSCoreString * fileStr = dynamic_cast<MJSCoreString *>(fileObj);

		if (fileStr)
		{
			string fileName = fileStr->getString();
			string fileString;

			if(FileUtils::ReadFile(fileName, fileString))
			{
				resultContainer.set(MJSCoreObjectFactory::getMObject(fileString));
			}
		}
	}
}
