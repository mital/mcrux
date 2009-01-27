#pragma once
#include <iostream>

using namespace std;

class MCruxException
	: public exception
{
	const string msg;
public:

	MCruxException(const string & _msg);

	~MCruxException();

	virtual const char *what() const;
};
