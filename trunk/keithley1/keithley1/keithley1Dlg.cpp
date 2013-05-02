// keithley1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "keithley1.h"
#include "keithley1Dlg.h"
#include "DlgProxy.h"
#include "IEEE-C.H"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

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


// Ckeithley1Dlg 对话框




IMPLEMENT_DYNAMIC(Ckeithley1Dlg, CDialog);

Ckeithley1Dlg::Ckeithley1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Ckeithley1Dlg::IDD, pParent)
{
	m_str_read = _T("Welcome to the soft of silicon measurement!");
	StrFileName="data.txt";
	m_waittime=4;
	m_maxvoltage=11;
	m_stepvoltage=4;
	operation_flag=false;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

Ckeithley1Dlg::~Ckeithley1Dlg()
{
	// 如果该对话框有自动化代理，则
	//  将此代理指向该对话框的后向指针设置为 NULL，以便
	//  此代理知道该对话框已被删除。
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void Ckeithley1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2,StrFileName);
	DDX_CBIndex(pDX, IDC_COMBO1, m_waittime);
	DDX_CBIndex(pDX, IDC_COMBO2, m_maxvoltage);
	DDX_CBIndex(pDX, IDC_COMBO3, m_stepvoltage);
}

BEGIN_MESSAGE_MAP(Ckeithley1Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &Ckeithley1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &Ckeithley1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &Ckeithley1Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &Ckeithley1Dlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT2, &Ckeithley1Dlg::OnEnChangeEdit2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Ckeithley1Dlg::OnCbnSelchangeCombo1)
	ON_LBN_SELCHANGE(IDC_LIST1, &Ckeithley1Dlg::OnLbnSelchangeList1)
	//ON_BN_CLICKED(IDC_WARM, &Ckeithley1Dlg::OnBnClickedWarm)
	ON_CBN_SELCHANGE(IDC_COMBO2, &Ckeithley1Dlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_HELP, &Ckeithley1Dlg::OnBnClickedAbout)
END_MESSAGE_MAP()


// Ckeithley1Dlg 消息处理程序

BOOL Ckeithley1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	pCtrl = (CListBox *)GetDlgItem( IDC_LIST1 ) ; 
	pCtrl->AddString(m_str_read);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Ckeithley1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Ckeithley1Dlg::OnPaint()
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
HCURSOR Ckeithley1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 当用户关闭 UI 时，
//  如果控制器仍保持着它的某个对象，则自动化服务器不应退出。这些
//  消息处理程序确保如下情形: 如果代理仍在使用，
//  则将隐藏 UI；但是在关闭对话框时，
//  对话框仍然会保留在那里。

void Ckeithley1Dlg::OnClose()
{
	if (CanExit())
		CDialog::OnClose();
}

void Ckeithley1Dlg::OnOK()
{
	if (CanExit())
		CDialog::OnOK();
}

void Ckeithley1Dlg::OnCancel()
{
	if (CanExit())
		CDialog::OnCancel();
}

BOOL Ckeithley1Dlg::CanExit()
{
	// 如果代理对象仍保留在那里，则自动化
	//  控制器仍会保持此应用程序。
	//  使对话框保留在那里，但将其 UI 隐藏起来。
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}


void Ckeithley1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//OnOK();
	int m_gpib=0;
	char wrtbuf[100]="*RST";
	char rdbuf[100];
	long int status;
	unsigned long len;
 	UpdateData();
    ieee488_boardselect (m_gpib);
	if(ieee488_board_present())
	{
		//Open and initialize the GPIB interface card
		ieee488_initialize (m_gpib, 0);
	}
	else
	{ 
		AfxMessageBox(_T("Invalid GPIB interface card."));
		return;
	}
	operation_flag=true;
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	m_str_read = wrtbuf;
	pCtrl->AddString(m_str_read);
    if (status)
	{
	    AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
	}
	//Select current function
    strcpy(wrtbuf,"FUNC 'CURR'");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	m_str_read = wrtbuf;
	pCtrl->AddString(m_str_read);
    if (status)
	{
	    AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
    }
	//Enable zero check
	strcpy(wrtbuf,"SYST:ZCH ON");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	m_str_read = wrtbuf;
	pCtrl->AddString(m_str_read);
    if (status)
	{
	    AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
    }
	//Select cunrrent range 200nA
	strcpy(wrtbuf,"CURR:RANG:AUTO ON");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	m_str_read = wrtbuf;
	pCtrl->AddString(m_str_read);
    if (status)
	{
	    AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
    }
	//Trigger reading to be used as zero correction
	strcpy(wrtbuf,"INIT");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	m_str_read = wrtbuf;
	pCtrl->AddString(m_str_read);
    if (status)
	{
	    AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
    }
	//Turn zero correct off
	strcpy(wrtbuf,"SYST:ZCOR:STAT OFF");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	m_str_read = wrtbuf;
	pCtrl->AddString(m_str_read);
    if (status)
	{
	    AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
    }
	//Use last reading taken as zero corret value
	strcpy(wrtbuf,"SYST:ZCOR:ACQ");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	m_str_read = wrtbuf;
	pCtrl->AddString(m_str_read);
    if (status)
	{
	    AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
    }
	//Perform zero correction
	strcpy(wrtbuf,"SYST:ZCOR ON");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	m_str_read = wrtbuf;
	pCtrl->AddString(m_str_read);
    if (status)
	{
	    AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
    }
	//Disable zero check
	strcpy(wrtbuf,"SYST:ZCH OFF");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	m_str_read = wrtbuf;
	pCtrl->AddString(m_str_read);
    if (status)
	{
	    AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
    }
	//Select source range
	strcpy(wrtbuf,"SOUR:VOLT:RANGE 500");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	m_str_read = wrtbuf;
	pCtrl->AddString(m_str_read);
    if (status)
	{
	    AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
    }
	//Set current limit 2mA
	strcpy(wrtbuf,"SOUR:VOLT:ILIM 2.5e-3");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	m_str_read = wrtbuf;
	pCtrl->AddString(m_str_read);
    if (status)
	{
	    AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
    }
	//Inital voltage set 0V
	strcpy(wrtbuf,"SOUR:VOLT 0");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	m_str_read = wrtbuf;
	pCtrl->AddString(m_str_read);
    if (status)
	{
	    AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
    }
	//Set voltage into data
	strcpy(wrtbuf,"FORM:ELEM READ");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	m_str_read = wrtbuf;
	pCtrl->AddString(m_str_read);
    if (status)
	{
	    AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
    }
	//Read the IDN
	strcpy(wrtbuf,"*IDN?");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	m_str_read = wrtbuf;
	pCtrl->AddString(m_str_read);
	if (status)
	{
	    AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
    }
	//Read the response string from the instrument with specific address
	ieee488_enter (rdbuf, 100, &len, 22, &status);
	m_str_read = rdbuf;
	pCtrl->AddString(m_str_read);
    if (status)
	{
	    AfxMessageBox(_T("Error in reading the response string from the GPIB instrument."));
		return;
    }
}
//自定义消息
#define WM_UPDATEPOS		WM_USER + 1000
//线程数据结构
typedef struct ThreadData
{
	Ckeithley1Dlg* pDlg;
	int nIndex;
	int tmp_maxvoltage;
	int tmp_stepvoltage;
	int tmp_waittime;
}THREADDATA;
//工作线程
	FILE* gnu_plot_pipe;
UINT WorkThreadProc(LPVOID lParam)
{
	THREADDATA* pData = (THREADDATA*)lParam;
	char wrtbuf[100]="READ?";
	char rdbuf[100];
	char*pend;
	unsigned int data;
	char tmp_data[100];
	gnu_plot_pipe= NULL;
	char *gnu_plot_filename= (char*)malloc(1000);
	//create the file
	if(!pData->pDlg->f_out.Open(pData->pDlg->StrFileName,CFile::modeCreate|CFile::modeReadWrite,NULL))
	{
		AfxMessageBox(_T("Can not open the file! (HD is full?)"));
	}
	pData->pDlg->f_out.Close();
	// open the pipe
	strcpy( gnu_plot_filename, "pgnuplot");
	if((gnu_plot_pipe=_popen( gnu_plot_filename, "w"))==NULL)
	{
		AfxMessageBox(_T("Can not open the Online monitor!"));
	};
    free( gnu_plot_filename);

	long int status;
	unsigned long len;
	double i_test;
	int wtime,mV,sV;
	CString tmp_str_read;
	mV=(pData->tmp_maxvoltage+1)*10;
	sV=pData->tmp_stepvoltage+1;
	wtime=(pData->tmp_waittime+1)*1000;
	//Select source range
	/*sprintf(wrtbuf,"SOUR:VOLT:RANGE 500");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
    if (status)
	{
	    AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
    }
*/
	//**************************        Voltage ON
	//**************************
	strcpy(wrtbuf,"SOUR:VOLT:STAT ON");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
    if (status)
	{
	    AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
    }

	//Change voltage
	for(int v_set=0;v_set<mV;v_set=v_set+sV)
	{
		sprintf(wrtbuf,"SOUR:VOLT %d",v_set);
		ieee488_send(22, wrtbuf, strlen(wrtbuf), &status);
		if (status)
		{
			AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		}
		Sleep(wtime);

		//reading
		strcpy(wrtbuf,"READ?");
		ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
		if (status)
		{
			AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		}

		//Read the response string from the instrument with specific address
		ieee488_enter (rdbuf, 100, &len, 22, &status);
		if (status)
		{
			AfxMessageBox(_T("Error in reading the response string from the GPIB instrument."));
		}
		//i_test=atof(rdbuf);
		sprintf(tmp_data,"%d",v_set);
		pData->pDlg->f_out.Open(pData->pDlg->StrFileName,CFile::modeReadWrite,NULL);
		pData->pDlg->f_out.SeekToEnd();
		pData->pDlg->f_out.Write(tmp_data,::strlen(tmp_data));
		pData->pDlg->f_out.Write("\t",1);
		pData->pDlg->f_out.Write(rdbuf,::strlen(rdbuf));
		pData->pDlg->f_out.Write("\r\n",2);
		pData->pDlg->f_out.Close();

		
		CString tmp_name=_T("plot '")+pData->pDlg->StrFileName+_T("' with lp\n");
		char *aux_string=(char*)tmp_name.GetBuffer(0);
		long len = wcslen (tmp_name); //the length of "salut"
		wcstombs (aux_string,tmp_name,len); //conversion to char *	
		aux_string[len] = '\0';	 //don't forget to put the caracter of terminated string	

		//int strLength = tmp_name.GetLength() + 1;
		//memset(aux_string,0, sizeof(bool) * 100);
		//strncpy(aux_string, tmp_name,strLength);
		//sprintf(aux_string,"plot 'data.txt' with lp\n");

		if(fwrite( aux_string, 1, strlen( aux_string), gnu_plot_pipe)!= strlen( aux_string))
		{
			AfxMessageBox(_T("Can not open the Online monitor!"));
		};

		fflush( gnu_plot_pipe);
	}
	strcpy(wrtbuf,"SOUR:VOLT:STAT OFF");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
    if (status)
	{
	    AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
    }
	AfxMessageBox(_T("Mesurement complete!"));
	delete pData;
	return 0;
}
void Ckeithley1Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	THREADDATA* pData = new THREADDATA;
	pData->nIndex = 1;
	pData->pDlg = this;
	pData->tmp_maxvoltage=m_maxvoltage;
	pData->tmp_stepvoltage=m_stepvoltage;
	pData->tmp_waittime=m_waittime;

	//启动工作线程
	this->m_ThreadOne=AfxBeginThread(WorkThreadProc,pData);
}

void Ckeithley1Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	char wrtbuf[100]="*RST";
	long int status;
	if(operation_flag)
	{
		//Inital voltage set 0V
		strcpy(wrtbuf,"SOUR:VOLT 0");
		ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
		m_str_read = wrtbuf;
		pCtrl->AddString(m_str_read);
		if (status)
		{
			AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
			return;
		}
		//**************************        Voltage OFF
		//**************************
		strcpy(wrtbuf,"SOUR:VOLT:STAT OFF");
		ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
		m_str_read = wrtbuf;
		pCtrl->AddString(m_str_read);
		if (status)
		{
			AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
			return;
		}
	}
    if(gnu_plot_pipe)_pclose( gnu_plot_pipe);
	OnCancel();
}


void Ckeithley1Dlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
		//终止线程
	if(this->m_ThreadOne)
	  TerminateThread(this->m_ThreadOne->m_hThread,NULL);

	char wrtbuf[100]="*RST";
	long int status;
	//**************************        Voltage OFF
	//**************************
	strcpy(wrtbuf,"SOUR:VOLT:STAT OFF");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	m_str_read = wrtbuf;
	pCtrl->AddString(m_str_read);
    if (status)
	{
	    AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
    }
}

void Ckeithley1Dlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void Ckeithley1Dlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
}

void Ckeithley1Dlg::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
}


void Ckeithley1Dlg::OnCbnSelchangeCombo2()
{
	// TODO: Add your control notification handler code here
}

void Ckeithley1Dlg::OnBnClickedAbout()
{
	CAboutDlg AboutDlg;
	AboutDlg.DoModal();
// TODO: Add your control notification handler code here
}
