
// MFCApplication_root.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
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
// �йش����ʵ�֣������ MFCApplication_root.cpp
//

class CMFCApplication_rootApp : public CWinApp
{
public:
	CMFCApplication_rootApp();

// ��д
public:
	virtual BOOL InitInstance();
	TApplication * gMyRootApp;

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication_rootApp theApp;