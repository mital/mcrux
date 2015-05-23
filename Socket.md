# **Socket** Plugin is a TCPSocket library #

## Introduction ##

  * Socket is a TCPSocket library provided as a plugin of MCrux.
  * It uses openssl as the backend library.

## How To Inject Plugin Into MCrux ##

**refer [Plugins](http://code.google.com/p/mcrux/wiki/Plugins) for more detail.**

## APIs ##

  * you can create an object of Socket plugin in JavaScript using following code block

` var socketObj = new mcrux.socket();  `
  * this creates a new socket object. you can call various methods which are provided.

` socketObj.connect(hostname, port); `
  * hostname :String: the hostname to connect. ( you can also pass valid IP Address)
  * port :Number: the port number to connect.
  * connect thread will be spawned and "onConnectComplete" event raised at the end of the connect attempt.

` socketObj.send(data); `
  * data :String: the data to be sent to the socket.
  * it is a blocking call and will return only when the data sending is completed.

` socketObj.disconnect(); `
  * this method is called for disconnecting the socket connection.

## Event Listeners ##

there are following event listeners available.

onConnectComplete(event)
  * This Event is raised only after the connect is called.
  * parameters:event
  * event.connected :Boolean: the connect result
  * event.hostname :String: the hostname given in the connect parameter
  * event.port :Number: the port given in the connect parameter

onRead(event)
  * This Event is raised when the socket is in connected state and it receives any data from the server.
  * parameters:event
  * event.data :String: the data received by the socket.

## How To Register Event Listeners ##

addEventListener(eventName, HandlerFunction)
  * **EventName** :String: name of the event which you want to handle.
  * **HandlerFunction** :function: function which you want to be called.

removeEventListener(eventName, HandlerFunction)
  * **EventName** :String: name of the event which you want to handle.
  * **HandlerFunction** :function: function which you want to remove from the call list.