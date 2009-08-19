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
#include "JSStringUtils.h"


char * getStringValueFrom(JSContextRef ctx, JSValueRef strValue)
{
	JSStringRef str = JSValueToStringCopy(ctx, strValue, 0);
	size_t length = JSStringGetMaximumUTF8CStringSize(str);
	char* buffer = new char[length];
	JSStringGetUTF8CString(str, buffer, length);
	return buffer;
}

char * getStringValueFrom(JSContextRef ctx, JSStringRef strValue)
{
	size_t length = JSStringGetMaximumUTF8CStringSize(strValue);
	char* buffer = new char[length];
	JSStringGetUTF8CString(strValue, buffer, length);
	return buffer;
}


double getDoubleValueFrom(JSContextRef ctx, JSValueRef strValue)
{
	return JSValueToNumber(ctx, strValue, 0);
}