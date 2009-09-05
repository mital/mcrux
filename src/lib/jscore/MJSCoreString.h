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

#ifndef _MJSCORESTRING_H_
#define _MJSCORESTRING_H_

#include <iostream>

using namespace std;

#include "jscore/MJSCoreObjectAbstract.h"


class MCRUX_API MJSCoreString
	: public MJSCoreObjectAbstract
{
protected:
	std::string str;

public:

	MJSCoreString(JSContextRef _ctx, const std::string & _str);
	virtual ~MJSCoreString();

	virtual JSValueRef getJSValue();
	virtual JSObjectRef getJSObject();

	const char * toString();
};

#endif // _MJSCORESTRING_H_