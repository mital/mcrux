/**
 * copyright (C) 2009 Mital Vora. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of MCrux nor the names of its contributors may be 
 *     used to endorse or promote products derived from this software 
 *     without specific prior written permission.
 *
 * @author: Mital Vora.
 **/

#include "stdafx.h"
#include "jscore/JSStringUtils.h"
#include "jscore/MJSCoreUtils.h"
#include "jscore/MJSCoreObjectFactory.h"

/*
 * Copyright 2008 Google Inc.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

/*
 * The following takes the prototype from the Function constructor, this allows
 * us to easily support call and apply on our objects that support CallAsFunction.
 *
 * NOTE: The return value is not protected.
 */

JSValueRef GetFunctionPrototype(JSContextRef jsContext, JSValueRef* exception) 
{
	JSObjectRef globalObject = JSContextGetGlobalObject(jsContext);
	JSStringRef fnPropName = JSStringCreateWithUTF8CString("Function");
	JSValueRef fnCtorValue = JSObjectGetProperty(jsContext, globalObject, fnPropName, exception);
	JSStringRelease(fnPropName);
	if (fnCtorValue)
	{
		JSObjectRef fnCtorObject = JSValueToObject(jsContext, fnCtorValue, exception);
		if (fnCtorObject)
		{
			JSStringRef protoPropName = JSStringCreateWithUTF8CString("prototype");
			JSValueRef fnPrototype = JSObjectGetProperty(jsContext, fnCtorObject,
				protoPropName, exception);
			JSStringRelease(protoPropName);
			if (fnPrototype)
			{
				return fnPrototype;
			}
		}
	}
	return JSValueMakeUndefined(jsContext);
}

void get_property_names_cb(
	JSContextRef js_context,
	JSObjectRef js_object,
	JSPropertyNameAccumulatorRef js_properties)
{
	MJSCoreObjectAbstract* mJSCoreObjectAbstract = static_cast<MJSCoreObjectAbstract*>(JSObjectGetPrivate(js_object));
	if (mJSCoreObjectAbstract && mJSCoreObjectAbstract->isObject())
	{
		MJSCoreObject * mJSCoreObject = dynamic_cast<MJSCoreObject *>(mJSCoreObjectAbstract);
		set<string> properties;
		mJSCoreObject->getPropertyNames(properties);
		for (set<string>::iterator oIter = properties.begin();
			oIter != properties.end();
			oIter++)
		{
			JSStringRef name = JSStringCreateWithUTF8CString((*oIter).c_str());
			JSPropertyNameAccumulatorAddName(js_properties, name);
			JSStringRelease(name);
		}
	}
}


void finalize_cb(JSObjectRef js_object)
{
	MJSCoreObjectAbstract* mJSCoreObjectAbstract = static_cast<MJSCoreObjectAbstract*>(JSObjectGetPrivate(js_object));
	delete mJSCoreObjectAbstract;
}


bool has_property_cb(
	JSContextRef js_context,
	JSObjectRef js_object,
	JSStringRef js_property)
{
	MJSCoreObjectAbstract* mJSCoreObjectAbstract = static_cast<MJSCoreObjectAbstract*>(JSObjectGetPrivate(js_object));
	if (mJSCoreObjectAbstract && mJSCoreObjectAbstract->isObject())
	{
		MJSCoreObject * mJSCoreObject = dynamic_cast<MJSCoreObject *>(mJSCoreObjectAbstract);
		std::string strName = getStringValueFrom(js_context, js_property);

		if (mJSCoreObject->hasProperty(strName))
		{
			return true;
		}
	}
	return false;
}


JSValueRef get_property_cb(
	JSContextRef js_context,
	JSObjectRef js_object,
	JSStringRef js_property,
	JSValueRef* js_exception)
{
	MJSCoreObjectAbstract* mJSCoreObjectAbstract = static_cast<MJSCoreObjectAbstract*>(JSObjectGetPrivate(js_object));
	if (mJSCoreObjectAbstract && mJSCoreObjectAbstract->isObject())
	{
		MJSCoreObject * mJSCoreObject = dynamic_cast<MJSCoreObject *>(mJSCoreObjectAbstract);
		std::string name = getStringValueFrom(js_context, js_property);
		try
		{
			MJSCoreObjectAbstract * mProperty = dynamic_cast<MJSCoreObjectAbstract*>(mJSCoreObject->getProperty(name));
			if(mProperty)
			{
				return mProperty->getJSValue();
			}
		}
		catch (const std::exception &e)
		{
			//TODO: throw error. 
			std::string error = e.what();
		}
		catch (...)
		{
			//TODO: throw error. 
			std::string error = "Unknown error";
		}
	}
	return JSValueMakeUndefined(js_context);
}

bool set_property_cb(
	JSContextRef js_context,
	JSObjectRef js_object,
	JSStringRef js_property,
	JSValueRef js_value,
	JSValueRef* js_exception)
{
	bool success = false;
	MJSCoreObjectAbstract* mJSCoreObjectAbstract = static_cast<MJSCoreObjectAbstract*>(JSObjectGetPrivate(js_object));
	if (mJSCoreObjectAbstract && mJSCoreObjectAbstract->isObject())
	{
		MJSCoreObject * mJSCoreObject = dynamic_cast<MJSCoreObject *>(mJSCoreObjectAbstract);

		std::string name = getStringValueFrom(js_context, js_property);
		try
		{
			MObject * mProperty = MJSCoreObjectFactory::getMObject(js_value);
			mJSCoreObject->setProperty(name, mProperty);
			success = true;
		}
		catch (const std::exception &e)
		{
			//TODO: throw error. 
			std::string error = e.what();
		}
		catch (...)
		{
			//TODO: throw error. 
			std::string error = "Unknown error";
		}
	}
	return success;
}


JSValueRef call_as_function_cb(
	JSContextRef js_context,
	JSObjectRef js_function,
	JSObjectRef js_this,
	size_t num_args,
	const JSValueRef js_args[],
	JSValueRef* js_exception)
{
	MJSCoreObjectAbstract* mJSCoreObjectAbstract = static_cast<MJSCoreObjectAbstract*>(JSObjectGetPrivate(js_function));
	if (mJSCoreObjectAbstract)
	{
		MJSCoreMethod * mJSCoreMethod = dynamic_cast<MJSCoreMethod *>(mJSCoreObjectAbstract);
		if (mJSCoreMethod)
		{
			MObjectArray args;

			for (size_t i = 0; i < num_args; i++) {
				args.setAt(i, MJSCoreObjectFactory::getMObject(js_args[i]));
			}

			MJSCoreObjectAbstract * result = NULL;
			try
			{
				result = mJSCoreMethod->invoke(args);
			}
			catch (const std::exception &e)
			{
				string error = e.what();
				// TODO: throw error.
			}
			catch (...)
			{
				string error = "Unknown Exception";
				// TODO: throw error.
			}

			if (result)
			{
				return result->getJSValue();
			}
		}
	}
	return JSValueMakeUndefined(js_context);
}


JSValueRef toJSValue(JSContextRef context, MJSCoreMethod * method_obj)
{
	if (method_class == NULL)
	{
		JSClassDefinition js_class_def = kJSClassDefinitionEmpty;
		js_class_def.className = "Function";
		js_class_def.getPropertyNames = get_property_names_cb;
		js_class_def.finalize = finalize_cb;
		js_class_def.hasProperty = has_property_cb;
		js_class_def.getProperty = get_property_cb;
		js_class_def.setProperty = set_property_cb;
		js_class_def.callAsFunction = call_as_function_cb;
		method_class = JSClassCreate(&js_class_def);
	}
	JSObjectRef jsMethod = JSObjectMake(context, method_class, new MJSCoreMethod(context, method_obj->getMethod()));
	JSValueRef fnProtoValue = GetFunctionPrototype(context, NULL);
	JSObjectSetPrototype(context, jsMethod, fnProtoValue);
	return jsMethod;
}
