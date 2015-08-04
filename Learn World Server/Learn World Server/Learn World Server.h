
// Learn World Server.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CLearnWorldServerApp:
// See Learn World Server.cpp for the implementation of this class
//

class CLearnWorldServerApp : public CWinApp
{
public:
	CLearnWorldServerApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CLearnWorldServerApp theApp;