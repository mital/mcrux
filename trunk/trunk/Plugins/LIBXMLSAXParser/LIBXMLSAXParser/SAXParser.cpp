#include "StdAfx.h"
#include <winsock2.h>

#include "LIBXMLSAXJSObject.h"
#include "SAXParser.h"


SAXParser::SAXParser(LIBXMLSAXJSObject* _jsObjectContainer)
: jsObjectContainer(_jsObjectContainer),
  saxhdlr(new xmlSAXHandler()),
  ctxt(NULL)
{
	xmlRegisterDefaultOutputCallbacks();
	ZeroMemory( saxhdlr, sizeof( xmlSAXHandler ) );

	saxhdlr->startElement = SAXParser::startElementHandler;
	saxhdlr->endElement = SAXParser::endElementHandler;
	saxhdlr->characters = SAXParser::charactersHandler;

	ctxt = xmlCreatePushParserCtxt( saxhdlr, this, NULL, 0, NULL );
}

SAXParser::~SAXParser()
{
	xmlFreeParserCtxt(ctxt);
	delete saxhdlr;
}

void SAXParser::startElementHandler(void * ctx, const xmlChar * name, const xmlChar ** atts)
{
	SAXParser * parser = (SAXParser *) ctx;
	if(parser)
	{
		parser->handleStartElement(name, atts);
	}
}


void SAXParser::endElementHandler(void * ctx, const xmlChar * name)
{
	SAXParser * parser = (SAXParser *) ctx;
	if(parser)
	{
		parser->handleEndElement(name);
	}
}


void SAXParser::charactersHandler(void * ctx, const xmlChar * ch, int len)
{
	SAXParser * parser = (SAXParser *) ctx;
	if(parser)
	{
		parser->handleCharacters(ch, len);

	}
}


int SAXParser::xmlParseChunk(const string & data)
{
	int ret = ::xmlParseChunk( ctxt, data.c_str(), (int)data.size(), 0 );
	return ret;
}

void SAXParser::handleStartElement(const xmlChar * name, const xmlChar ** atts)
{
	if(jsObjectContainer)
	{
		jsObjectContainer->handleStartElement(name, atts);
	}
}


void SAXParser::handleEndElement(const xmlChar * name)
{
	if(jsObjectContainer)
	{
		jsObjectContainer->handleEndElement(name);
	}
}


void SAXParser::handleCharacters(const xmlChar * ch, int len)
{
	if(jsObjectContainer)
	{
		jsObjectContainer->handleCharacters(ch, len);
	}
}
