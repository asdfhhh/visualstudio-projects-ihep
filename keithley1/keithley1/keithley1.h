// keithley1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Ckeithley1App:
// �йش����ʵ�֣������ keithley1.cpp
//

class Ckeithley1App : public CWinApp
{
public:
	Ckeithley1App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Ckeithley1App theApp;