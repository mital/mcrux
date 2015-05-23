# **FileSystem** Plugin is Local FileSystem access library #

## Introduction ##

**FileSystem provides access to the local filesystem to JavaScript. This is provided as a plugin of MCrux.**

## Details ##

**refer [Plugins](http://code.google.com/p/mcrux/wiki/Plugins) for more detail.**

## APIs ##

  * you have various static methods which can be invoked by the JavaScript to access the fileSystem.


` var files = mcrux.filesystem.readDir(dirName)`
  * dirName :String: the directory name for which we need all the information.
  * It reads the directory and returns the array of objects. Each object in the list will contain following properties.
  * name - the name of the file/subdirectory.
  * type - for file it will return "file" string and for directories it will return "dir".
  * size - the file size in number of bytes.
  * last\_modified\_time - the last modified time of the file in the form of timestamp.