var socketObj;

function onConnectComplete(event)
{
	alert("onConnected Handler Called");
	alert(event.hostname);
	alert(event.port);
	socketObj.send("<?xml version=\"1.0\"?>");
	socketObj.send("<stream:stream to=\"mital-lappy\" xml:lang=\"en\" xmlns=\"jabber:client\" xmlns:stream=\"http://etherx.jabber.org/streams\" version=\"1.0\">");
}


function ReadDataHandler(event)
{
	alert("ReadDataHandler Handler Called");
	alert(event.data);
}

function myFunction()
{
	alert("socket Example ! creating socketObj object with new operator");

    window.open("http://www.google.com");
//	socketObj = new mcrux.socket();
//	socketObj.addEventListener("onConnectComplete", onConnectComplete);
//	var ret = socketObj.connect("localhost", 5222);
//	socketObj.addEventListener("onRead", ReadDataHandler);
}
