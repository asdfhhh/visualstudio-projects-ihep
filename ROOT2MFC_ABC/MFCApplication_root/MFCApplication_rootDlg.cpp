
// MFCApplication_rootDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication_root.h"
#include "MFCApplication_rootDlg.h"
#include "afxdialogex.h"
//�������仰һ��Ҫ�����ˣ�����������������������
//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif
#include "TFile.h"

// CMFCApplication_rootDlg �Ի���



CMFCApplication_rootDlg::CMFCApplication_rootDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication_rootDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	rootv = new viewer(this);
	Ntuple = new MakeNTuple();
	TFile *f = new TFile("test.root", "NEW");
}

void CMFCApplication_rootDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication_rootDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication_rootDlg::OnBnClickedOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMFCApplication_rootDlg ��Ϣ�������

BOOL CMFCApplication_rootDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	SetTimer(1, 10, NULL);//��װ��ʱ����������ʱ������Ϊ1000����

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplication_rootDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCApplication_rootDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication_rootDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	if (rootv->GetSafeHwnd() == NULL)
	{	
		rootv->Create();
	}
	//else AfxMessageBox(_T("���ӽ����Ѿ��򿪣�"));
		rootv->ShowWindow(SW_SHOW);
}


void CMFCApplication_rootDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnTimer(nIDEvent);
	Ntuple->fillrandom(1000);
	rootv->SetHist(Ntuple->getntuple());
}
