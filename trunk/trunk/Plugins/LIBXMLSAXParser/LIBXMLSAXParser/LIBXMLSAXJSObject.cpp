#include "StdAfx.h"

#include "mcrux/JSStringUtils.h"

#include "LIBXMLSAXJSObject.h"


list<LIBXMLSAXJSObject *> LIBXMLSAXJSObject::saxParserObjects;


LIBXMLSAXJSObject::LIBXMLSAXJSObject()
: parser(this)
{
}


LIBXMLSAXJSObject::LIBXMLSAXJSObject(JSContextRef ctx,
									 JSObjectRef constructor,
									 size_t argumentCount,
									 const JSValueRef arguments[],
									 JSValueRef* exception)
									 : parser(this)
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
	::MessageBoxA(0, "constructor called", "test", MB_OK);
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

const char * LIBXMLSAXJSObject::getName() const
{
	static string name("libxml_saxparser");
	return name.c_str();
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


JSStaticFunction * LIBXMLSAXJSObject::getJSObjectFunctions() const
{
	static JSStaticFunction JSDefaultFunctions[]
	= {
		{"xmlParseChunk", LIBXMLSAXJSObject::xmlParseChunk, 0},
		{"addEventListener", LIBXMLSAXJSObject::addEventListener, 0},
		{"removeEventListener", LIBXMLSAXJSObject::removeEventListener, 0},
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


JSValueRef LIBXMLSAXJSObject::removeEventListener(JSContextRef ctx,
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
			bool bRet = saxObj->removeEventListener(eventName, eventHandler);
			return JSValueMakeBoolean(ctx, bRet);
		}
	}
	return JSValueMakeBoolean(ctx, false);
}


int LIBXMLSAXJSObject::xmlParseChunk(const string & data)
{
	return parser.xmlParseChunk(data);
}


void getAttributesFrom(const xmlChar ** atts, map<string, string>& attributes)
{
	for(int i=0; ; i+=2)
	{
		if(atts[i] == NULL)
		{
			break;
		}
		string key = (char*)atts[i];
		string value = (char*)atts[i+1];
		attributes[key] = value;
	}
}


void LIBXMLSAXJSObject::handleStartElement(const xmlChar * name, const xmlChar ** atts)
{
	if (!MCruxPlugin::webView)
	{
		::MessageBoxA(0, "startElementHandler webview not set", "saxparser", MB_OK);
		// TODO: return error
		return;
	}
	map<string, string> attributes;
	getAttributesFrom(atts, attributes);
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

			JSObjectRef jsAttrs = JSObjectMake(ctx, NULL, NULL);
			for(map<string, string>::const_iterator
				oIter = attributes.begin();
				oIter != attributes.end();
			oIter++)
			{
				JSStringRef key = JSStringCreateWithUTF8CString(oIter->first.c_str());
				JSStringRef value = JSStringCreateWithUTF8CString(oIter->second.c_str());
				JSObjectSetProperty(ctx, jsAttrs, key, JSValueMakeString(ctx, value), 0, 0);
			}

			JSStringRef attributesJS = JSStringCreateWithUTF8CString("attributes");
			JSObjectSetProperty(ctx, startElement, attributesJS, jsAttrs, 0, 0);

			JSObjectRef handler = getEventListener(START_ELEMENT_EVENT_NAME);
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

			JSObjectRef handler = getEventListener(END_ELEMENT_EVENT_NAME);
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

			JSObjectRef handler = getEventListener(CHARACTERS_EVENT_NAME);
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


bool LIBXMLSAXJSObject::removeEventListener(const string & eventName, JSObjectRef eventHandler)
{
	map<string, JSObjectRef>::iterator iter = eventMap.find(eventName);
	if (iter != eventMap.end() && iter->second == eventHandler)
	{
		eventMap.erase(iter);
		return true;
	}
	return false;
}
