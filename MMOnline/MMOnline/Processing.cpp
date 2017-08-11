// Processing.cpp : implementation file
//

#include "stdafx.h"
#include "MMOnline.h"
#include "Processing.h"
#include "afxdialogex.h"


// Processing dialog

IMPLEMENT_DYNAMIC(Processing, CDialogEx)

Processing::Processing(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
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
END_MESSAGE_MAP()


// Processing message handlers
