function startElementHandler(event)
{
	alert("startelement called yepppppppppppppppppppppieeeeeeeeeeeeeeeeeeee");
	alert(event.tag);
	alert(event.attributes);
	alert(event.attributes.size);
}


function endElementHandler(event)
{
	alert("endelement called yepppppppppppppppppppppieeeeeeeeeeeeeeeeeeee");
	alert(event.tag);
}


function charactersHandler(event)
{
	alert("charactersHandler called yepppppppppppppppppppppieeeeeeeeeeeeeeeeeeee");
	alert(event.characters);
}


function myFunction()
{
	alert("libxml saxparser Example !");
	var saxParserObj = new mcrux.libxml_saxparser();
	alert("saxparser created successfully now calling xmlParseChunk() over it");

	alert(saxParserObj);
	saxParserObj.addEventListener("onStartElement", startElementHandler);
	saxParserObj.addEventListener("onEndElement", endElementHandler);
	saxParserObj.addEventListener("onCharacters", charactersHandler);

	saxParserObj.xmlParseChunk('<array:foobar size="5">mydata</array:foobar>');

	saxParserObj.removeEventListener("onStartElement", startElementHandler);
	saxParserObj.removeEventListener("onEndElement", endElementHandler);
	saxParserObj.removeEventListener("onCharacters", charactersHandler);
}