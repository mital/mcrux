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

#ifndef _FILEPROPS_H_
#define _FILEPROPS_H_

#include <iostream>

using namespace std;

#include <QtGui/QtGui>

#include <mcrux/qt/MQtModule.h>

#include "FileUtils.h"

class FileProps
: public MQtModule
{
  Q_OBJECT

public:

  FileProps(const FileInfo * _info);
  FileProps(const FileProps & props);
  virtual ~FileProps();

private:
  const FileInfo * info;

  void setProperties();
};


Q_DECLARE_METATYPE(FileProps*)

#endif // _FILEPROPS_H_
