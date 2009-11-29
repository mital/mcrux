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

#include "FileSystemQtModule.h"
#include "FileUtils.h"

static int myTypeID = qRegisterMetaType<FileSystemQtModule*>();

FileSystemQtModule::FileSystemQtModule()
{
  this->setObjectName("fileSystem");
}

FileSystemQtModule::~FileSystemQtModule()
{
}

QString FileSystemQtModule::readFile(const QString &filePath)
{
  qDebug() << "FileSystemQtModule::readFile: " << filePath;
  std::string filedata;
  if (FileUtils::ReadFile(filePath.toStdString(), filedata))
  {
    return QString(filedata.c_str());
  }
  // TODO: throw exception
  return QString("");
}

//  bool readDirectory(const string& dirName, vector<string>& files);
/*QList<QString> FileSystemQtModule::readDirectory(const QString& dirName)
{
  QList<QString> files;
  vector<string> stdFiles;
  if (FileUtils::readDirectory(dirName.toStdString(), stdFiles))
  {
    for(vector<string>::const_iterator
        oIter = stdFiles.begin();
        oIter != stdFiles.end();
        oIter++)
    {
      files.push_back(QString(oIter->c_str()));
    }
    return files;
  }
  // TODO: throw Exception
  return files;
}

QScriptValue FileSystemQtModule::getFileInfo(const QString& fileName)
{
  FileInfo * info = FileUtils::getFileInfo(fileName.toStdString());
  FileProps prop(info);
  return NULL;
}
  */
bool FileSystemQtModule::copy(const QString& sourceFileName, const QString& destFileName)
{
  return FileUtils::Copy(sourceFileName.toStdString(), destFileName.toStdString());
}
