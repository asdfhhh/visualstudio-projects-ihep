// VCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VC.h"
#include "VCDlg.h"




/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVCDlg dialog

CVCDlg::CVCDlg(CWnd* pParent /*=NULL*/)
: CDialog(CVCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVCDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	mca_flag=false;
	m_Hard = new CHard();
	TFile*f = new TFile("test.root", "NEW");
	//TH1F*h = new TH1F("test", "test", 200, 0, 200);
}

void CVCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVCDlg)
	DDX_Control(pDX, IDC_EDIT_TRIG_LEVEL, m_editTrigLevel);
	DDX_Control(pDX, IDC_EDIT_CH_LEVEL, m_editChLevel);
	DDX_Control(pDX, IDC_CBO_TRIG_SWEEP, m_cboTrigSweep);
	DDX_Control(pDX, IDC_CBO_TRIG_COUPLE, m_cboTrigCouple);
	DDX_Control(pDX, IDC_CBO_TRIG_SLOPE, m_cboTrigSlope);
	DDX_Control(pDX, IDC_CBO_TRIG_SRC, m_cboTrigSrc);
	DDX_Control(pDX, IDC_BTN_RUN_STOP, m_btnRunStop);
	DDX_Control(pDX, IDC_CBO_CH_VOLT, m_cboChVolt);
	DDX_Control(pDX, IDC_CBO_CH_COUPLE, m_cboChCouple);
	DDX_Control(pDX, IDC_CHK_CH_ENABLE, m_chkChEnable);
	DDX_Control(pDX, IDC_CBO_CH, m_cboCH);
	DDX_Control(pDX, IDC_CBO_TIMEBASE, m_cboTimebase);
	DDX_Control(pDX, IDC_MAINPANEL, m_MainPanel);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVCDlg, CDialog)
	//{{AFX_MSG_MAP(CVCDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_CBO_TIMEBASE, OnSelchangeCboTimebase)
	ON_CBN_SELCHANGE(IDC_CBO_CH, OnSelchangeCboCh)
	ON_CBN_SELCHANGE(IDC_CBO_CH_COUPLE, OnSelchangeCboChCouple)
	ON_CBN_SELCHANGE(IDC_CBO_CH_VOLT, OnSelchangeCboChVolt)
	ON_BN_CLICKED(IDC_BTN_RUN_STOP, OnBtnRunStop)
	ON_BN_CLICKED(IDC_CHK_CH_ENABLE, OnChkChEnable)
	ON_CBN_SELCHANGE(IDC_CBO_TRIG_SRC, OnSelchangeCboTrigSrc)
	ON_CBN_SELCHANGE(IDC_CBO_TRIG_SLOPE, OnSelchangeCboTrigSlope)
	ON_CBN_SELCHANGE(IDC_CBO_TRIG_COUPLE, OnSelchangeCboTrigCouple)
	ON_CBN_SELCHANGE(IDC_CBO_TRIG_SWEEP, OnSelchangeCboTrigSweep)
	ON_EN_KILLFOCUS(IDC_EDIT_CH_LEVEL, OnKillfocusEditChLevel)
	ON_EN_KILLFOCUS(IDC_EDIT_TRIG_LEVEL, OnKillfocusEditTrigLevel)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CVCDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVCDlg message handlers

BOOL CVCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	InitVariables();
	if(0 == dsoHTDeviceConnect(m_Hard->m_nDeviceIndex))
	{
		//No device Connected
		AfxMessageBox(_T("No Device!"));
	}
	else
	{
		//Need to Obtain detail Information and Initial device State
		InitHardDevice();
		SetTimer(0,20,NULL);

		//Initial Drawing CDC
		CRect imgRect ;
		m_MainPanel.GetClientRect(&imgRect);
		CDC *pDC = m_MainPanel.GetDC();
		CreateMemoryDC(pDC,imgRect);
	}
	InitControls();
	UpdateCtrls();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVCDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVCDlg::OnOK() 
{
	// TODO: Add extra validation here

	//	CDialog::OnOK();
}

void CVCDlg::OnCancel() 
{
	// TODO: Add extra cleanup here

	CDialog::OnCancel();
}

void CVCDlg::InitVariables()
{
	m_Hard->m_nDeviceIndex = 0;
	m_bRunStop = TRUE;
}

void CVCDlg::InitHardDevice()
{
	USHORT nReturn;
	//After Powering on device, you must do this.
	//Reset Device
	nReturn = dsoHMResetDevice(m_Hard->m_nDeviceIndex);		
	//Get FPGA Version
	m_Hard->m_nFPGAVersion = dsoGetFPGAVersion(m_Hard->m_nDeviceIndex);
	//Get Self Calibration Result
	dsoHTReadCalibrationData(m_Hard->m_nDeviceIndex,m_Hard->m_nCalLevel,CAL_LEVEL_LEN);	
	//Get Amplitude Correction calibration Result
	nReturn = dsoHMReadAmpCorrectData(m_Hard->m_nDeviceIndex,m_Hard->m_fAmpCorrect,MAX_CH_NUM*MAX_VOLTDIV_NUM*CAL_CHANNEL_MODEL);	
	//Computer Twelve Road DAC Voltage
	m_Hard->ComputerTwelveRoadVoltage();

	//Start Bus Trigger(Reserved)
	nReturn = dsoSetUSBBus(m_Hard->m_nDeviceIndex);		
	//Start Fan
	nReturn = dsoHMSetFanControlState(m_Hard->m_nDeviceIndex,1);	//1:Open  0:Close
	//Set AD Clock Work Type
	nReturn = dsoHMSetADClockType(m_Hard->m_nDeviceIndex,&m_Hard->m_stControl,&m_Hard->m_stRelayControl);
	//Set Sampling Rate
	nReturn = dsoHMSetSampleRate(m_Hard->m_nDeviceIndex,m_Hard->m_stControl.nTimeDIV,&m_Hard->m_stRelayControl);
	//Set Buffer Size
	nReturn = dsoHMSetBufferSize(m_Hard->m_nDeviceIndex,&m_Hard->m_stControl);
	//Set Trigger Control and Sync Control
	m_Hard->SetTriggerAndSyncOutput();
	Sleep(1);
	m_Hard->SetTriggerAndSyncOutput();
	//Close Peak Detect Sampling Mode
	nReturn = dsoHMClosePeakDetect(m_Hard->m_nDeviceIndex);
	//Set Channel and Trigger Souce
	m_Hard->SetCHAndTrigger(m_Hard->m_stRelayControl);
	//Set Twelve Road DAC Voltage
	m_Hard->SetDACVoltageforTwelveRoad();
	//Set Channel Swith Type
	dsoHMSetChannelSwitch(m_Hard->m_nDeviceIndex,&m_Hard->m_stRelayControl);
	//Set Amplitude Correction Ratio
	m_Hard->SetAmpCorrectRatio();

	//Flag
	m_Hard->m_bStartNormalCollect = TRUE;

}

void CVCDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	if(0 == dsoHTDeviceConnect(m_Hard->m_nDeviceIndex))
	{
		KillTimer(0);
		//No device Connected
		AfxMessageBox(_T("No Device!"));
		return;
	}
	else
	{
		m_Hard->CollectData();
		if(m_Hard->m_nCollectState == 7 && m_Hard->m_nReadOK == 1)
		{
			//Draw Wave
			DrawWave(&m_dcMemory,m_rcMemory);

			CDC *pDC = m_MainPanel.GetDC();
			pDC->BitBlt(m_rcMemory.left,m_rcMemory.top,m_rcMemory.Width(),m_rcMemory.Height(),&m_dcMemory,0,0,SRCCOPY);

			if(m_Hard->m_Trigger.m_nSweep == TRIG_SINGLE)
			{
				//Single Trigger needs stopping collecting

				m_bRunStop = FALSE;
				m_btnRunStop.SetWindowText(_T("Run"));					
				KillTimer(0);
			}
			if(mca_flag)
			{
				int max=0;
				for(int i=0;i<m_Hard->m_stControl.nReadDataLen;i++)
				{
					short adc= m_Hard->m_CH[0].m_pSrcData[i];
					max=(adc>max)?adc:max;
				}
				if(max>0)mca[max]++;
			}
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CVCDlg::DrawWave(CDC* pDC,CRect Rect)
{
	//Draw Grid
	pDC->FillSolidRect(Rect,RGB(0,0,0));
	HTDrawGrid(pDC->GetSafeHdc(),Rect.left,Rect.top,Rect.right,Rect.bottom,10,8,200,1);		//10:Ten rows  //8:Eight Lines //200:Contrast ratio  //1:Grid Line is dotted(or 0:No Grid Line)

	//Draw CH
	for(int i=0;i<MAX_CH_NUM;i++)
	{
		if(m_Hard->m_CH[i].m_bOnOff)
		{
			DrawWaveInYT(pDC,Rect,i);
		}
	}

}

void CVCDlg::DrawWaveInYT(CDC* pDC,CRect Rect,USHORT nCH)
{
	short* pData = m_Hard->m_CH[nCH].m_pSrcData;							//源数据
	ULONG nDisDataLen = m_Hard->m_CH[nCH].m_nDrawDataLen;				//网格内要画的数据长度
	ULONG nSrcDataLen = m_Hard->m_CH[nCH].m_nSrcDataLen;					//源数据的长度
	USHORT nLeverPos = m_Hard->m_CH[nCH].m_nLeverPos;					//零电平的显示位置
	COLORREF clrRGB = m_Hard->m_CH[nCH].m_clrRGB;						//颜色
	USHORT nHTriggerPos = m_Hard->m_nHTriggerPos;						//水平触发点位置
	USHORT nYTFormat = 0;   //0:YT
	USHORT nDisType = 0;	//0:Line  1::Dot

	HTDrawWaveInYT(pDC->GetSafeHdc(),Rect,clrRGB,nDisType,pData,nSrcDataLen,nDisDataLen,nSrcDataLen/2,nLeverPos,1.000,1.000,0,0);//DLL import
}

void CVCDlg::CreateMemoryDC(CDC *pDC, CRect Rect)
{
	if(m_dcMemory != NULL)
	{
		//Release Old Resources
		m_dcMemory.DeleteDC();
		m_bmpMemory.DeleteObject();
	}
	//Area
	m_rcMemory = Rect;
	//Memory CDC
	m_dcMemory.CreateCompatibleDC(pDC);
	m_bmpMemory.CreateCompatibleBitmap(pDC,Rect.Width(),Rect.Height());
	m_dcMemory.SelectObject(&m_bmpMemory);

}

void CVCDlg::InitControls()
{
	int i = 0;
	CString str;
	m_cboTimebase.ResetContent();
	m_cboTimebase.AddString(_T("5.000ns"));
	m_cboTimebase.AddString(_T("10.00ns"));
	m_cboTimebase.AddString(_T("20.00ns"));
	m_cboTimebase.AddString(_T("50.00ns"));
	m_cboTimebase.AddString(_T("100.0ns"));
	m_cboTimebase.AddString(_T("200.0ns"));
	m_cboTimebase.AddString(_T("500.0ns"));
	m_cboTimebase.AddString(_T("1.000us"));
	m_cboTimebase.AddString(_T("2.000us"));
	m_cboTimebase.AddString(_T("5.000us"));
	m_cboTimebase.AddString(_T("10.00us"));
	m_cboTimebase.AddString(_T("20.00us"));
	m_cboTimebase.AddString(_T("50.00us"));
	m_cboTimebase.AddString(_T("100.0us"));
	m_cboTimebase.AddString(_T("200.0us"));
	m_cboTimebase.AddString(_T("500.0us"));
	m_cboTimebase.AddString(_T("1.000ms"));
	m_cboTimebase.AddString(_T("2.000ms"));
	m_cboTimebase.AddString(_T("5.000ms"));
	m_cboTimebase.AddString(_T("10.00ms"));
	m_cboTimebase.AddString(_T("20.00ms"));
	m_cboTimebase.AddString(_T("50.00ms"));
	m_cboTimebase.AddString(_T("100.0ms"));
	m_cboTimebase.SetCurSel(12);

	m_cboCH.ResetContent();
	for(i=0;i<MAX_CH_NUM;i++)
	{
		str.Format(_T("CH%d"),i+1);
		m_cboCH.AddString(str);
	}
	m_cboCH.SetCurSel(0);

	m_cboChVolt.ResetContent();
	m_cboChVolt.AddString(_T("1.000mV"));
	m_cboChVolt.AddString(_T("2.000mV"));
	m_cboChVolt.AddString(_T("5.000mV"));
	m_cboChVolt.AddString(_T("10.00mV"));
	m_cboChVolt.AddString(_T("20.00mV"));
	m_cboChVolt.AddString(_T("50.00mV"));
	m_cboChVolt.AddString(_T("100.0mV"));
	m_cboChVolt.AddString(_T("200.0mV"));
	m_cboChVolt.AddString(_T("500.0mV"));
	m_cboChVolt.AddString(_T("1.000V"));
	m_cboChVolt.AddString(_T("2.000V"));
	m_cboChVolt.AddString(_T("5.000V"));
	m_cboChVolt.SetCurSel(9);


	m_cboChCouple.ResetContent();
	m_cboChCouple.AddString(_T("DC"));
	m_cboChCouple.AddString(_T("AC"));
	m_cboChCouple.SetCurSel(0);

	m_cboTrigSrc.ResetContent();
	for(i=0;i<MAX_CH_NUM;i++)
	{
		str.Format(_T("CH%d"),i+1);
		m_cboTrigSrc.AddString(str);
	}
	m_cboTrigSrc.SetCurSel(0);

	m_cboTrigSlope.ResetContent();
	m_cboTrigSlope.AddString(_T("+"));
	m_cboTrigSlope.AddString(_T("-"));
	m_cboTrigSlope.SetCurSel(0);

	m_cboTrigCouple.ResetContent();
	m_cboTrigCouple.AddString(_T("AC"));
	m_cboTrigCouple.AddString(_T("DC"));
	m_cboTrigCouple.SetCurSel(0);

	m_cboTrigSweep.ResetContent();
	m_cboTrigSweep.AddString(_T("Auto"));
	m_cboTrigSweep.AddString(_T("Normal"));
	m_cboTrigSweep.AddString(_T("Single"));
	m_cboTrigSweep.SetCurSel(0);
}

void CVCDlg::UpdateCtrls()
{
	CString str;
	m_cboTimebase.SetCurSel(m_Hard->m_stControl.nTimeDIV);
	m_cboCH.SetCurSel(m_Hard->m_nCurCH);
	m_chkChEnable.SetCheck(m_Hard->m_CH[m_Hard->m_nCurCH].m_bOnOff);
	m_cboChVolt.SetCurSel(m_Hard->m_CH[m_Hard->m_nCurCH].m_nVoltDIV);
	m_cboChCouple.SetCurSel(m_Hard->m_CH[m_Hard->m_nCurCH].m_nCoupling);
	str.Format(_T("%d"),m_Hard->m_CH[m_Hard->m_nCurCH].m_nLeverPos);
	m_editChLevel.SetWindowText(str);
	if(m_bRunStop)
	{
		m_btnRunStop.SetWindowText(_T("Stop"));
	}
	m_cboTrigSrc.SetCurSel(m_Hard->m_Trigger.m_nSource);
	m_cboTrigSweep.SetCurSel(m_Hard->m_Trigger.m_nSweep);
	m_cboTrigSlope.SetCurSel(m_Hard->m_Trigger.m_nSlope);
	m_cboTrigCouple.SetCurSel(m_Hard->m_Trigger.m_nCoupling);
	str.Format(_T("%d"),m_Hard->m_Trigger.m_nLeverPos[m_Hard->m_Trigger.m_nSource]);
	m_editTrigLevel.SetWindowText(str);
}

void CVCDlg::OnBtnRunStop() 
{
	// TODO: Add your control notification handler code here
	if(m_bRunStop)
	{
		m_bRunStop = FALSE;
		m_btnRunStop.SetWindowText(_T("Run"));	

		KillTimer(0);
	}
	else
	{
		m_bRunStop = TRUE;
		m_btnRunStop.SetWindowText(_T("Stop"));

		SetTimer(0,100,NULL);
	}
}

void CVCDlg::OnSelchangeCboTimebase() 
{
	// TODO: Add your control notification handler code here
	USHORT nReturn;
	int nTimeDiv = m_cboTimebase.GetCurSel();
	//Change Set
	m_Hard->m_stControl.nTimeDIV = nTimeDiv;
	//Set Sampling Rate
	nReturn = dsoHMSetSampleRate(m_Hard->m_nDeviceIndex,m_Hard->m_stControl.nTimeDIV,&m_Hard->m_stRelayControl);
	//
	m_Hard->m_bStartNormalCollect = TRUE;
}

void CVCDlg::OnSelchangeCboCh() 
{
	// TODO: Add your control notification handler code here
	m_Hard->m_nCurCH = m_cboCH.GetCurSel();
	UpdateCtrls();
}

void CVCDlg::OnChkChEnable() 
{
	// TODO: Add your control notification handler code here
	int nReturn;
	int nChk = m_chkChEnable.GetCheck();
	//Change available
	m_Hard->m_CH[m_Hard->m_nCurCH].m_bOnOff = nChk;
	m_Hard->m_stRelayControl.bCHEnable[m_Hard->m_nCurCH] = nChk;
	m_Hard->m_stControl.nCHSet = 0;
	for(int i=0;i<MAX_CH_NUM;i++)
	{
		USHORT n = 0;
		if(m_Hard->m_CH[i].m_bOnOff)
		{
			n = (USHORT)pow(2.,i);
		}
		m_Hard->m_stControl.nCHSet += n;
	}
	//Set Channel and Trigger Souce
	m_Hard->SetCHAndTrigger(m_Hard->m_stRelayControl);
	//Set Channel Swith Type
	dsoHMSetChannelSwitch(m_Hard->m_nDeviceIndex,&m_Hard->m_stRelayControl);
	//Set Sampling Rate
	nReturn = dsoHMSetSampleRate(m_Hard->m_nDeviceIndex,m_Hard->m_stControl.nTimeDIV,&m_Hard->m_stRelayControl);
	//Set Buffer Size
	nReturn = dsoHMSetBufferSize(m_Hard->m_nDeviceIndex,&m_Hard->m_stControl);
	//Computer Twelve Road DAC Voltage
	m_Hard->ComputerTwelveRoadVoltage();
	//Set Twelve Road DAC Voltage
	m_Hard->SetDACVoltageforTwelveRoad();
	//Set Amplitude Correction Ratio
	m_Hard->SetAmpCorrectRatio();
	//
	m_Hard->m_bStartNormalCollect = TRUE;	
}

void CVCDlg::OnSelchangeCboChVolt() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cboChVolt.GetCurSel();
	m_Hard->m_CH[m_Hard->m_nCurCH].m_nVoltDIV = nSel;
	m_Hard->m_stRelayControl.nCHVoltDIV[m_Hard->m_nCurCH] = nSel;
	//Set Channel and Trigger Souce
	m_Hard->SetCHAndTrigger(m_Hard->m_stRelayControl);
	//Computer Twelve Road DAC Voltage
	m_Hard->ComputerTwelveRoadVoltage();
	//Set Twelve Road DAC Voltage
	m_Hard->SetDACVoltageforTwelveRoad();
	//
	m_Hard->m_bStartNormalCollect = TRUE;	
}

void CVCDlg::OnSelchangeCboChCouple() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cboChCouple.GetCurSel();
	m_Hard->m_CH[m_Hard->m_nCurCH].m_nCoupling = nSel;
	m_Hard->m_stRelayControl.nCHCoupling[m_Hard->m_nCurCH] = nSel;
	//Set Channel and Trigger Souce
	m_Hard->SetCHAndTrigger(m_Hard->m_stRelayControl);
	//Computer Twelve Road DAC Voltage
	m_Hard->ComputerTwelveRoadVoltage();
	//Set Twelve Road DAC Voltage
	m_Hard->SetDACVoltageforTwelveRoad();
	//
	m_Hard->m_bStartNormalCollect = TRUE;
}

void CVCDlg::OnKillfocusEditChLevel() 
{
	// TODO: Add your control notification handler code here
	CString str;
	int nLevel;
	m_editChLevel.GetWindowText(str);
	nLevel = atoi(str);
	if(nLevel > 255)
	{
		nLevel = 255;
		str.Format(_T("%d"),nLevel);
		m_editChLevel.SetWindowText(str);
	}
	else if(nLevel < 0)
	{
		nLevel = 0;
		str.Format(_T("%d"),nLevel);
		m_editChLevel.SetWindowText(str);
	}
	m_Hard->m_CH[m_Hard->m_nCurCH].m_nLeverPos = nLevel;
	//Computer Twelve Road DAC Voltage
	m_Hard->ComputerTwelveRoadVoltage();
	//Set Twelve Road DAC Voltage
	m_Hard->SetDACVoltageforTwelveRoad();
	//
	m_Hard->m_bStartNormalCollect = TRUE;

}

void CVCDlg::OnSelchangeCboTrigSrc() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cboTrigSrc.GetCurSel();
	m_Hard->m_Trigger.m_nSource = nSel;
	m_Hard->m_stControl.nTriggerSource = nSel;
	m_Hard->m_stControl.nVTriggerPos = m_Hard->m_Trigger.m_nLeverPos[m_Hard->m_Trigger.m_nSource];
	m_Hard->m_stRelayControl.nTrigSource = m_Hard->m_Trigger.m_nSource;
	//Set Channel and Trigger Souce
	m_Hard->SetCHAndTrigger(m_Hard->m_stRelayControl);
	//Set Trigger Control and Sync Control
	m_Hard->SetTriggerAndSyncOutput();
	Sleep(1);
	m_Hard->SetTriggerAndSyncOutput();
	//Computer Twelve Road DAC Voltage
	m_Hard->ComputerTwelveRoadVoltage();
	//Set Twelve Road DAC Voltage
	m_Hard->SetDACVoltageforTwelveRoad();
	//Set Amplitude Correction Ratio
	m_Hard->SetAmpCorrectRatio();
	//
	m_Hard->m_bStartNormalCollect = TRUE;
	UpdateCtrls();
}

void CVCDlg::OnSelchangeCboTrigSlope() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	int nSel = m_cboTrigSlope.GetCurSel();	
	m_Hard->m_stControl.nTriggerSlope = nSel;
	m_Hard->m_Trigger.m_nSlope = nSel;

	//Set Trigger Control and Sync Control
	m_Hard->SetTriggerAndSyncOutput();
	Sleep(1);
	m_Hard->SetTriggerAndSyncOutput();
	//
	m_Hard->m_bStartNormalCollect = TRUE;

}

void CVCDlg::OnSelchangeCboTrigCouple() 
{
	// TODO: Add your control notification handler code here

	// TODO: Add your control notification handler code here
	int nSel = m_cboTrigCouple.GetCurSel();
	m_Hard->m_Trigger.m_nCoupling= nSel;
	//Set Channel and Trigger Souce
	m_Hard->SetCHAndTrigger(m_Hard->m_stRelayControl);
	//Set Trigger Control and Sync Control
	m_Hard->SetTriggerAndSyncOutput();
	//Computer Twelve Road DAC Voltage
	m_Hard->ComputerTwelveRoadVoltage();
	//Set Twelve Road DAC Voltage
	m_Hard->SetDACVoltageforTwelveRoad();
	//Set Amplitude Correction Ratio
	m_Hard->SetAmpCorrectRatio();
	//
	m_Hard->m_bStartNormalCollect = TRUE;
}

void CVCDlg::OnSelchangeCboTrigSweep() 
{
	// TODO: Add your control notification handler code here
	m_Hard->m_Trigger.m_nSweep = m_cboTrigSweep.GetCurSel();
}

void CVCDlg::OnKillfocusEditTrigLevel() 
{
	// TODO: Add your control notification handler code here
	CString str;
	int nLevel;
	m_editTrigLevel.GetWindowText(str);
	nLevel = atoi(str);
	if(nLevel > 255)
	{
		nLevel = 255;
		str.Format(_T("%d"),nLevel);
		m_editTrigLevel.SetWindowText(str);
	}
	else if(nLevel < 0)
	{
		nLevel = 0;
		str.Format(_T("%d"),nLevel);
		m_editTrigLevel.SetWindowText(str);
	}
	m_Hard->m_Trigger.m_nLeverPos[m_Hard->m_Trigger.m_nSource] = nLevel;
	//Computer Twelve Road DAC Voltage
	m_Hard->ComputerTwelveRoadVoltage();
	//Set Twelve Road DAC Voltage
	m_Hard->SetDACVoltageforTwelveRoad();
	//
	m_Hard->m_bStartNormalCollect = TRUE;
}

BOOL CVCDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	//Close Fan
	int nReturn = dsoHMSetFanControlState(m_Hard->m_nDeviceIndex,0);	//1:Open  0:Close
	if(mca_flag)
	{
		for(int i=0;i<MCA_CH;i++)f_out<<mca[i]<<"\n";
		f_out.close();
	}
	return CDialog::DestroyWindow();
}

void CVCDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	if(mca_flag)
	{
		for(int i=0;i<MCA_CH;i++)f_out<<mca[i]<<"\n";
		f_out.close();
		GetDlgItem(IDC_BUTTON1)->SetWindowText(_T("MCA"));	
		mca_flag=false;
	}
	else
	{
		f_out.open("MCA.txt");
		for(int i=0;i<MCA_CH;i++)mca[i]=0;
		mca_flag=true;
		GetDlgItem(IDC_BUTTON1)->SetWindowText(_T("Stop"));
	}
}
