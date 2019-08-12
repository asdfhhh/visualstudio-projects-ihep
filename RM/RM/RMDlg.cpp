
// RMDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RM.h"
#include "RMDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_DIALOG2
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

														// 实现
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

// CRMDlg 对话框



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


// CRMDlg 消息处理程序

BOOL CRMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码
	pCtrl = (CListBox *)GetDlgItem(IDC_LIST2);
	pCtrl->AddString(m_output);
	pMWPC = new MWPCANA(pCtrl);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		ShowParameter();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRMDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: Add your control notification handler code here
	m_FilePath.RemoveAll();
	CFileDialog dlg(TRUE,
		_T(".dat"),
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT | OFN_ENABLESIZING,
		_T("RAW DATA (*.dat)|*.dat||"),
		NULL);
	dlg.m_ofn.lpstrTitle = _T("请选择需要打开的文件");	//设置对话框标题 
	dlg.m_ofn.nMaxFile = 500 * MAX_PATH;//最多可以打开100个文件  
	dlg.m_ofn.lpstrFile = new TCHAR[dlg.m_ofn.nMaxFile];
	ZeroMemory(dlg.m_ofn.lpstrFile, sizeof(TCHAR) * dlg.m_ofn.nMaxFile); //
	if (dlg.DoModal() == IDOK)
	{
		////////取出文件路径
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
	//读入文件
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
	// TODO: 在此添加控件通知处理程序代码
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
//	// TODO: 在此添加控件通知处理程序代码
//}


//void CRMDlg::OnChangeEdit1()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//	UpdateData(TRUE);
//	if(m_paralist==0)AfxMessageBox(_T("Error! Please select the parameter first!"));
//	return;
//}


void CRMDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	delete pMWPC;
	CDialogEx::OnCancel();
}
