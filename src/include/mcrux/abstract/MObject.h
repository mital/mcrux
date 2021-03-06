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

#ifndef _MOBJECT_H_
#define _MOBJECT_H_


#ifdef WIN32
#include <mcrux/abstract/callback.h>
#include <win32/MCruxExport.h>

class MObject;
class MObjectArray;
class MObjectContainer;

typedef Callback2<const MObjectArray&, MObjectContainer &>::Type MCruxMethodCallback;

#else // for linux

#define MCRUX_API

#endif

class MCRUX_API MObject
{
public:
	MObject();
	virtual ~MObject();
};

#endif // _MOBJECT_H_
