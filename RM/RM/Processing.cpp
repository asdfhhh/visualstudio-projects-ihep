// Processing.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "RMDlg.h"
#include "Processing.h"
#include "afxdialogex.h"


// Processing dialog

IMPLEMENT_DYNAMIC(Processing, CDialogEx)

Processing::Processing(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

Processing::~Processing()
{
}

void Processing::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
}


BEGIN_MESSAGE_MAP(Processing, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &Processing::OnNMCustomdrawProgress1)
END_MESSAGE_MAP()


// Processing message handlers


void Processing::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
