function startElementHandler()
{
	alert("startelement called");
	//alert(element);
	//alert(element.tag);
}


function endElementHandler()
{
}


function charactersHandler()
{
}


function myFunction()
{
	alert("libxml saxparser Example !");
	var saxParserObj = new libxml_saxparser();
	alert("saxparser created successfully now calling xmlParseChunk() over it");
	//saxParserObj.xmlParseChunk('<stream:stream xmlns:stream="http://etherx.jabber.org/streams" xmlns="jabber:client" from="dv-mital-v" id="87b96c50" xml:lang="en" version="1.0">');
	saxParserObj.setSAXParserCallBacks(startElementHandler, endElementHandler, charactersHandler);
	saxParserObj.xmlParseChunk('<array size="5">mydata</array>');
}
