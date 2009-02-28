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
	saxParserObj.addEventListener("StartElementHandler", startElementHandler);
	saxParserObj.addEventListener("EndElementHandler", endElementHandler);
	saxParserObj.addEventListener("CharactersHandler", charactersHandler);

	saxParserObj.xmlParseChunk('<array:foobar size="5">mydata</array:foobar>');

	var ret = saxParserObj.removeEventListener("StartElementHandler", startElementHandler);
	if(ret == false)
	{
		alert("remove failed");
	}
	var ret = saxParserObj.removeEventListener("EndElementHandler", endElementHandler);
	if(ret == false)
	{
		alert("remove failed");
	}
	var ret = saxParserObj.removeEventListener("CharactersHandler", charactersHandler);
	if(ret == false)
	{
		alert("remove failed");
	}
}