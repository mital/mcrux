# **LIBXMLSAXParser** Plugin is a SAX parsing library #

## Introduction ##

**LIBXMLSAXParser is a SAX parsing library provided as a plugin of MCrux.** It uses libxml as the backend parsing library.

## Details ##

**refer [Plugins](http://code.google.com/p/mcrux/wiki/Plugins) for more detail.**

## APIs ##

  * you can create an object of LIBXMLSAXParser plugin in JavaScript using following code block

` var saxParserObj = new mcrux.libxml_saxparser();  `
  * this creates a new libxml\_saxparser object. you can call various methods which are provided.

` saxParserObj.xmlParseChunk(data);`
  * data :String: the data to be parsed
  * you can parse your xml file chunk by chunk by calling this method in loop.
  * data will be parsed by the Plugin and Events are raised appropriately.

## Event Listeners ##

there are following event listeners available.

onStartElement(event)
  * This Event is raised when an XML start tag is found.
  * parameters:event
  * event.tag :String: the tag name of the start-element
  * event.attributes :key value pairs of Strings: various attributes available in the tag.

onCharacters(event)
  * This Event is raised when an XML start tag is found.
  * parameters:event
  * event.characters :String: the characters which are found in between the start and end elements.

onEndElement(event)
  * This Event is raised when an XML end tag is found.
  * parameters:event
  * event.tag :String: the tag name of the end-element

## How To Register Event Listeners ##

addEventListener(eventName, HandlerFunction)
  * **EventName** :String: name of the event which you want to handle.
  * **HandlerFunction** :function: function which you want to be called.

removeEventListener(eventName, HandlerFunction)
  * **EventName** :String: name of the event which you want to handle.
  * **HandlerFunction** :function: function which you want to remove from the call list.