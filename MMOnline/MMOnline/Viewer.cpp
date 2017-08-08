// Viewer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MMOnline.h"
#include "Viewer.h"
#include "afxdialogex.h"


// Viewer �Ի���

IMPLEMENT_DYNAMIC(Viewer, CDialogEx)

Viewer::Viewer(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	daq_canvas = NULL;
	drawing = new TH1F("test", "test", 200, 0, 600000);
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
END_MESSAGE_MAP()


// Viewer ��Ϣ�������


BOOL Viewer::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}


BOOL Viewer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	SetTimer(0, 1000, NULL);//set the Drawing timer
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void Viewer::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);

	// TODO: �ڴ˴������Ϣ����������
	RECT rect;
	GetWindowRect(&rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	int wid = gVirtualX->AddWindow((ULong_t)m_hWnd, width, height);
	daq_canvas->SetWindowSize(width, height);
	daq_canvas->Resize();
}


int Viewer::FillHist(float data)
{
	drawing->Fill(data);
	return 0;
}


int Viewer::UpdateViewer()
{
	daq_canvas->cd();
	drawing->Draw();
	daq_canvas->Modified();
	daq_canvas->Update();
	return 0;
}


void Viewer::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialogEx::OnTimer(nIDEvent);
	switch (nIDEvent)
	{
	case 0:
		UpdateViewer();
		break;
	default:
		break;
	}
}
