
// MMOnline.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include <Windows4Root.h>
#include "TApplication.h"

// CMMOnlineApp: 
// �йش����ʵ�֣������ MMOnline.cpp
//

class CMMOnlineApp : public CWinApp
{
public:
	CMMOnlineApp();

// ��д
public:
	virtual BOOL InitInstance();
	TApplication * gMyRootApp;
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMMOnlineApp theApp;