// keithley2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Ckeithley2App:
// �йش����ʵ�֣������ keithley2.cpp
//

class Ckeithley2App : public CWinApp
{
public:
	Ckeithley2App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Ckeithley2App theApp;