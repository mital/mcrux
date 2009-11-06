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

#include <string>
using namespace std;
#include "MCruxQTWindow.h"


MCruxQTWindow::MCruxQTWindow(const MCruxWindowConfiguration * _config)
	: MCruxWindow(_config)
{
  this->show();
}


MCruxQTWindow::~MCruxQTWindow()
{
}

int MCruxQTWindow::ShowWindow() const
{
	return -1;
}


int MCruxQTWindow::HideWindow() const
{
	return -1;
}


int MCruxQTWindow::UpdateWindow() const
{
	return -1;
}


void MCruxQTWindow::resize() const
{
}
