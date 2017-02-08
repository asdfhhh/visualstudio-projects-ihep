// DAQ_Viewer.cpp : implementation file
//

#include "stdafx.h"
#include "DSO-Sample.h"
#include "DAQ_Viewer.h"
#include "afxdialogex.h"


// DAQ_Viewer dialog

IMPLEMENT_DYNAMIC(DAQ_Viewer, CDialogEx)

DAQ_Viewer::DAQ_Viewer(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DAQ, pParent)
{
	daq_canvas = NULL;
	drawing = NULL;
}

DAQ_Viewer::~DAQ_Viewer()
{
	delete daq_canvas;
	delete drawing;
}

void DAQ_Viewer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DAQ_Viewer, CDialogEx)
	ON_WM_SIZING()
END_MESSAGE_MAP()


// DAQ_Viewer message handlers


BOOL DAQ_Viewer::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}


BOOL DAQ_Viewer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	//»æÖÆROOT»­²¼
	RECT rect;

	if (daq_canvas == 0) {
		GetWindowRect(&rect);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		int wid = gVirtualX->AddWindow((ULong_t)m_hWnd, width, height);
		daq_canvas = new TCanvas("CanvasDAQ", width, height, wid);
		//fCanvas->SetFillColor(1);
		daq_canvas->SetGrid();
		//fCanvas->GetFrame()->SetFillColor(1);
		/*fCanvas->SetBorderMode(0);

		gStyle->SetOptStat(0);
		gStyle->SetPalette(1);
		gStyle->SetCanvasColor(33);
		gStyle->SetFrameFillColor(1);*/
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void DAQ_Viewer::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);

	// TODO: Add your message handler code here
	RECT rect;
	GetWindowRect(&rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	int wid = gVirtualX->AddWindow((ULong_t)m_hWnd, width, height);
	daq_canvas->SetWindowSize(width, height);
	daq_canvas->Resize();
}


int DAQ_Viewer::Drawing()
{
	daq_canvas->cd();
	if (drawing)drawing->Draw();
	daq_canvas->Update();
	return 0;
}


int DAQ_Viewer::MakeGraph(int nBin, double* Data)
{
	if (drawing)delete drawing;
	drawing = new TH1F("PSDwave", "Wave after PSD", nBin, 0, nBin);
	for (int i = 0; i < nBin; i++)drawing->Fill(i, Data[i]);
	return 0;
}
