// keithley2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "keithley2.h"
#include "keithley2Dlg.h"
#include "IEEE-C.H"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ckeithley2Dlg 对话框


//工作线程
FILE* gnu_plot_pipe;

Ckeithley2Dlg::Ckeithley2Dlg(CWnd* pParent /*=NULL*/)
: CDialog(Ckeithley2Dlg::IDD, pParent)
{
	time_limit=60;
	v_set=0;
	StrFileName=_T("output.txt");
	operation_flag=false;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ckeithley2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1,time_limit_str);
	DDX_Text(pDX, IDC_EDIT2,v_set_str);
}

BEGIN_MESSAGE_MAP(Ckeithley2Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT1, &Ckeithley2Dlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &Ckeithley2Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Ckeithley2Dlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT2, &Ckeithley2Dlg::OnEnChangeEdit2)

END_MESSAGE_MAP()


// Ckeithley2Dlg 消息处理程序

BOOL Ckeithley2Dlg::OnInitDialog()
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

void Ckeithley2Dlg::OnPaint()
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
		SetTimer(1,1000,NULL);//安装定时器，并将其时间间隔设为1000毫秒
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR Ckeithley2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Ckeithley2Dlg::OnTimer(UINT nIDEvent)
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
		time=CTime::GetCurrentTime();//得到当前时间
		time_str=time.Format("%Y/%m/%d  %H:%M:%S" );
		GetDlgItem(IDC_STATIC1)->SetWindowText(time_str);
		//UpdateData(FALSE);//更新
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
		time=CTime::GetCurrentTime();//得到当前时间
		time_str=time.Format("%Y%m%d%H%M%S" );
		f_out.Open(StrFileName,CFile::modeReadWrite,NULL);
		f_out.SeekToEnd();
		f_out.WriteString(time_str);
		f_out.Write("\t",1);
		f_out.Write(rdbuf,::strlen(rdbuf));
		f_out.Write("\r\n",2);
		f_out.Close();

		tmp_name=_T("plot '")+StrFileName+_T("' using 1:2 with lp\n");
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
void Ckeithley2Dlg::OnBnClickedOk()
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
	strcpy(wrtbuf,"SOUR:VOLT 0");
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

	//set the acquire time with second
	time_limit=_tstoi(time_limit_str);
	v_set=_tstoi(v_set_str);
	SetTimer(2,time_limit*1000,NULL);//安装定时器，并将其时间间隔设为1000毫秒

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
	time=CTime::GetCurrentTime();//得到当前时间
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

		fflush( gnu_plot_pipe);

}

void Ckeithley2Dlg::OnBnClickedCancel()
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
	OnCancel();
}

void Ckeithley2Dlg::OnEnChangeEdit1()
{

	//
}
void Ckeithley2Dlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
