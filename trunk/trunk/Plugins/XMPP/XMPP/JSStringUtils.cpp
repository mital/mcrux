#include "stdafx.h"
#include "JSStringUtils.h"


namespace JSStringUtils
{
	string getStringValueFrom(JSContextRef ctx, JSValueRef strValue)
	{
		JSStringRef str = JSValueToStringCopy(ctx, strValue, 0);
		size_t length = JSStringGetMaximumUTF8CStringSize(str);
		char* buffer = new char[length];
		JSStringGetUTF8CString(str, buffer, length);
		string stdStr = buffer;
		delete[] buffer;
		return stdStr;
	}

	double getDoubleValueFrom(JSContextRef ctx, JSValueRef strValue)
	{
		return JSValueToNumber(ctx, strValue, 0);
	}

};