// keithley_commandDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "keithley_command.h"
#include "keithley_commandDlg.h"
#include "IEEE-C.H"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ckeithley_commandDlg �Ի���




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


// Ckeithley_commandDlg ��Ϣ�������

BOOL Ckeithley_commandDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Ckeithley_commandDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
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
