#pragma once

#include <list>

using namespace std;

#include "mcrux/MCruxPlugin.h"
#include "SAXParser.h"

class LIBXMLSAXJSObject :
	public MCruxPlugin
{
	SAXParser parser;
	JSObjectRef startElementHandler;
	JSObjectRef endElementHandler;
	JSObjectRef charactersElementHandler;

	static list<LIBXMLSAXJSObject *> saxParserObjects;

	static JSObjectRef ConstructorCallback(JSContextRef ctx,
		JSObjectRef constructor,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef* exception);

	static JSValueRef xmlParseChunk(JSContextRef ctx,
		JSObjectRef function,
		JSObjectRef thisObject,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef *exception);

	static JSValueRef setSAXParserCallBacks(JSContextRef ctx,
		JSObjectRef function,
		JSObjectRef thisObject,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef *exception);

	int xmlParseChunk(const string & data);

	bool setSAXParserCallBacks(JSObjectRef _startElementHandler,
		JSObjectRef _endElementHandler,
		JSObjectRef _charactersElementHandler);

public:

	LIBXMLSAXJSObject();

	LIBXMLSAXJSObject(JSContextRef ctx,
		JSObjectRef constructor,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef* exception);

	virtual ~LIBXMLSAXJSObject();

	virtual string getName() const;
	virtual JSStaticFunction * getStaticFunctions() const;;
	virtual JSObjectCallAsConstructorCallback getConstructor() const;
	virtual JSStaticFunction * getJSObjectStaticFunctions() const;

	void handleStartElement(const xmlChar * name, const xmlChar ** atts);
	void handleEndElement(const xmlChar * name);
	void handleCharacters(const xmlChar * ch, int len);

};
