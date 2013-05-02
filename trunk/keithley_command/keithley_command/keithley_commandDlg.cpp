// keithley_commandDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "keithley_command.h"
#include "keithley_commandDlg.h"
#include "IEEE-C.H"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ckeithley_commandDlg 对话框




Ckeithley_commandDlg::Ckeithley_commandDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Ckeithley_commandDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ckeithley_commandDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1,command_str);

}

BEGIN_MESSAGE_MAP(Ckeithley_commandDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT1, &Ckeithley_commandDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &Ckeithley_commandDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Ckeithley_commandDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// Ckeithley_commandDlg 消息处理程序

BOOL Ckeithley_commandDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Ckeithley_commandDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR Ckeithley_commandDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Ckeithley_commandDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void Ckeithley_commandDlg::OnBnClickedOk()
{
	long int status;
	char *wrtbuf;
	CString out;
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	wrtbuf=(char*)command_str.GetBuffer(0);
	int len = wcslen (command_str); //the length of "salut"
	wcstombs (wrtbuf,command_str,len); //conversion to char *	
	wrtbuf[len] = '\0';	 //don't forget to put the caracter of terminated string
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	if(!status)out=_T("The command is sent to the 4687");
	else if(status==8)out=_T("Eorror! Time out!");
	else out=_T("Eorror! Unkown!");
	GetDlgItem(IDC_STATIC1)->SetWindowText(out);
}

void Ckeithley_commandDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
