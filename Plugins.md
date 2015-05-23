This page lists various Plugins provided by MCrux.

# Introduction #
  * This page lists various Plugins provided by MCrux.
  * It also provides the common steps one need to do to get their plugins work with MCrux.

# Details #

  * Below is the list of plugins provided by MCrux.

  * [LIBXMLSAXParser](http://code.google.com/p/mcrux/wiki/LIBXMLSAXParser)
  * [Socket](http://code.google.com/p/mcrux/wiki/Socket)
  * FileSystem
  * SqliteDatabase


## How To Inject Plugin Into MCrux ##
  * steps to follow while injecting **MCruxPlugin**

  * you need to get the **PluginName.dll** and put it at appropriate place. ( currently in plugins directory relative path to MCrux\_exe.exe
  * for each plugin add the below specified XML node. (PluginName will come from PluginName.dll)
```
<plugin name="PluginName"/>
```

  * the final plugins section will look like
```
<plugins>
  <plugin name="PluginName1"/>
  <plugin name="PluginName2"/>
  <plugin name="PluginName3"/>
</plugins>
```

  * here you go now you have a list of plugins ready to work with MCrux.