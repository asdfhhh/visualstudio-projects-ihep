// DlgProxy.cpp : ʵ���ļ�
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
	
	// ΪʹӦ�ó������Զ��� 
	//	�����ڻ״̬ʱһֱ�������У����캯������ AfxOleLockApp��
	AfxOleLockApp();

	// ͨ��Ӧ�ó���
	//  ��������ָ�������ʶԻ������ô�����ڲ�ָ��
	//  ָ��Ի��򣬲����öԻ���ĺ���ָ��ָ��
	//  �ô���
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
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	// 	������������ AfxOleUnlockApp��
	//  ���������������⣬�⻹���������Ի���
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void Ckeithley1DlgAutoProxy::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(Ckeithley1DlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(Ckeithley1DlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_Ikeithley1 ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID �����븽���� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {B036E18F-59E5-466A-B6CF-D357C36BCAF7}
static const IID IID_Ikeithley1 =
{ 0xB036E18F, 0x59E5, 0x466A, { 0xB6, 0xCF, 0xD3, 0x57, 0xC3, 0x6B, 0xCA, 0xF7 } };

BEGIN_INTERFACE_MAP(Ckeithley1DlgAutoProxy, CCmdTarget)
	INTERFACE_PART(Ckeithley1DlgAutoProxy, IID_Ikeithley1, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 ���ڴ���Ŀ�� StdAfx.h �ж���
// {0D9B53D0-03E1-45E9-B372-7128E96857F6}
IMPLEMENT_OLECREATE2(Ckeithley1DlgAutoProxy, "keithley1.Application", 0xd9b53d0, 0x3e1, 0x45e9, 0xb3, 0x72, 0x71, 0x28, 0xe9, 0x68, 0x57, 0xf6)


// Ckeithley1DlgAutoProxy ��Ϣ�������
