#include "StdAfx.h"
#include "MCruxException.h"

MCruxException::MCruxException(const string & _msg)
: msg(_msg)
{
}

MCruxException::~MCruxException(void)
{
}

const char* MCruxException::what() const
{
	return msg.c_str();
}