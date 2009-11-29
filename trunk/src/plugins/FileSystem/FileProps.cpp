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

#include "FileProps.h"

static int myTypeID = qRegisterMetaType<FileProps*>();

FileProps::FileProps(const FileInfo * _info)
  : MQtModule(),
  info(_info)
{
  this->setObjectName("fileSystem");
  setProperties();
}

FileProps::FileProps(const FileProps & props)
  : MQtModule(),
  info(props.info)
{
  this->setObjectName("fileSystem");
  setProperties();
}


FileProps::~FileProps()
{
}


void FileProps::setProperties()
{
  string fileType = (info->fileType == FILETYPE_FILE) ? "file" : "dir";
  double fileSize = info->fileSize;
  double lastModifiedTime = info->lastModifiedTime;
  double permissionMode = info->permissionMode;

  setProperty("type", QVariant(QString(fileType.c_str())));
  setProperty("size", QVariant(fileSize));
  setProperty("last_modified_time", QVariant(lastModifiedTime));
  setProperty("permission_mode", QVariant(permissionMode));
}

