function stanzaHandler(data)
{
	alert("stanza Handler Called");
	alert(data);
}

function myFunction()
{
	alert("xmpp Example ! creating xmppObj object with new operator");
	var xmppObj = new xmpp();
	alert("xmppObj created successfully now calling Connect() over it");
	var ret = xmppObj.Connect("localhost", 5222);
	xmppObj.setStanzaHandler(stanzaHandler);
	if (ret == true)
	{
		alert("Connect call returned true");
		xmppObj.Send("<?xml version=\"1.0\"?>");
		xmppObj.Send("<stream:stream to=\"mital-lappy\" xml:lang=\"en\" xmlns=\"jabber:client\" xmlns:stream=\"http://etherx.jabber.org/streams\" version=\"1.0\">");
	}
	
}
