// viewer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication_root.h"
#include "viewer.h"
#include "afxdialogex.h"


// viewer �Ի���

IMPLEMENT_DYNAMIC(viewer, CDialogEx)

viewer::viewer(CWnd* m_Parent )
	: CDialogEx(viewer::IDD, pParent)
{
	pParent = m_Parent;
	fCanvas = NULL;
}

viewer::~viewer()
{
}

void viewer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(viewer, CDialogEx)
	//ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL viewer::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetTimer(1, 10, NULL);//��װ��ʱ����������ʱ������Ϊ1000����

	return TRUE;  // return TRUE  unless you set the focus to a control
}
// viewer ��Ϣ�������
/*void viewer::OnPaint()
{
}*/


void viewer::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);
	//����ROOT����
	RECT rect;
	if (fCanvas == 0) {
		GetWindowRect(&rect);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		int wid = gVirtualX->AddWindow((ULong_t)m_hWnd, width, height);
		fCanvas = new TCanvas("fCanvas", width, height, wid);
		fCanvas->SetFillColor(10);
		fCanvas->SetBorderMode(0);

		gStyle->SetOptStat(0);
		gStyle->SetPalette(1);
		gStyle->SetCanvasColor(33);
		gStyle->SetFrameFillColor(18);
	}
	h->Draw();
	if (fCanvas)fCanvas->Update();
	
	/*gApplication->StartIdleing();
	gSystem->InnerLoop();
	gApplication->StopIdleing();*/
}



BOOL viewer::Create()
{
	return  CDialog::Create(IDD_DIALOG1);
}
