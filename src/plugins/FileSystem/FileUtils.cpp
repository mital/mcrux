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

#ifdef WIN32
#include "StdAfx.h"

#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "dirent.h"
#include <errno.h>
#else // for linux

#include <dirent.h>
#endif

#include <fcntl.h>
#include <fstream>

#include "FileUtils.h"

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
	FileInfo * info = new FileInfo();

	struct stat status;
	stat(fileName.c_str(), &status);

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

  std::cout << "copy: "<< sourceFileName.c_str() << " to " << destFileName.c_str() << std::endl;
	bool bRet = false;
	char *buffer = NULL;

	try
	{
		FileInfo *sourceFileInfo = FileUtils::getFileInfo(sourceFileName);
		FileInfo *destFileInfo = FileUtils::getFileInfo(destFileName);
		if(sourceFileInfo
			&& sourceFileInfo->fileType != FILETYPE_DIRECTORY && destFileInfo == NULL)
		{
			buffer = new char[sourceFileInfo->fileSize];

			ifstream srcFileStream(sourceFileName.c_str(), ios::in|ios::binary);
			if (srcFileStream.is_open())
			{
				srcFileStream.seekg (0, ios::end);
				int length = srcFileStream.tellg();
				srcFileStream.seekg (0, ios::beg);

				ofstream destFileStream(destFileName.c_str(), ios::out|ios::binary);

				int readBytes=0;
				while (srcFileStream)
				{
					srcFileStream.read(buffer, sourceFileInfo->fileSize);
					readBytes = srcFileStream.gcount();

					if (readBytes > 0)
					{
						destFileStream.write(buffer, readBytes);
					}

					length -= readBytes;

					if (length <= 0)
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
    std::cout << "caught exception" << std::endl;
		if (NULL != buffer)
		{
			delete [] buffer;
		}
	}

	return bRet;
}


bool FileUtils::ReadFile(const string & fileName, string & str)
{
	struct stat st;
	int bufSize;
	char * pcBuf = NULL;
	str = "";
	try
	{
		if ((stat(fileName.c_str(), &st)) == -1)
		{
			return false;
		}

		bufSize = st.st_size;
		pcBuf = new char[bufSize];

		ifstream streamFile(fileName.c_str(), ios::in | ios::binary);
		if (!streamFile.is_open())
		{
			delete []  pcBuf;
			return false;
		}
		streamFile.seekg(0, ios::end);
		int length = streamFile.tellg();
		streamFile.seekg(0, ios::beg);

		int readBytes = 0;
		while (streamFile)
		{
			streamFile.read(pcBuf, bufSize);
			readBytes = streamFile.gcount();

			if (readBytes > 0)
			{
				copy(pcBuf, pcBuf + readBytes, back_inserter<string>(str));
			}

			length -= readBytes;

			if (length <= 0)
			{
				break;
			}
		}

		streamFile.close();
		delete [] pcBuf;
	}
	catch(exception &)
	{
		if (pcBuf)
		{
			delete [] pcBuf;
		}
		return false;
	}
	return true;
}
