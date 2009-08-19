#pragma once

#include <iostream>

using namespace std;

#include <libxml/globals.h>
#include <libxml/xmlreader.h>

class LIBXMLSAXJSObject;

class SAXParser
{
	LIBXMLSAXJSObject* jsObjectContainer;
	xmlSAXHandlerPtr saxhdlr;
	xmlParserCtxtPtr ctxt;
	static void startElementHandler( void * ctx, const xmlChar * name, const xmlChar ** atts );
	static void endElementHandler( void * ctx, const xmlChar * name );
	static void charactersHandler( void * ctx, const xmlChar * ch, int len );

public:
	SAXParser(LIBXMLSAXJSObject* _jsObjectContainer);
	~SAXParser();
	int xmlParseChunk(const string & data);

	void handleStartElement(const xmlChar * name, const xmlChar ** atts);
	void handleEndElement(const xmlChar * name);
	void handleCharacters(const xmlChar * ch, int len);

};
