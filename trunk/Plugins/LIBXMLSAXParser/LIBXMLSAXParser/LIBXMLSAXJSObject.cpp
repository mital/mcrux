#include "StdAfx.h"

#include "mcrux/JSStringUtils.h"

#include "LIBXMLSAXJSObject.h"


list<LIBXMLSAXJSObject *> LIBXMLSAXJSObject::saxParserObjects;


LIBXMLSAXJSObject::LIBXMLSAXJSObject()
: parser(this),
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
		{"addEventListener", LIBXMLSAXJSObject::addEventListener, 0},
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

JSValueRef LIBXMLSAXJSObject::addEventListener(JSContextRef ctx,
													JSObjectRef function,
													JSObjectRef thisObject,
													size_t argumentCount,
													const JSValueRef arguments[],
													JSValueRef *exception)
{
	if(argumentCount == 2) // eventName, eventHandlerFunction
	{
		LIBXMLSAXJSObject * saxObj = (LIBXMLSAXJSObject*) JSObjectGetPrivate(thisObject);
		if(saxObj)
		{
			string eventName = getStringValueFrom(ctx, arguments[0]);
			JSObjectRef eventHandler = JSValueToObject(ctx, arguments[1], exception);
			bool bRet = saxObj->addEventListener(eventName, eventHandler);
			return JSValueMakeBoolean(ctx, bRet);
		}
	}
	return JSValueMakeBoolean(ctx, false);
}


bool LIBXMLSAXJSObject::setSAXParserCallBacks(JSObjectRef _startElementHandler,
											  JSObjectRef _endElementHandler,
											  JSObjectRef _charactersElementHandler)
{
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
	if (!MCruxPlugin::webView)
	{
		::MessageBoxA(0, "startElementHandler webview not set", "saxparser", MB_OK);
		// TODO: return error
		return;
	}
	IWebFrame * frame;
	HRESULT hr = MCruxPlugin::webView->mainFrame(&frame);
	if(SUCCEEDED(hr))
	{
		JSContextRef ctx = frame->globalContext();
		if(ctx)
		{
			JSObjectRef global = JSContextGetGlobalObject(ctx);
			JSObjectRef startElement = JSObjectMake(ctx, NULL, NULL);
			JSStringRef tagName = JSStringCreateWithUTF8CString((const char *)name);
			JSStringRef tag = JSStringCreateWithUTF8CString("tag");
			JSObjectSetProperty(ctx, startElement, tag, JSValueMakeString(ctx, tagName), 0, 0);

			JSObjectRef handler = getEventListener("StartElementHandler");
			if(handler)
			{
				JSObjectCallAsFunction(ctx, handler, global, 1, &startElement, 0);
			}

		}
	}
}


void LIBXMLSAXJSObject::handleEndElement(const xmlChar * name)
{
	if (!MCruxPlugin::webView)
	{
		::MessageBoxA(0, "endElementHandler webview not set", "saxparser", MB_OK);
		// TODO: return error
		return;
	}
	IWebFrame * frame;
	HRESULT hr = MCruxPlugin::webView->mainFrame(&frame);
	if(SUCCEEDED(hr))
	{
		JSContextRef ctx = frame->globalContext();
		if(ctx)
		{
			JSObjectRef global = JSContextGetGlobalObject(ctx);
			JSObjectRef endElement = JSObjectMake(ctx, NULL, NULL);
			JSStringRef tagName = JSStringCreateWithUTF8CString((const char *)name);
			JSStringRef tag = JSStringCreateWithUTF8CString("tag");
			JSObjectSetProperty(ctx, endElement, tag, JSValueMakeString(ctx, tagName), 0, 0);

			JSObjectRef handler = getEventListener("EndElementHandler");
			if(handler)
			{
				JSObjectCallAsFunction(ctx, handler, global, 1, &endElement, 0);
			}

		}
	}
}


void LIBXMLSAXJSObject::handleCharacters(const xmlChar * ch, int len)
{
	if (!MCruxPlugin::webView)
	{
		::MessageBoxA(0, "endElementHandler webview not set", "saxparser", MB_OK);
		// TODO: return error
		return;
	}
	IWebFrame * frame;
	HRESULT hr = MCruxPlugin::webView->mainFrame(&frame);
	if(SUCCEEDED(hr))
	{
		JSContextRef ctx = frame->globalContext();
		if(ctx)
		{
			string c((char *)ch, len);
			JSObjectRef global = JSContextGetGlobalObject(ctx);
			JSObjectRef charElement = JSObjectMake(ctx, NULL, NULL);
			JSStringRef charactersString = JSStringCreateWithUTF8CString((const char *)c.c_str());
			JSStringRef characters = JSStringCreateWithUTF8CString("characters");
			JSObjectSetProperty(ctx, charElement, characters, JSValueMakeString(ctx, charactersString), 0, 0);

			JSObjectRef handler = getEventListener("CharactersHandler");
			if(handler)
			{
				JSObjectCallAsFunction(ctx, handler, global, 1, &charElement, 0);
			}

		}
	}
}

bool LIBXMLSAXJSObject::addEventListener(const string & eventName, JSObjectRef eventHandler)
{
	eventMap[eventName] = eventHandler;
	return true;
}

JSObjectRef LIBXMLSAXJSObject::getEventListener(const string & eventName) const
{
	map<string, JSObjectRef>::const_iterator iter = eventMap.find(eventName);
	if (iter != eventMap.end())
	{
		return iter->second;
	}
	return NULL;
}