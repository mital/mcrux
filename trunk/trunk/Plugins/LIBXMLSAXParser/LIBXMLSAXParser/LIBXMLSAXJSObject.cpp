#include "StdAfx.h"

#include "mcrux/JSStringUtils.h"

#include "LIBXMLSAXJSObject.h"


list<LIBXMLSAXJSObject *> LIBXMLSAXJSObject::saxParserObjects;


LIBXMLSAXJSObject::LIBXMLSAXJSObject()
: parser(this),
  ctx(NULL),
  startElementHandler(NULL),
  endElementHandler(NULL),
  charactersElementHandler(NULL)
{
}


LIBXMLSAXJSObject::LIBXMLSAXJSObject(JSContextRef ctx,
									 JSObjectRef constructor,
									 size_t argumentCount,
									 const JSValueRef arguments[],
									 JSValueRef* exception)
									 : parser(this),
									   ctx(NULL),
									   startElementHandler(NULL),
									   endElementHandler(NULL),
									   charactersElementHandler(NULL)
{
}


LIBXMLSAXJSObject::~LIBXMLSAXJSObject()
{
}


JSObjectRef LIBXMLSAXJSObject::ConstructorCallback(JSContextRef ctx,
												   JSObjectRef constructor,
												   size_t argumentCount,
												   const JSValueRef arguments[],
												   JSValueRef* exception)
{
	::MessageBoxA(0, "libxml_saxparser constructor called", "test", MB_OK);
	// check for required arguments before creating the object
	if(argumentCount == 0)
	{
		LIBXMLSAXJSObject * newObj
			= new LIBXMLSAXJSObject(ctx, constructor, argumentCount, arguments, exception);
		saxParserObjects.push_back(newObj);
		return newObj->createJSObject(ctx);
	}
	// TODO: throw exception.
	return JSValueToObject(ctx, JSValueMakeUndefined(ctx), exception);

}

string LIBXMLSAXJSObject::getName() const
{
	static string name = "libxml_saxparser";
	return name;
}

JSObjectCallAsConstructorCallback LIBXMLSAXJSObject::getConstructor() const
{
	return LIBXMLSAXJSObject::ConstructorCallback;
}



JSStaticFunction * LIBXMLSAXJSObject::getStaticFunctions() const
{
	static JSStaticFunction JSDefaultFunctions[]
	= {
		{0, 0, 0}
	};
	return JSDefaultFunctions;
}


JSStaticFunction * LIBXMLSAXJSObject::getJSObjectStaticFunctions() const
{
	static JSStaticFunction JSDefaultFunctions[]
	= {
		{"xmlParseChunk", LIBXMLSAXJSObject::xmlParseChunk, 0},
		{"setSAXParserCallBacks", LIBXMLSAXJSObject::setSAXParserCallBacks, 0},
		{0, 0, 0}
	};
	return JSDefaultFunctions;
}

JSValueRef LIBXMLSAXJSObject::xmlParseChunk(JSContextRef ctx,
											JSObjectRef function,
											JSObjectRef thisObject,
											size_t argumentCount,
											const JSValueRef arguments[],
											JSValueRef *exception)
{
	int ret = -1;
	::MessageBoxA(0, "LIBXMLSAXJSObject.xmlparsechunk called.", "test", MB_OK);
	if(argumentCount == 1) // data
	{
		string data = getStringValueFrom(ctx, arguments[0]);
		LIBXMLSAXJSObject * saxObj = (LIBXMLSAXJSObject*) JSObjectGetPrivate(thisObject);
		if(saxObj)
		{
			ret = saxObj->xmlParseChunk(data);
		}
	}

	return JSValueMakeNumber(ctx, (double)ret);
}

JSValueRef LIBXMLSAXJSObject::setSAXParserCallBacks(JSContextRef ctx,
													JSObjectRef function,
													JSObjectRef thisObject,
													size_t argumentCount,
													const JSValueRef arguments[],
													JSValueRef *exception)
{
	::MessageBoxA(0, "LIBXMLSAXJSObject.setSAXParserCallBacks called.", "test", MB_OK);
	if(argumentCount == 3) // startElementHandler, endElementHandler, charactersHandler
	{
		LIBXMLSAXJSObject * saxObj = (LIBXMLSAXJSObject*) JSObjectGetPrivate(thisObject);
		if(saxObj)
		{
			bool bRet = saxObj->setSAXParserCallBacks(ctx,
				JSValueToObject(ctx, arguments[0], exception),
				JSValueToObject(ctx, arguments[1], exception),
				JSValueToObject(ctx, arguments[2], exception));
			return JSValueMakeBoolean(ctx, bRet);
		}
	}
	return JSValueMakeBoolean(ctx, false);
}


bool LIBXMLSAXJSObject::setSAXParserCallBacks(JSContextRef _ctx,
											  JSObjectRef _startElementHandler,
											  JSObjectRef _endElementHandler,
											  JSObjectRef _charactersElementHandler)
{
	ctx = _ctx;
	startElementHandler = _startElementHandler;
	endElementHandler = _endElementHandler;
	charactersElementHandler = _charactersElementHandler;
	return true;
}


int LIBXMLSAXJSObject::xmlParseChunk(const string & data)
{
	return parser.xmlParseChunk(data);
}

void LIBXMLSAXJSObject::handleStartElement(const xmlChar * name, const xmlChar ** atts)
{
	::MessageBoxA(0, "startElementHandler called", "saxparser", MB_OK);
	if(ctx)
	{
		//JSObjectRef global = JSContextGetGlobalObject(ctx);
		//JSObjectRef startElement = JSObjectMake(ctx, NULL, NULL);
		//JSStringRef tagName = JSStringCreateWithUTF8CString((const char *)name);
		//JSStringRef tag = JSStringCreateWithUTF8CString("tag");
		//JSObjectSetProperty(ctx, startElement, tag, JSValueMakeString(ctx, tagName), 0, 0);

		//JSObjectCallAsFunction(ctx, startElementHandler, global, 0, &startElement, 0);
		//JSObjectCallAsFunction(ctx, startElementHandler, global, 0, 0, 0);

	}
}


void LIBXMLSAXJSObject::handleEndElement(const xmlChar * name)
{
	::MessageBoxA(0, "endElementHandler called", "saxparser", MB_OK);
}


void LIBXMLSAXJSObject::handleCharacters(const xmlChar * ch, int len)
{
	::MessageBoxA(0, "charactersHandler called", "saxparser", MB_OK);
}
