#pragma once

#include <iostream>

using namespace std;

#include "MCruxExport.h"


class MCRUX_API MCrux
{
	void Initialize();

	void UnInitialize();

public:

	MCrux();
	~MCrux();

	bool InitializeAndRunWith(const string & mcruxAppConfigFileName);
};
