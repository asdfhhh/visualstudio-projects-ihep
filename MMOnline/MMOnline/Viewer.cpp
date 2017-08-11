// Viewer.cpp : 实现文件
//

#include "stdafx.h"
#include "MMOnline.h"
#include "Viewer.h"
#include "afxdialogex.h"


// Viewer 对话框

IMPLEMENT_DYNAMIC(Viewer, CDialogEx)

Viewer::Viewer(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	daq_canvas = NULL;
	drawing1 = 0;
	drawing2 = 0;

}

Viewer::~Viewer()
{
}

void Viewer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Viewer, CDialogEx)
	ON_WM_SIZING()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


// Viewer 消息处理程序


BOOL Viewer::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}


BOOL Viewer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	RECT rect;

	if (daq_canvas == 0) {
		GetWindowRect(&rect);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		int wid = gVirtualX->AddWindow((ULong_t)m_hWnd, width, height);
		daq_canvas = new TCanvas("Canvas", width, height, wid);
		//fCanvas->SetFillColor(1);
		daq_canvas->SetGrid();
		//daq_canvas->Divide(2, 2);
		//fCanvas->GetFrame()->SetFillColor(1);
		/*fCanvas->SetBorderMode(0);

		gStyle->SetOptStat(0);
		gStyle->SetPalette(1);
		gStyle->SetCanvasColor(33);
		gStyle->SetFrameFillColor(1);*/
	}
	SetTimer(0, 1000, NULL);//no use
	SetTimer(1, 100, NULL);//ROOT signal processing
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Viewer::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);

	// TODO: 在此处添加消息处理程序代码
	RECT rect;
	GetWindowRect(&rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	int wid = gVirtualX->AddWindow((ULong_t)m_hWnd, width, height);
	daq_canvas->SetWindowSize(width, height);
	daq_canvas->Resize();
}


int Viewer::FillHist(TH1F* data)
{
	drawing1 = data;
	daq_canvas->cd();
	UpdateViewer();
	if (drawing1)drawing1->Draw();
	return 0;
}

int Viewer::FillHist(TH2F* data)
{
	drawing2 = data;
	daq_canvas->cd();
	UpdateViewer();
	if (drawing2)drawing2->Draw();
	return 0;
}

int Viewer::UpdateViewer()
{
	daq_canvas->Modified();
	daq_canvas->Update();
	return 0;
}


void Viewer::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnTimer(nIDEvent);
	switch (nIDEvent)
	{
	case 0:
		//UpdateViewer();
		break;
	case 1:
		OnRefreshTimer();
		break;
	default:
		break;
	}
}


void Viewer::OnRefreshTimer()
{
	// Process Root events when a timer message is received
	gApplication->StartIdleing();
	gSystem->InnerLoop();
	gApplication->StopIdleing();
}


void Viewer::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnMouseMove(nFlags, point);
	// Handle Mouse move events

	if (!daq_canvas) return;

	if (nFlags & MK_LBUTTON )
		daq_canvas->HandleInput(kButton1Motion, point.x, point.y);
	else
		daq_canvas->HandleInput(kMouseMotion, point.x, point.y);
	UpdateViewer();
}


void Viewer::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnLButtonDown(nFlags, point);
	// Handle Mouse Left button down event

	if (daq_canvas) daq_canvas->HandleInput(kButton1Down, point.x, point.y);
	UpdateViewer();
}


void Viewer::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnRButtonDown(nFlags, point);
	// Handle Mouse Right button down event

	if (daq_canvas) daq_canvas->HandleInput(kButton3Down, point.x, point.y);
	UpdateViewer();
}


void Viewer::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnLButtonUp(nFlags, point);
	if (daq_canvas) daq_canvas->HandleInput(kButton1Up, point.x, point.y);
	UpdateViewer();
}


void Viewer::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnRButtonUp(nFlags, point);
	if (daq_canvas) daq_canvas->HandleInput(kButton3Up, point.x, point.y);
	UpdateViewer();
}
