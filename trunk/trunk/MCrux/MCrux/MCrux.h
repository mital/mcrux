#pragma once

#include <iostream>

using namespace std;

#include "MCruxExport.h"


class MCRUX_API MCrux
{
public:

	MCrux();
	~MCrux();

	void Initialize();

	void UnInitialize();

	bool InitializeAndRunWith(const string & mcruxAppConfigFileName);
};
