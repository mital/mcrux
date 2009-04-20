function startElementHandler(event)
{
	alert("START ELEMENT Found with TAG: [" + event.tag + "] and attribute SIZE: [" +  event.attributes.size + "]");
}


function endElementHandler(event)
{
	alert("END ELEMENT Found with TAG: [" + event.tag + "]");
}


function charactersHandler(event)
{
	alert("CHARACTERS FOUND : [" + event.characters + "]");
}


function myFunction()
{
	alert("libxml saxparser Example !");
	var saxParserObj = new mcrux.libxml_saxparser();
	alert("calling xmlParseChunk()");

	saxParserObj.addEventListener("onStartElement", startElementHandler);
	saxParserObj.addEventListener("onEndElement", endElementHandler);
	saxParserObj.addEventListener("onCharacters", charactersHandler);

	saxParserObj.xmlParseChunk('<array:foobar size="5">mydata</array:foobar>');

	saxParserObj.removeEventListener("onStartElement", startElementHandler);
	saxParserObj.removeEventListener("onEndElement", endElementHandler);
	saxParserObj.removeEventListener("onCharacters", charactersHandler);
}