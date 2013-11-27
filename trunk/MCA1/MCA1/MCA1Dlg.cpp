// MCA1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MCA1.h"
#include "MCA1Dlg.h"
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//�����߳�
FILE* gnu_plot_pipe;

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


// CMCA1Dlg �Ի���




CMCA1Dlg::CMCA1Dlg(CWnd* pParent /*=NULL*/)
: CDialog(CMCA1Dlg::IDD, pParent)
, time(0)
{
	time_limit=1;
	v_set=1;
	StrFileName=_T("output.txt");
	operation_flag=false;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	buff=(unsigned long*) calloc (ADC_GAIN,sizeof(unsigned long));
}

void CMCA1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMCA1Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()

	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CMCA1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CMCA1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMCA1Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CMCA1Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMCA1Dlg ��Ϣ�������

BOOL CMCA1Dlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMCA1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMCA1Dlg::OnPaint()
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
HCURSOR CMCA1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMCA1Dlg::OnTimer(UINT nIDEvent)
{
	char wrtbuf[100];
	char rdbuf[100];
	char*pend;
	unsigned int data;
	char tmp_data[100];
	char *aux_string;
	CString tmp_name;
	long int status;
	unsigned long len;
	CString tmp_str_read;
	switch(nIDEvent)
	{
	case 1:
		time=CTime::GetCurrentTime();//�õ���ǰʱ��
		time_str=time.Format("%Y/%m/%d  %H:%M:%S" );
		GetDlgItem(IDC_STATIC1)->SetWindowText(time_str);
		//UpdateData(FALSE);//����
		break;
	case 2:
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
		//for(int i=0;i<maxGroup;i++)
		{
			PmcaSetGroup(0);
			PmcaClearDataAndTime();
			PmcaGetData(buff, 0, g_gain);
			//Sleep(1000);
			PmcaClearData();
			rate=0;
			for(int i=0;i<g_gain-6;i++)
			{
				rate+=buff[i];
				buff[i]=0;
			}
		}
		time=CTime::GetCurrentTime();//�õ���ǰʱ��
		time_str=time.Format("%Y%m%d%H%M%S" );
		f_out.Open(StrFileName,CFile::modeReadWrite,NULL);
		f_out.SeekToEnd();
		f_out.WriteString(time_str);
		f_out.Write("\t",1);
		f_out.Write(rdbuf,::strlen(rdbuf));
		f_out.Write("\t",1);
		sprintf(rdbuf,"%d",rate);
		f_out.Write(rdbuf,::strlen(rdbuf));
		f_out.Write("\r\n",2);
		f_out.Close();

		tmp_name=_T("plot '")+StrFileName+_T("'using 1:2 w lp pt 5 axis x1y1 t 'current', '")+StrFileName+_T("' using 1:3 w lp pt 7 axis x1y2 t 'rate'\n");
		aux_string=(char*)tmp_name.GetBuffer(0);
		len = wcslen (tmp_name); //the length of "salut"
		wcstombs (aux_string,tmp_name,len); //conversion to char *	
		aux_string[len] = '\0';	 //don't forget to put the caracter of terminated string	


		if(fwrite( aux_string, 1, strlen( aux_string), gnu_plot_pipe)!= strlen( aux_string))
		{
			AfxMessageBox(_T("Can not open the Online monitor!"));
		};

		fflush( gnu_plot_pipe);
		break;
	default:
		break;
	}
}
void CMCA1Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	int m_gpib=0;
	char wrtbuf[100]="*RST";
	char rdbuf[100];
	long int status;
	unsigned long len;
	char *aux_string;
	CString tmp_name;

	UpdateData(TRUE);
	ieee488_boardselect (m_gpib);
	Sleep(100);
	if(ieee488_board_present())
	{
		//Open and initialize the GPIB interface card
		ieee488_initialize (m_gpib, 0);
		Sleep(100);
	}
	else
	{ 
		AfxMessageBox(_T("Invalid GPIB interface card."));
		return;
	}
	operation_flag=true;
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	Sleep(100);

	if (status)
	{
		AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
	}
	//Select current function
	strcpy(wrtbuf,"FUNC 'CURR'");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	Sleep(100);

	if (status)
	{
		AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
	}
	//Enable zero check
	strcpy(wrtbuf,"SYST:ZCH ON");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	Sleep(100);
	if (status)
	{
		AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
	}
	//Select cunrrent range 200nA
	strcpy(wrtbuf,"CURR:RANG:AUTO ON");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	Sleep(100);

	if (status)
	{
		AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
	}
	//Trigger reading to be used as zero correction
	strcpy(wrtbuf,"INIT");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	Sleep(100);

	if (status)
	{
		AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
	}
	//Turn zero correct off
	strcpy(wrtbuf,"SYST:ZCOR:STAT OFF");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	Sleep(100);

	if (status)
	{
		AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
	}
	//Use last reading taken as zero corret value
	strcpy(wrtbuf,"SYST:ZCOR:ACQ");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	Sleep(100);

	if (status)
	{
		AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
	}
	//Perform zero correction
	strcpy(wrtbuf,"SYST:ZCOR ON");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	Sleep(100);

	if (status)
	{
		AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
	}
	//Disable zero check
	strcpy(wrtbuf,"SYST:ZCH OFF");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	Sleep(100);

	if (status)
	{
		AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
	}
	//Select source range
	strcpy(wrtbuf,"SOUR:VOLT:RANGE 500");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	Sleep(100);

	if (status)
	{
		AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
	}
	//Set current limit 2mA
	strcpy(wrtbuf,"SOUR:VOLT:ILIM 2.5e-3");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	Sleep(100);

	if (status)
	{
		AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
	}
	//Inital voltage set 0V
	strcpy(wrtbuf,"SOUR:VOLT 1");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	Sleep(100);

	if (status)
	{
		AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
	}
	//Set voltage into data
	strcpy(wrtbuf,"FORM:ELEM READ");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	Sleep(100);

	if (status)
	{
		AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
	}
	//Read the IDN
	strcpy(wrtbuf,"*IDN?");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	Sleep(100);

	if (status)
	{
		AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
		return;
	}
	//Read the response string from the instrument with specific address
	ieee488_enter (rdbuf, 100, &len, 22, &status);
	Sleep(100);

	if (status)
	{
		AfxMessageBox(_T("Error in reading the response string from the GPIB instrument."));
		return;
	}
	SetTimer(1,1000,NULL);//��װ��ʱ����������ʱ������Ϊ1000����

	AfxMessageBox(_T("Keithley Done!"));
	GetDlgItem(IDC_BUTTON1)->EnableWindow( FALSE ); //DISABLE


	// TODO: Add your control notification handler code here
}

void CMCA1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	long int status;
	unsigned long len;
	char *aux_string;
	CString tmp_name;
	char wrtbuf[100]="*RST";
	//**************************        Voltage ON
	//**************************
	strcpy(wrtbuf,"SOUR:VOLT:STAT ON");
	ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
	Sleep(100);
	if (status)
	{
		AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
	}
	//set the voltage
	sprintf(wrtbuf,"SOUR:VOLT %d",v_set);
	ieee488_send(22, wrtbuf, strlen(wrtbuf), &status);
	if (status)
	{
		AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
	}
	Sleep(100);
	//create the file
	time=CTime::GetCurrentTime();//�õ���ǰʱ��
	StrFileName=time.Format("%Y%m%d%H%M%S")+_T(".txt");
	if(!f_out.Open(StrFileName,CFile::modeCreate|CFile::modeReadWrite,NULL))
	{
		AfxMessageBox(_T("Can not open the file! (HD is full?)"));
	}
	f_out.Close();
	gnu_plot_pipe= NULL;
	gnu_plot_filename= (char*)malloc(1000);
	// open the pipe
	strcpy( gnu_plot_filename, "pgnuplot");
	if((gnu_plot_pipe=_popen( gnu_plot_filename, "w"))==NULL)
	{
		AfxMessageBox(_T("Can not open the Online monitor!"));
	};
	free( gnu_plot_filename);
	//set gnuplot with x axis time
	tmp_name=_T("set xdata time\n");
	aux_string=(char*)tmp_name.GetBuffer(0);
	len = wcslen (tmp_name); //the length of "salut"
	wcstombs (aux_string,tmp_name,len); //conversion to char *	
	aux_string[len] = '\0';	 //don't forget to put the caracter of terminated string
	if(fwrite( aux_string, 1, strlen( aux_string), gnu_plot_pipe)!= strlen( aux_string))
	{
		AfxMessageBox(_T("Can not open the Online monitor!"));
	};

	fflush( gnu_plot_pipe);

	tmp_name=_T("set timefmt \"\%Y\%m\%d\%H\%M\%S\"\n");
	aux_string=(char*)tmp_name.GetBuffer(0);
	len = wcslen (tmp_name); //the length of "salut"
	wcstombs (aux_string,tmp_name,len); //conversion to char *	
	aux_string[len] = '\0';	 //don't forget to put the caracter of terminated string	
	if(fwrite( aux_string, 1, strlen( aux_string), gnu_plot_pipe)!= strlen( aux_string))
	{
		AfxMessageBox(_T("Can not open the Online monitor!"));
	};
	PmcaStartAcquisition(TRUE);

	fflush( gnu_plot_pipe);
	//set the acquire time with second
	SetTimer(2,time_limit*1000,NULL);//��װ��ʱ����������ʱ������Ϊ1000����

}

void CMCA1Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	char wrtbuf[100]="*RST";
	long int status;
	if(operation_flag)
	{
		//Inital voltage set 0V
		strcpy(wrtbuf,"SOUR:VOLT 0");
		ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
		if (status)
		{
			AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
			return;
		}
		//**************************        Voltage OFF
		//**************************
		strcpy(wrtbuf,"SOUR:VOLT:STAT OFF");
		ieee488_send (22, wrtbuf, strlen(wrtbuf), &status);
		if (status)
		{
			AfxMessageBox(_T("Error in writing the string command to the GPIB instrument."));
			return;
		}
	}
	if(gnu_plot_pipe)_pclose( gnu_plot_pipe);
	PmcaStopAcquisition();
	PmcaDisconnect();
	PmcaTerminateCom();
	OnCancel();
}

void CMCA1Dlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here

	// command line: test <com port> <baud rate> <device type> <start gain>
	// device type 0 - AUTO DETECT, 1 - PMCA 8000, 2 - PMCA 8000A 
	int stat = 0;
	int result;
	int thr=100;
	g_port=2;
	g_baudRate=115200;
	g_gain=ADC_GAIN;
	maxGroup=MAX_MEMORY/1024;
    g_device = (PmcaDeviceType) 2;
	stat = PmcaPowerUp(g_port);
	if (stat)
	{
		AfxMessageBox(_T("Error in MCA Power Up!"));
		return;
	}
	Sleep(100);
	stat = PmcaConnect(g_port, g_baudRate, g_device);
	Sleep(100);
	if (stat)
	{
		AfxMessageBox(_T("Can not connect the MCA."));
		return;
	}

	g_device = PmcaGetDeviceType();

	if (g_device == PMCA_8000A)
	{
		stat = PmcaGetSerialNumber();
	}
	stat = PmcaSetPriority(4);
	stat = PmcaSetGain(g_gain);
	stat = PmcaSetThreshold(thr);
	AfxMessageBox(_T("MCA Done!"));
	GetDlgItem(IDC_BUTTON2)->EnableWindow( FALSE ); //DISABLE
	return;
}
