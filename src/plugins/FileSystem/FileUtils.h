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

#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

enum FileType_en
{
  FILETYPE_FILE = 0,
  FILETYPE_DIRECTORY,
};


struct FileInfo
{
  FileType_en fileType;
  long fileSize;
  time_t lastModifiedTime;
  unsigned short permissionMode;
};


namespace FileUtils
{
  bool readDirectory(const string& dirName, vector<string>& files);
  FileInfo * getFileInfo(const string& fileName);
  bool Copy(const string& sourceFileName, const string& destFileName);
  bool ReadFile(const string& filename, string& str);

};
