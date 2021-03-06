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

#include <abstract/MObjectContainer.h>
#include <jscore/MJSCoreObjectFactory.h>

#include "FileSystemJSObject.h"


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
		MJSCoreObjectAbstract* srcFileString = dynamic_cast<MJSCoreObjectAbstract*>(args.getAt(0));
		MJSCoreObjectAbstract* destFileString = dynamic_cast<MJSCoreObjectAbstract *>(args.getAt(1));
		if (srcFileString && destFileString)
		{
			if(FileUtils::Copy(srcFileString->toString(), destFileString->toString()))
			{
				resultContainer.set(MJSCoreObjectFactory::getMObject(true));
				return;
			}
		}
	}
	resultContainer.set(MJSCoreObjectFactory::getMObject(false));
}


void FileSystemJSObject::readDir(const MObjectArray& args, MObjectContainer& resultContainer)
{
	if (args.size() == 1)
	{
		MJSCoreObjectAbstract* srcFileString = dynamic_cast<MJSCoreObjectAbstract*>(args.getAt(0));
		if (srcFileString)
		{
			string dir = srcFileString->toString();
			FileInfo * info = FileUtils::getFileInfo(dir);
			if(info)
			{
				if(info->fileType == FILETYPE_DIRECTORY)
				{
					delete info;
					vector<string> files;
					if (FileUtils::readDirectory(dir, files) && (files.size() > 0))
					{
						vector<MJSCoreObject *> jsFiles;
						for (size_t i = 0; i < files.size(); i++)
						{
							info = FileUtils::getFileInfo(dir + files[i]);
							if(info)
							{
								MJSCoreObject * fileProps = getFilePropertyObject(info);
								delete info;
								jsFiles.push_back(fileProps);
							}
						}
						resultContainer.set(MJSCoreObjectFactory::getMObject(jsFiles));
					}
				}
				else
				{
					delete info;
				}
			}
		}
	}
}

void FileSystemJSObject::getFileInfo(const MObjectArray& args, MObjectContainer& resultContainer)
{
	::MessageBoxA(0, "filesystem.getFileInfo called.", "test", MB_OK);
	if (args.size() == 1)
	{
		MJSCoreObjectAbstract * fileString = dynamic_cast<MJSCoreObjectAbstract *>(args.getAt(0));

		if (fileString)
		{
			string fileName = fileString->toString();
			FileInfo * info = FileUtils::getFileInfo(fileName);
			if (info)
			{
				MJSCoreObject * fileProps = getFilePropertyObject(info);
				if(fileProps)
				{
					resultContainer.set(fileProps);
				}
				delete info;
			}
		}
	}
}


void FileSystemJSObject::readFile(const MObjectArray& args, MObjectContainer& resultContainer)
{
	::MessageBoxA(0, "filesystem.ReadFile called.", "test", MB_OK);
	if (args.size() == 1)
	{
		MJSCoreObjectAbstract* fileStr = dynamic_cast<MJSCoreObjectAbstract*>(args.getAt(0));

		if (fileStr)
		{
			string fileName = fileStr->toString();
			string fileString;

			if(FileUtils::ReadFile(fileName, fileString))
			{
				resultContainer.set(MJSCoreObjectFactory::getMObject(fileString));
			}
		}
	}
}

MJSCoreObject * FileSystemJSObject::getFilePropertyObject(FileInfo * info) const
{
	string fileType = (info->fileType == FILETYPE_FILE) ? "file" : "dir";
	double fileSize = info->fileSize;
	double lastModifiedTime = info->lastModifiedTime;
	double permissionMode = info->permissionMode;

	MJSCoreObject * fileProps = dynamic_cast<MJSCoreObject *>(MJSCoreObjectFactory::getMObject());
	fileProps->setProperty("type", MJSCoreObjectFactory::getMObject(fileType));
	fileProps->setProperty("size", MJSCoreObjectFactory::getMObject(fileSize));
	fileProps->setProperty("last_modified_time", MJSCoreObjectFactory::getMObject(lastModifiedTime));
	fileProps->setProperty("permission_mode", MJSCoreObjectFactory::getMObject(permissionMode));
	return fileProps;
}