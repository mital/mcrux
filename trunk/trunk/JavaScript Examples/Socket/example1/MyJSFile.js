function onConnected(event)
{
	alert("onConnected Handler Called");
	alert(event.hostname);
	alert(event.port);
	socketObj.Send("<?xml version=\"1.0\"?>");
	socketObj.Send("<stream:stream to=\"mital-lappy\" xml:lang=\"en\" xmlns=\"jabber:client\" xmlns:stream=\"http://etherx.jabber.org/streams\" version=\"1.0\">");
}


function ReadDataHandler(event)
{
	alert("ReadDataHandler Handler Called");
	alert(event.data);
}

var socketObj;

function myFunction()
{
	alert("socket Example ! creating socketObj object with new operator");

	socketObj = new mcrux.socket();
	socketObj.addEventListener("onConnected", onConnected);
	var ret = socketObj.Connect("localhost", 5222);
	socketObj.addEventListener("onRead", ReadDataHandler);
}
