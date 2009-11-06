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

#ifndef _MCRUXQTWINDOW_H_
#define _MCRUXQTWINDOW_H_

#include <QtGui/QtGui>
#include <abstract/MCruxWindow.h>
#include <window/MCruxWindowConfiguration.h>

//#include "MCruxWebView.h"
//#include "plugin/MCruxPluginManager.h"


class MCruxQTWindow
  : public QWidget,
  public MCruxWindow
{
#ifdef WIN32
private:
	// webView
	MCruxWebView webView;
#else
  Q_OBJECT

  // TODO: Add Qwebview class
#endif

public:

	MCruxQTWindow(const MCruxWindowConfiguration * _config);
	virtual ~MCruxQTWindow();

	virtual int ShowWindow() const;
	virtual int HideWindow() const;
	virtual int UpdateWindow() const;
	virtual void resize() const;
};

#endif // _MCRUXQTWINDOW_H_
