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
	viewer_canvas = NULL;
	drawing = NULL;
}

DAQ_Viewer::~DAQ_Viewer()
{
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
	//����ROOT����
	RECT rect;

	if (viewer_canvas == 0) {
		GetWindowRect(&rect);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		int wid = gVirtualX->AddWindow((ULong_t)m_hWnd, width, height);
		viewer_canvas = new TCanvas("fCanvas", width, height, wid);
		//fCanvas->SetFillColor(1);
		viewer_canvas->SetGrid();
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
	viewer_canvas->SetWindowSize(width, height);
	viewer_canvas->Resize();
}
