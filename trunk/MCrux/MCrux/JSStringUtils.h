#pragma once

#include <iostream>

using namespace std;

#include <JavaScriptCore/JSStringRef.h>
#include "MCruxExport.h"


string MCRUX_API getStringValueFrom(JSContextRef ctx, JSValueRef strValue);
double MCRUX_API getDoubleValueFrom(JSContextRef ctx, JSValueRef strValue);