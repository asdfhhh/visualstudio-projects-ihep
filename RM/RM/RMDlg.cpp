
// RMDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RM.h"
#include "RMDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_DIALOG2
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

														// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// CRMDlg �Ի���



CRMDlg::CRMDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RM_DIALOG, pParent)
	, base_FilePath(_T(""))
	, m_FileExt(_T(""))
	, ParaShow(_T(""))
	, m_paralist(0)
	, m_value(_T(""))
	, m_output(_T("Wellcome to use the MWPC processing programme!"))
	, pCtrl(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO1, m_paralist);
	DDX_Text(pDX, IDC_EDIT1, m_value);
}

BEGIN_MESSAGE_MAP(CRMDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CRMDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CRMDlg::OnBnClickedOk)
//	ON_CBN_EDITCHANGE(IDC_COMBO1, &CRMDlg::OnEditchangeCombo1)
//ON_EN_CHANGE(IDC_EDIT1, &CRMDlg::OnChangeEdit1)
ON_BN_CLICKED(IDC_BUTTON2, &CRMDlg::OnBnClickedButton2)
ON_BN_CLICKED(IDCANCEL, &CRMDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CRMDlg ��Ϣ�������

BOOL CRMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	pCtrl = (CListBox *)GetDlgItem(IDC_LIST2);
	pCtrl->AddString(m_output);
	pMWPC = new MWPCANA(pCtrl);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRMDlg::OnPaint()
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
		ShowParameter();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRMDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: Add your control notification handler code here
	m_FilePath.RemoveAll();
	CFileDialog dlg(TRUE,
		_T(".dat"),
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT | OFN_ENABLESIZING,
		_T("RAW DATA (*.dat)|*.dat||"),
		NULL);
	dlg.m_ofn.lpstrTitle = _T("��ѡ����Ҫ�򿪵��ļ�");	//���öԻ������ 
	dlg.m_ofn.nMaxFile = 500 * MAX_PATH;//�����Դ�100���ļ�  
	dlg.m_ofn.lpstrFile = new TCHAR[dlg.m_ofn.nMaxFile];
	ZeroMemory(dlg.m_ofn.lpstrFile, sizeof(TCHAR) * dlg.m_ofn.nMaxFile); //
	if (dlg.DoModal() == IDOK)
	{
		////////ȡ���ļ�·��
		POSITION pos = dlg.GetStartPosition();
		while (pos != NULL)
		{
			m_FilePath.Add(dlg.GetNextPathName(pos));
		}
		m_FileExt = m_FilePath.ElementAt(0).Right(3);
		FileNum = m_FilePath.GetSize();
		//UpdateData(FALSE);
	}
	if (m_FileExt == _T("dat"))NameProcessing();
	else return;

}


int CRMDlg::NameProcessing()
{
	//�����ļ�
	UpdateData(TRUE);
	Processing *P_GUI = new Processing(this);
	if (P_GUI->GetSafeHwnd() == NULL)P_GUI->Create(MAKEINTRESOURCE(IDD_DIALOG1), this);
	P_GUI->ShowWindow(SW_SHOW);
	m_Progress = P_GUI->GetCP();
	pMWPC->SetProgress(m_Progress);
	for (int fileloop = 0; fileloop < FileNum; fileloop++)
	{
		m_output.Format(_T("Processing the file:"));
		pCtrl->AddString(m_output);
		m_output=m_FilePath.ElementAt(fileloop);
		pCtrl->AddString(m_output);
		// Convert a TCHAR string to a LPCSTR
		CString filename = m_FilePath.ElementAt(fileloop);
		filename = filename.Left(filename.GetLength()-4);
		//CT2CA pszConvertedAnsiString(tmpstr);
		// construct a std::string using the LPCSTR input
		//std::string filename(pszConvertedAnsiString);
		pMWPC->Processing(filename);
	}
	P_GUI->DestroyWindow();
	delete P_GUI;
	return 0;
}


void CRMDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAboutDlg AboutDlg;
	AboutDlg.DoModal();
	//CDialogEx::OnOK();
}


// //update the parameters painting
void CRMDlg::ShowParameter()
{
	ParaShow.Format(_T("%d \r\n%d \r\n%d \r\n%d \r\n%f \r\n%f \r\n%d \r\n%d  \r\n%d \r\n%d \r\n%d \r\n%d  \r\n%d \r\n%d \r\n%d  \r\n%d"),
		pMWPC->GetSLICESIZE(), pMWPC->GetSIGNALSIZE(), pMWPC->GetXCHANNELNUM(), pMWPC->GetYCHANNELNUM(), pMWPC->GetQMIN(), pMWPC->GetQMAX(), pMWPC->GetMATCHWINDOW(), pMWPC->GetSTRIPGAP(), pMWPC->GetTOFRANGE1(), pMWPC->GetTOFRANGE2(), pMWPC->GetWIDELIMITX(), pMWPC->GetWIDELIMITY(), pMWPC->GetQSUMX(), pMWPC->GetQSUMY(), pMWPC->GetFASTMATCH1(), pMWPC->GetFASTMATCH2());
	GetDlgItem(IDC_STATIC2)->SetWindowText(ParaShow);
}


//void CRMDlg::OnEditchangeCombo1()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}


//void CRMDlg::OnChangeEdit1()
//{
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
//	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
//	// ���������� CRichEditCtrl().SetEventMask()��
//	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
//
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	UpdateData(TRUE);
//	if(m_paralist==0)AfxMessageBox(_T("Error! Please select the parameter first!"));
//	return;
//}


void CRMDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	switch (m_paralist)
	{
	case SLICESIZE:
		pMWPC->SetSLICESIZE(_tstoi(m_value));
		break;
	case SIGNALSIZE:
		pMWPC->SetSIGNALSIZE(_tstoi(m_value));
		break;
	case XCHANNELNUM:
		pMWPC->SetXCHANNELNUM(_tstoi(m_value));
		break;
	case YCHANNELNUM:
		pMWPC->SetYCHANNELNUM(_tstoi(m_value));
		break;
	case QMIN:
		pMWPC->SetQMIN(_tstof(m_value));
		break;
	case QMAX:
		pMWPC->SetQMAX(_tstof(m_value));
		break;
	case MATCHWINDOW:
		pMWPC->SetMATCHWINDOW(_tstoi(m_value));
		break;
	case STRIPGAP:
		pMWPC->SetSTRIPGAP(_tstoi(m_value));
		break;
	case TOFRANGE1:
		pMWPC->SetTOFRANGE1(_tstoi(m_value));
		break;
	case TOFRANGE2:
		pMWPC->SetTOFRANGE2(_tstoi(m_value));
		break;
	case WIDELIMITX:
		pMWPC->SetWIDELIMITX(_tstoi(m_value));
		break;
	case WIDELIMITY:
		pMWPC->SetWIDELIMITY(_tstoi(m_value));
		break;
	case QSUMX:
		pMWPC->SetQSUMX(_tstoi(m_value));
		break;
	case QSUMY:
		pMWPC->SetQSUMY(_tstoi(m_value));
		break;
	case FASTMATCH1:
		pMWPC->SetFASTMATCH1(_tstoi(m_value));
		break;
	case FASTMATCH2:
		pMWPC->SetFASTMATCH2(_tstoi(m_value));
		break;
	default:
		break;
	}
	ShowParameter();
}


void CRMDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	delete pMWPC;
	CDialogEx::OnCancel();
}
