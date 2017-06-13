// DlgProxy.cpp : 实现文件
//

#include "stdafx.h"
#include "keithley1.h"
#include "DlgProxy.h"
#include "keithley1Dlg.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif


// Ckeithley1DlgAutoProxy

IMPLEMENT_DYNCREATE(Ckeithley1DlgAutoProxy, CCmdTarget)

Ckeithley1DlgAutoProxy::Ckeithley1DlgAutoProxy()
{
	EnableAutomation();
	
	// 为使应用程序在自动化 
	//	对象处于活动状态时一直保持运行，构造函数调用 AfxOleLockApp。
	AfxOleLockApp();

	// 通过应用程序
	//  的主窗口指针来访问对话框。设置代理的内部指针
	//  指向对话框，并设置对话框的后向指针指向
	//  该代理。
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(Ckeithley1Dlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(Ckeithley1Dlg)))
		{
			m_pDialog = reinterpret_cast<Ckeithley1Dlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

Ckeithley1DlgAutoProxy::~Ckeithley1DlgAutoProxy()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	// 	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void Ckeithley1DlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清除代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(Ckeithley1DlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(Ckeithley1DlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_Ikeithley1 的支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须与附加在 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {B036E18F-59E5-466A-B6CF-D357C36BCAF7}
static const IID IID_Ikeithley1 =
{ 0xB036E18F, 0x59E5, 0x466A, { 0xB6, 0xCF, 0xD3, 0x57, 0xC3, 0x6B, 0xCA, 0xF7 } };

BEGIN_INTERFACE_MAP(Ckeithley1DlgAutoProxy, CCmdTarget)
	INTERFACE_PART(Ckeithley1DlgAutoProxy, IID_Ikeithley1, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏在此项目的 StdAfx.h 中定义
// {0D9B53D0-03E1-45E9-B372-7128E96857F6}
IMPLEMENT_OLECREATE2(Ckeithley1DlgAutoProxy, "keithley1.Application", 0xd9b53d0, 0x3e1, 0x45e9, 0xb3, 0x72, 0x71, 0x28, 0xe9, 0x68, 0x57, 0xf6)


// Ckeithley1DlgAutoProxy 消息处理程序
