#pragma once

#include <iostream>

using namespace std;

#include <JavaScriptCore/JSStringRef.h>
#include "MCruxExport.h"


MCRUX_API char * getStringValueFrom(JSContextRef ctx, JSValueRef strValue);
MCRUX_API double getDoubleValueFrom(JSContextRef ctx, JSValueRef strValue);