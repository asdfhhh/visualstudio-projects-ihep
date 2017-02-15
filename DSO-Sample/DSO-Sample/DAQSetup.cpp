// DAQSetup.cpp : implementation file
//

#include "stdafx.h"
#include "DSO-Sample.h"
#include "DAQSetup.h"
#include "afxdialogex.h"


// DAQSetup dialog

IMPLEMENT_DYNAMIC(DAQSetup, CDialogEx)

DAQSetup::DAQSetup(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_DAQSetup, pParent)
{

}

DAQSetup::~DAQSetup()
{
}

void DAQSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DAQSetup_Cutoff, m_editCutoff);
	DDX_Control(pDX, IDC_EDIT_DAQSetup_MCAMax, m_editMcaMax);
	DDX_Control(pDX, IDC_EDIT_DAQSetup_RTimeMax, m_editRTimemax);
}


BEGIN_MESSAGE_MAP(DAQSetup, CDialogEx)
	ON_BN_CLICKED(IDOK, &DAQSetup::OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_EDIT_DAQSetup_Cutoff, &DAQSetup::OnKillfocusEditDaqsetupCutoff)
	ON_EN_KILLFOCUS(IDC_EDIT_DAQSetup_MCAMax, &DAQSetup::OnKillfocusEditDaqsetupMcamax)
	ON_EN_KILLFOCUS(IDC_EDIT_DAQSetup_RTimeMax, &DAQSetup::OnKillfocusEditDaqsetupRtimemax)
END_MESSAGE_MAP()


// DAQSetup message handlers


void DAQSetup::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if (data_p)data_p->SetDAQCtrl(DAQ_p);
	DestroyWindow();
}


void DAQSetup::OnKillfocusEditDaqsetupCutoff()
{
	// TODO: Add your control notification handler code here
	CString str;
	double nlevel;
	m_editCutoff.GetWindowText(str);
	nlevel = _tstof(str);
	if (nlevel < 0)
	{
		nlevel = 1;
		str.Format(_T("%f"), nlevel);
		m_editCutoff.SetWindowText(str);
	}
	DAQ_p.cutoff = nlevel;
}


void DAQSetup::OnKillfocusEditDaqsetupMcamax()
{
	// TODO: Add your control notification handler code here
	CString str;
	int nlevel;
	m_editMcaMax.GetWindowText(str);
	nlevel = _tstoi(str);
	if (nlevel < 0)
	{
		nlevel = 1000;
		str.Format(_T("%d"), nlevel);
		m_editMcaMax.SetWindowText(str);
	}
	DAQ_p.MCA_MAX = nlevel;
}


void DAQSetup::OnKillfocusEditDaqsetupRtimemax()
{
	// TODO: Add your control notification handler code here
	CString str;
	int nlevel;
	m_editRTimemax.GetWindowText(str);
	nlevel = _tstoi(str);
	if (nlevel < 0)
	{
		nlevel = 100;
		str.Format(_T("%d"), nlevel);
		m_editRTimemax.SetWindowText(str);
	}
	DAQ_p.RT_MAX = nlevel;
}


BOOL DAQSetup::Create(DataProcessing*data,LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base class
	data_p = data;
	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}


BOOL DAQSetup::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  Add extra initialization here
	CString str;
	DAQ_p.cutoff = 1;
	str.Format(_T("%f"), DAQ_p.cutoff);
	m_editCutoff.SetWindowText(str);
	DAQ_p.MCA_MAX = 1000;
	str.Format(_T("%d"), DAQ_p.MCA_MAX);
	m_editMcaMax.SetWindowText(str);
	DAQ_p.RT_MAX = 100;
	str.Format(_T("%d"), DAQ_p.RT_MAX);
	m_editRTimemax.SetWindowText(str);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
