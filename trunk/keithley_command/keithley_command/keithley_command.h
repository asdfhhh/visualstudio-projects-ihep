// keithley_command.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Ckeithley_commandApp:
// �йش����ʵ�֣������ keithley_command.cpp
//

class Ckeithley_commandApp : public CWinApp
{
public:
	Ckeithley_commandApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Ckeithley_commandApp theApp;