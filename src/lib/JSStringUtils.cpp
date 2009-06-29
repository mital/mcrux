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

double getDoubleValueFrom(JSContextRef ctx, JSValueRef strValue)
{
	return JSValueToNumber(ctx, strValue, 0);
}