#pragma once

#include <iostream>

using namespace std;

#include <JavaScriptCore/JSStringRef.h>


namespace JSStringUtils
{
	string getStringValueFrom(JSContextRef ctx, JSValueRef strValue);
	double getDoubleValueFrom(JSContextRef ctx, JSValueRef strValue);
};