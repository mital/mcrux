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
#ifndef _MOBJECT_ARRAY_H_
#define _MOBJECT_ARRAY_H_

#include <vector>

using namespace std;

#include "MObject.h"


class MCRUX_API MObjectArray
{
	vector <MObject *> mArray;
public:
	MObjectArray();
	MObjectArray(const vector<MObject *> & _mArray);
	~MObjectArray();

	void setAt(size_t index, MObject* object);
	MObject* getAt(size_t index) const;

	size_t size() const;
};

#endif // _MOBJECT_ARRAY_H_