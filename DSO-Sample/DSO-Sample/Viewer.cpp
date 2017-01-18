// Viewer.cpp : implementation file
//

#include "stdafx.h"
#include "DSO-Sample.h"
#include "Viewer.h"
#include "afxdialogex.h"
#include "TFrame.h"
#include "TAxis.h"
// Viewer dialog

IMPLEMENT_DYNAMIC(Viewer, CDialogEx)

Viewer::Viewer(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	drawing = NULL;
	fCanvas = NULL;
	trigger = NULL;
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
	ON_WM_SIZING()
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
	//绘制ROOT画布
	RECT rect;	

	if (fCanvas == 0) {
		GetWindowRect(&rect);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		int wid = gVirtualX->AddWindow((ULong_t)m_hWnd, width, height);
		fCanvas = new TCanvas("fCanvas", width, height, wid);
		fCanvas->SetFillColor(1);
		fCanvas->SetGrid();
		//fCanvas->GetFrame()->SetFillColor(1);
		/*fCanvas->SetBorderMode(0);

		gStyle->SetOptStat(0);
		gStyle->SetPalette(1);
		gStyle->SetCanvasColor(33);
		gStyle->SetFrameFillColor(1);*/
	}
	// TODO:  Add extra initialization here
	SetTimer(1, 10, NULL);//安装定时器，并将其时间间隔设为1000毫秒

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void Viewer::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);
	if (fCanvas)fCanvas->Clear();
	if (drawing)
	{
		drawing->Draw("A");
		drawing->GetXaxis()->SetTitle("X title");
		drawing->GetXaxis()->SetAxisColor(18);
		drawing->GetXaxis()->SetTitleColor(18);
		drawing->GetXaxis()->SetLabelColor(18);
		drawing->GetYaxis()->SetTitle("Y title");
		drawing->GetYaxis()->SetAxisColor(18);
		drawing->GetYaxis()->SetTitleColor(18);
		drawing->GetYaxis()->SetLabelColor(18);
		if(trigger)trigger->Draw();
	}
	if (fCanvas)fCanvas->Update();
	/*gApplication->StartIdleing();
	gSystem->InnerLoop();
	gApplication->StopIdleing();*/
}


void Viewer::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);

	// TODO: Add your message handler code here
	RECT rect;
	GetWindowRect(&rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	int wid = gVirtualX->AddWindow((ULong_t)m_hWnd, width, height);
	fCanvas->SetWindowSize(width, height);
	fCanvas->Resize();
}


bool Viewer::MakeTriLine(int Ch_n, double level)
{
	if (drawing)
	{
		/*drawing->GetXaxis()->GetXmin()
		drawing->GetXaxis()->GetXmax()*/
		trigger = new TLine(0, level, 10240, level);
		if(!Ch_n)trigger->SetLineColor(CH1_COL);
		else if (Ch_n==1)trigger->SetLineColor(CH2_COL);
		else return false;
		trigger->SetLineStyle(4);
		trigger->SetLineWidth(2);
		return true;
	}
	return false;
}
