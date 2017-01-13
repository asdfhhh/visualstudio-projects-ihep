
// MFCApplication_root.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include <Windows4Root.h>
#include "TApplication.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TF1.h"
#include "TF2.h"
#include "TF3.h"
#include "TH1.h"
#include "TH2.h"
#include "TStyle.h"
#include <sstream>

// CMFCApplication_rootApp: 
// 有关此类的实现，请参阅 MFCApplication_root.cpp
//

class CMFCApplication_rootApp : public CWinApp
{
public:
	CMFCApplication_rootApp();

// 重写
public:
	virtual BOOL InitInstance();
	TApplication * gMyRootApp;

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication_rootApp theApp;