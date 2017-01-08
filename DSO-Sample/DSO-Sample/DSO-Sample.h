
// DSO-Sample.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include <Windows4Root.h>
#include "TApplication.h"


// CDSOSampleApp:
// See DSO-Sample.cpp for the implementation of this class
//

class CDSOSampleApp : public CWinApp
{
public:
	CDSOSampleApp();

// Overrides
public:
	virtual BOOL InitInstance();
	TApplication * gMyRootApp;
// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CDSOSampleApp theApp;