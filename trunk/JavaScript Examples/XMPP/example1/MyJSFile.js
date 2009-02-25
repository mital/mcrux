function ReadDataHandler(event)
{
	alert("stanza Handler Called");
	alert(event.data);
}

function myFunction()
{
	alert("xmpp Example ! creating xmppObj object with new operator");

	var socketObj = new socket();
	var ret = socketObj.Connect("localhost", 5222);
	socketObj.addEventListener("ReadDataHandler", ReadDataHandler);

	if (ret == true)
	{
		alert("Connect call returned true");
		socketObj.Send("<?xml version=\"1.0\"?>");
		socketObj.Send("<stream:stream to=\"mital-lappy\" xml:lang=\"en\" xmlns=\"jabber:client\" xmlns:stream=\"http://etherx.jabber.org/streams\" version=\"1.0\">");
	}
}
