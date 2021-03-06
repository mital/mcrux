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

#ifndef _MJSCOREOBJECT_H_
#define _MJSCOREOBJECT_H_

#include <set>
#include <string>

#include "jscore/MJSCoreObjectAbstract.h"
#include "jscore/MJSCoreMethod.h"


class MCRUX_API MJSCoreObject
	: public MJSCoreObjectAbstract
{
protected:
	JSObjectRef object;
	std::string className;

	static JSObjectRef ConstructorCallback(JSContextRef ctx,
		JSObjectRef constructor,
		size_t argumentCount,
		const JSValueRef arguments[],
		JSValueRef* exception);

	virtual void construct(const MObjectArray& args, MObjectContainer& resultContainer);

public:

	MJSCoreObject(JSContextRef _ctx,
		const std::string & _className = "MJSCoreObject",
		const bool _hasConstructor = false);

	MJSCoreObject(JSContextRef _ctx, JSObjectRef _object);
	virtual ~MJSCoreObject();

	void setProperty(const std::string & name, MObject * obj);

	template <typename T>
	void setProperty(JSContextRef _ctx, const char *name, void (T::*method)(const MObjectArray&, MObjectContainer&))
	{
		MCruxMethodCallback* callback = NewCallback<T, const MObjectArray&, MObjectContainer&>(static_cast<T*>(this), method);
		this->setProperty(name, new MJSCoreMethod(_ctx, callback));
	}

	MObject * getProperty(const std::string & name);
	bool hasProperty(const std::string & name);
	void getPropertyNames(set<string> & properties);

	virtual JSValueRef getJSValue();
	virtual JSObjectRef getJSObject();
	const char * toString();
	const char * getClassName() const;
	JSObjectCallAsConstructorCallback getConstructor() const;

	void protect();
	void unprotect();
};

#endif // _MJSCOREOBJECT_H_
