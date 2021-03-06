#pragma once

#include <map>
#include <list>
#include <string>

using namespace std;

#define START_ELEMENT_EVENT_NAME "onStartElement"
#define END_ELEMENT_EVENT_NAME "onEndElement"
#define CHARACTERS_EVENT_NAME "onCharacters"

#include "mcrux/MCruxPlugin.h"
#include "SAXParser.h"

class LIBXMLSAXJSObject :
	public MCruxPlugin
{
	SAXParser parser;
	map<string, JSObjectRef> eventMap;

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

	static JSValueRef addEventListener(JSContextRef ctx,
		JSObjectRef function,
		JSObjectRef thisObject,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef *exception);

	static JSValueRef removeEventListener(JSContextRef ctx,
		JSObjectRef function,
		JSObjectRef thisObject,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef *exception);

	int xmlParseChunk(const string & data);

	// event listener related methods
	bool addEventListener(JSContextRef ctx, const string & eventName, JSObjectRef eventHandler);
	bool removeEventListener(JSContextRef ctx, const string & eventName, JSObjectRef eventHandler);
	JSObjectRef getEventListener(const string & eventName) const;

public:

	LIBXMLSAXJSObject();

	LIBXMLSAXJSObject(JSContextRef ctx,
		JSObjectRef constructor,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef* exception);

	virtual ~LIBXMLSAXJSObject();

	virtual const char * getName() const;
	virtual JSStaticFunction * getStaticFunctions() const;;
	virtual JSObjectCallAsConstructorCallback getConstructor() const;
	virtual JSStaticFunction * getJSObjectFunctions() const;

	void handleStartElement(const xmlChar * name, const xmlChar ** atts);
	void handleEndElement(const xmlChar * name);
	void handleCharacters(const xmlChar * ch, int len);

};
