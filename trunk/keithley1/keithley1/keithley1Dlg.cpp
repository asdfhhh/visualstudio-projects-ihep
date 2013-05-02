// keithley1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "keithley1.h"
#include "keithley1Dlg.h"
#include "DlgProxy.h"
#include "IEEE-C.H"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

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


// Ckeithley1Dlg �Ի���




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
	// ����öԻ������Զ���������
	//  ���˴���ָ��öԻ���ĺ���ָ������Ϊ NULL���Ա�
	//  �˴���֪���öԻ����ѱ�ɾ����
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


// Ckeithley1Dlg ��Ϣ�������

BOOL Ckeithley1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	pCtrl = (CListBox *)GetDlgItem( IDC_LIST1 ) ; 
	pCtrl->AddString(m_str_read);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Ckeithley1Dlg::OnPaint()
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
HCURSOR Ckeithley1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���û��ر� UI ʱ��
//  ����������Ա���������ĳ���������Զ�����������Ӧ�˳�����Щ
//  ��Ϣ�������ȷ����������: �����������ʹ�ã�
//  ������ UI�������ڹرնԻ���ʱ��
//  �Ի�����Ȼ�ᱣ�������

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
	// �����������Ա�����������Զ���
	//  �������Իᱣ�ִ�Ӧ�ó���
	//  ʹ�Ի���������������� UI ����������
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
//�Զ�����Ϣ
#define WM_UPDATEPOS		WM_USER + 1000
//�߳����ݽṹ
typedef struct ThreadData
{
	Ckeithley1Dlg* pDlg;
	int nIndex;
	int tmp_maxvoltage;
	int tmp_stepvoltage;
	int tmp_waittime;
}THREADDATA;
//�����߳�
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

	//���������߳�
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
		//��ֹ�߳�
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
