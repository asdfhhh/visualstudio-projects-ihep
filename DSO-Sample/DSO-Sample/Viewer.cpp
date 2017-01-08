// Viewer.cpp : implementation file
//

#include "stdafx.h"
#include "DSO-Sample.h"
#include "Viewer.h"
#include "afxdialogex.h"


// Viewer dialog

IMPLEMENT_DYNAMIC(Viewer, CDialogEx)

Viewer::Viewer(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

Viewer::~Viewer()
{
}

void Viewer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Viewer, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// Viewer message handlers


BOOL Viewer::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}


BOOL Viewer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetTimer(1, 10, NULL);//安装定时器，并将其时间间隔设为1000毫秒

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void Viewer::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);
	/*Ntuple->fillrandom(1000);
	TH1F*h = Ntuple->getntuple();*/
	//绘制ROOT画布
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
	//h->Draw();
	if (fCanvas)fCanvas->Update();
	/*gApplication->StartIdleing();
	gSystem->InnerLoop();
	gApplication->StopIdleing();*/
}