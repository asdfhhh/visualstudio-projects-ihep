
// RM.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include <Windows4Root.h>
#include "TApplication.h"

// CRMApp: 
// �йش����ʵ�֣������ RM.cpp
//

class CRMApp : public CWinApp
{
public:
	CRMApp();

// ��д
public:
	virtual BOOL InitInstance();
	TApplication * gMyRootApp;

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRMApp theApp;