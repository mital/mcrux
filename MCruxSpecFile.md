## Introduction ##

  * "mcruxspec" files are the specifications of the various windows of any application created by MCrux.
  * It also includes the list of plugins used by the application.
  * Following sections are included in MCruxSpec files.
## MCruxSpec ##
```
<?xml version="1.0" encoding="utf-8"?>
<mcrux xmlns="http://www.mcrux.com/2009/mcruxspec-version-1">
     <section1>
          ......
     </section1>
     <section2>
          ......
     </section2>
</mcrux>
```

  * all the MCrux applications will be embedded in "mcrux" node.
  * "mcrux" node has the namespace property which is the namespace which is going to be used for the xml parsing of the spec file. you should set it to "http://www.mcrux.com/2009/mcruxspec-version-1"
  * there will be list of sections which will be there as a child node of "mcrux" node.
  * the mcruxspec-version-1 is under development. There might be so many frequent changes happening to it. I will try to sync this wiki page updated for the latest changes.

below are the list of sections which can come under "mcrux"

### windows ###

  * mcrux supports multiple windows to be created.
  * the windows tag will look as shown below.
```
        <windows>
   	     <window title="My Window Title 1" height="600" width="300">
	   	     <url>/full/path/to/url/1</url>
	     </window>
   	     <window title="My Window Title2" height="200" width="200">
	   	     <url>/full/path/to/url/2</url>
	     </window>
        </windows>
```
  * window has below mentioned attributes
| Attribute | Value | Usage |
|:----------|:------|:------|
| title     | Title String | the window title to be shown on the titlebar of the window. |
| height    | Height in Pixels String | the height of the window required. |
| width     | Width in Pixels String | the width of the window required. |
| ` <url>fullpath</url> ` | the path of the url | The HTML file to be loaded into the mcruxwindow |


### plugins ###

  * mcrux can load multiple plugins. we need to specify the list of plugins to be loaded.
```
	<plugins>
		<plugin name="PluginName1"/>
		<plugin name="PluginName2"/>
		<plugin name="PluginName3"/>
		<plugin name="PluginName4"/>
	</plugins>
```

  * the name attribute of the plugin signifies that there is a plugin dll with the same name.
  * for example: If name attribute of any plugin is "PluginName1" then there is a Plugin dll named "PluginName1.dll" exists in the relative path "plugins/PluginName1.dll" to the MCrux executable.