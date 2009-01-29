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
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "dirent.h"
#include <errno.h>

#include <fstream>


bool FileUtils::readDirectory(const string& dirName, vector<string>& files)
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

FileInfo * FileUtils::getFileInfo(const string& fileName)
{
	if (_access(fileName.c_str(), 0) != 0)
	{
		return NULL;
	}

	struct stat status;
	stat(fileName.c_str(), &status);

	FileInfo * info = new FileInfo();

	info->fileType = FILETYPE_FILE;
	info->fileSize = status.st_size;
	info->lastModifiedTime = status.st_mtime;
	info->permissionMode = status.st_mode;

	if (status.st_mode & S_IFDIR)
	{
		info->fileType = FILETYPE_DIRECTORY;
	}

	return info;
}


bool FileUtils::Copy(const string& sourceFileName, const string& destFileName)
{
	bool bRet = false;
	char *buffer = NULL;

	try
	{
		FileInfo *sourceFileInfo = FileUtils::getFileInfo(sourceFileName);
		FileInfo *destFileInfo = FileUtils::getFileInfo(destFileName);
		if(sourceFileInfo
			&& sourceFileInfo->fileType != FILETYPE_DIRECTORY && destFileInfo == NULL)
		{
			int dstFileHandle = -1;
			_sopen_s(&dstFileHandle, destFileName.c_str(), _O_CREAT | _O_BINARY, 0, sourceFileInfo->permissionMode);
			_close(dstFileHandle);

			buffer = new char[sourceFileInfo->fileSize];

			ifstream srcFileStream(sourceFileName.c_str(), ios::in|ios::binary);
			if (srcFileStream.is_open())
			{
				srcFileStream.seekg (0, ios::end);
				int iLength = srcFileStream.tellg();
				srcFileStream.seekg (0, ios::beg);

				ofstream destFileStream(destFileName.c_str(), ios::out|ios::binary);

				int iBread=0;
				while (srcFileStream)
				{
					srcFileStream.read(buffer, sourceFileInfo->fileSize);
					iBread = srcFileStream.gcount();

					if (iBread > 0)
					{
						destFileStream.write(buffer, iBread);
					}

					iLength -= iBread;

					if (iLength <= 0)
					{
						break;
					}
				}

				srcFileStream.close();
				destFileStream.close();
				bRet = true;
			}

			delete [] buffer;
			delete sourceFileInfo;
		}
		if(destFileInfo)
		{
			delete destFileInfo;
		}

	}
	catch (...)
	{
		if (NULL != buffer)
		{
			delete [] buffer;
		}
	}

	return bRet;
}
