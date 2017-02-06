
// DSO-SampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DSO-Sample.h"
#include "DSO-SampleDlg.h"
#include "afxdialogex.h"
#include "TFile.h"
#include "TGraph.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedStaticPic();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_STN_CLICKED(IDC_STATIC_PIC, &CAboutDlg::OnStnClickedStaticPic)
END_MESSAGE_MAP()


// CDSOSampleDlg dialog



CDSOSampleDlg::CDSOSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DSOSAMPLE_DIALOG, pParent)
	, runflag(false)
	, Ch1_offset(0)
	, Ch2_offset(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_LPDA);
	rootv = new Viewer(this);
	m_Hard = new CHard();
	gf = new DrawGraph();
}

void CDSOSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_V_DIV, m_cboChVolt);
	DDX_Control(pDX, IDC_V_Couple, m_cboChCouple);
	DDX_Control(pDX, IDC_CH_ON, m_chkChEnable);
	DDX_Control(pDX, IDC_V_Ch, m_cboCH);
	DDX_Control(pDX, IDC_T_DIV, m_cboTimebase);
	DDX_Control(pDX, IDC_Tri_Sweep, m_cboTrigSweep);
	DDX_Control(pDX, IDC_Tri_Source, m_cboTrigSrc);
	DDX_Control(pDX, IDC_Tri_Slope, m_cboTrigSlope);
	DDX_Control(pDX, IDC_Tri_Couple, m_cboTrigCouple);
	DDX_Control(pDX, IDC_V_Position, m_cslChPosition);
	DDX_Control(pDX, IDC_Tri_Level, m_cslTriPosition);

}

BEGIN_MESSAGE_MAP(CDSOSampleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDSOSampleDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDSOSampleDlg::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_V_DIV, &CDSOSampleDlg::OnCbnSelchangeVDiv)
	ON_CBN_SELCHANGE(IDC_V_Couple, &CDSOSampleDlg::OnCbnSelchangeVCouple)
	ON_BN_CLICKED(IDC_CH_ON, &CDSOSampleDlg::OnBnClickedChOn)
	ON_CBN_SELCHANGE(IDC_V_Ch, &CDSOSampleDlg::OnCbnSelchangeVCh)
	ON_CBN_SELCHANGE(IDC_T_DIV, &CDSOSampleDlg::OnCbnSelchangeTDiv)
	ON_CBN_SELCHANGE(IDC_Tri_Sweep, &CDSOSampleDlg::OnCbnSelchangeTriSweep)
	ON_CBN_SELCHANGE(IDC_Tri_Source, &CDSOSampleDlg::OnCbnSelchangeTriSource)
	ON_CBN_SELCHANGE(IDC_Tri_Slope, &CDSOSampleDlg::OnCbnSelchangeTriSlope)
	ON_CBN_SELCHANGE(IDC_Tri_Couple, &CDSOSampleDlg::OnCbnSelchangeTriCouple)
	ON_BN_CLICKED(IDC_BUTTON_About, &CDSOSampleDlg::OnBnClickedButtonAbout)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CDSOSampleDlg message handlers

BOOL CDSOSampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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
	if (0 == dsoHTDeviceConnect(m_Hard->m_nDeviceIndex))
	{
		//No device Connected
		AfxMessageBox(_T("No Device!"));
	}
	else
	{
		//Need to Obtain detail Information and Initial device State
		InitHardDevice();
	}
	InitControls();
	UpdateCtrls();
	SetTimer(1, 5, NULL);//set the data collection timer
	SetTimer(2, 10, NULL);//set the Drawing timer
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDSOSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDSOSampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDSOSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



// initial the DSO hardware
bool CDSOSampleDlg::InitHardDevice()
{
	USHORT nReturn;
	//After Powering on device, you must do this.
	//Reset Device
	nReturn = dsoHMResetDevice(m_Hard->m_nDeviceIndex);
	//Get FPGA Version
	m_Hard->m_nFPGAVersion = dsoGetFPGAVersion(m_Hard->m_nDeviceIndex);
	//Get Self Calibration Result
	dsoHTReadCalibrationData(m_Hard->m_nDeviceIndex, m_Hard->m_nCalLevel, CAL_LEVEL_LEN);
	//Get Amplitude Correction calibration Result
	nReturn = dsoHMReadAmpCorrectData(m_Hard->m_nDeviceIndex, m_Hard->m_fAmpCorrect, MAX_CH_NUM*MAX_VOLTDIV_NUM*CAL_CHANNEL_MODEL);
	//Computer Twelve Road DAC Voltage
	m_Hard->ComputerTwelveRoadVoltage();

	//Start Bus Trigger(Reserved)
	nReturn = dsoSetUSBBus(m_Hard->m_nDeviceIndex);
	//Start Fan
	nReturn = dsoHMSetFanControlState(m_Hard->m_nDeviceIndex, 1);	//1:Open  0:Close
																	//Set AD Clock Work Type
	nReturn = dsoHMSetADClockType(m_Hard->m_nDeviceIndex, &m_Hard->m_stControl, &m_Hard->m_stRelayControl);
	//Set Sampling Rate
	nReturn = dsoHMSetSampleRate(m_Hard->m_nDeviceIndex, m_Hard->m_stControl.nTimeDIV, &m_Hard->m_stRelayControl);
	//Set Buffer Size
	nReturn = dsoHMSetBufferSize(m_Hard->m_nDeviceIndex, &m_Hard->m_stControl);
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
	dsoHMSetChannelSwitch(m_Hard->m_nDeviceIndex, &m_Hard->m_stRelayControl);
	//Set Amplitude Correction Ratio
	m_Hard->SetAmpCorrectRatio();

	//Flag
	m_Hard->m_bStartNormalCollect = TRUE;
	return false;
}


void CDSOSampleDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
	//open ROOT viewer
	if (rootv->GetSafeHwnd() == NULL)
	{
		rootv->Create(MAKEINTRESOURCE(IDD_DIALOG1), this);
	}
	//else AfxMessageBox(_T("监视界面已经打开！"));
	rootv->ShowWindow(SW_SHOW);
	//
	if (0 == dsoHTDeviceConnect(m_Hard->m_nDeviceIndex))
	{
		//No device Connected
		AfxMessageBox(_T("No Device!"));
		return;
	}
	runflag = true;
}


void CDSOSampleDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	int nReturn = dsoHMSetFanControlState(m_Hard->m_nDeviceIndex, 0);	//1:Open  0:Close
	CDialogEx::OnCancel();
}


void CDSOSampleDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnTimer(nIDEvent);
	switch (nIDEvent)
	{
	case 1:
		if (runflag)
		{
			m_Hard->CollectData();
			if (m_Hard->m_nCollectState == 7 && m_Hard->m_nReadOK == 1)
			{
				int nBin = m_Hard->m_stControl.nReadDataLen;
				double* t_axis = new double[nBin];
				double* v_axis1 = new double[nBin];
				double* v_axis2 = new double[nBin];
				for (int i = 0; i < m_Hard->m_stControl.nReadDataLen; i++)
				{

					t_axis[i] = i;
					v_axis1[i] = m_Hard->m_CH[0].m_pSrcData[i];
					v_axis2[i] = m_Hard->m_CH[1].m_pSrcData[i];
				}
				gf->SetTGraph(nBin, t_axis, v_axis1, v_axis2);
				rootv->GetGraph(gf->MakeTGraph());
				delete t_axis;
				delete v_axis1;
				delete v_axis2;
			}
		};
		break;
	case 2:
		rootv->Drawing();
		break;
	default:
		break;
	}
}


BOOL CDSOSampleDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	if (rootv)delete rootv;
	if (m_Hard)delete m_Hard;
	if (gf)delete gf;
	return CDialogEx::DestroyWindow();
}

void CDSOSampleDlg::OnCbnSelchangeVDiv()
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


void CDSOSampleDlg::InitControls()
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
	for (i = 0; i < MAX_CH_NUM; i++)
	{
		str.Format(_T("CH%d"), i + 1);
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
	for (i = 0; i < MAX_CH_NUM; i++)
	{
		str.Format(_T("CH%d"), i + 1);
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

	m_cslChPosition.SetRange(-255, 255);
	m_cslChPosition.SetTicFreq(1);

	m_cslTriPosition.SetRange(0, 255);
	m_cslTriPosition.SetTicFreq(1);
	//Drawing the trigger
	m_cslTriPosition.SetPos(MID_DATA);
}


void CDSOSampleDlg::OnCbnSelchangeVCouple()
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


void CDSOSampleDlg::UpdateCtrls()
{
	CString str;
	//m_cboTimebase.SetCurSel(m_Hard->m_stControl.nTimeDIV);
	m_cboCH.SetCurSel(m_Hard->m_nCurCH);
	m_chkChEnable.SetCheck(m_Hard->m_CH[m_Hard->m_nCurCH].m_bOnOff);
	m_cboChVolt.SetCurSel(m_Hard->m_CH[m_Hard->m_nCurCH].m_nVoltDIV);
	m_cboChCouple.SetCurSel(m_Hard->m_CH[m_Hard->m_nCurCH].m_nCoupling);
	/*str.Format(_T("%d"), m_Hard->m_CH[m_Hard->m_nCurCH].m_nLeverPos);
	m_editChLevel.SetWindowText(str);
	if (m_bRunStop)
	{
		m_btnRunStop.SetWindowText(_T("Stop"));
	}*/
	m_cboTrigSrc.SetCurSel(m_Hard->m_Trigger.m_nSource);
	m_cboTrigSweep.SetCurSel(m_Hard->m_Trigger.m_nSweep);
	m_cboTrigSlope.SetCurSel(m_Hard->m_Trigger.m_nSlope);
	m_cboTrigCouple.SetCurSel(m_Hard->m_Trigger.m_nCoupling);
	//str.Format(_T("%d"), m_Hard->m_Trigger.m_nLeverPos[m_Hard->m_Trigger.m_nSource]);
	//m_editTrigLevel.SetWindowText(str);
	//Drawing the trigger
	ShowTrigger();
}


void CDSOSampleDlg::OnBnClickedChOn()
{
	// TODO: Add your control notification handler code here
	int nReturn;
	int nChk = m_chkChEnable.GetCheck();
	//Change available
	m_Hard->m_CH[m_Hard->m_nCurCH].m_bOnOff = nChk;
	m_Hard->m_stRelayControl.bCHEnable[m_Hard->m_nCurCH] = nChk;
	m_Hard->m_stControl.nCHSet = 0;
	for (int i = 0; i < MAX_CH_NUM; i++)
	{
		USHORT n = 0;
		if (m_Hard->m_CH[i].m_bOnOff)
		{
			n = (USHORT)pow(2., i);
		}
		m_Hard->m_stControl.nCHSet += n;
		//Set the Drawing
		gf->SetChOn(i, m_Hard->m_CH[i].m_bOnOff);
	}
	//Set Channel and Trigger Souce
	m_Hard->SetCHAndTrigger(m_Hard->m_stRelayControl);
	//Set Channel Swith Type
	dsoHMSetChannelSwitch(m_Hard->m_nDeviceIndex, &m_Hard->m_stRelayControl);
	//Set Sampling Rate
	nReturn = dsoHMSetSampleRate(m_Hard->m_nDeviceIndex, m_Hard->m_stControl.nTimeDIV, &m_Hard->m_stRelayControl);
	//Set Buffer Size
	nReturn = dsoHMSetBufferSize(m_Hard->m_nDeviceIndex, &m_Hard->m_stControl);
	//Computer Twelve Road DAC Voltage
	m_Hard->ComputerTwelveRoadVoltage();
	//Set Twelve Road DAC Voltage
	m_Hard->SetDACVoltageforTwelveRoad();
	//Set Amplitude Correction Ratio
	m_Hard->SetAmpCorrectRatio();
	//
	m_Hard->m_bStartNormalCollect = TRUE;
}


void CDSOSampleDlg::OnCbnSelchangeVCh()
{
	// TODO: Add your control notification handler code here
	m_Hard->m_nCurCH = m_cboCH.GetCurSel();
	UpdateCtrls();
}


void CDSOSampleDlg::OnCbnSelchangeTDiv()
{
	// TODO: Add your control notification handler code here
	USHORT nReturn;
	int nTimeDiv = m_cboTimebase.GetCurSel();
	//Change Set
	m_Hard->m_stControl.nTimeDIV = nTimeDiv;
	//Set Sampling Rate
	nReturn = dsoHMSetSampleRate(m_Hard->m_nDeviceIndex, m_Hard->m_stControl.nTimeDIV, &m_Hard->m_stRelayControl);
	//
	m_Hard->m_bStartNormalCollect = TRUE;

}


void CDSOSampleDlg::OnCbnSelchangeTriSweep()
{
	// TODO: Add your control notification handler code here
	m_Hard->m_Trigger.m_nSweep = m_cboTrigSweep.GetCurSel();
}


void CDSOSampleDlg::OnCbnSelchangeTriSource()
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


void CDSOSampleDlg::OnCbnSelchangeTriSlope()
{
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


void CDSOSampleDlg::OnCbnSelchangeTriCouple()
{
	// TODO: Add your control notification handler code here
	int nSel = m_cboTrigCouple.GetCurSel();
	m_Hard->m_Trigger.m_nCoupling = nSel;
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


void CDSOSampleDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDSOSampleDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	CWnd *pSliderVPos = this->GetDlgItem(IDC_V_Position);
	CWnd *pSliderTri = this->GetDlgItem(IDC_Tri_Level);
	if (pScrollBar == pSliderVPos)
	{
		CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_V_Position);
		int nLevel = pSlidCtrl->GetPos();//取得当前位置值  
		/*if (m_Hard->m_nCurCH == 0) { Ch1_offset = nLevel; }
		else if (m_Hard->m_nCurCH == 1) { Ch2_offset = nLevel; }*/

		m_Hard->m_CH[m_Hard->m_nCurCH].m_nLeverPos = nLevel;
		//Computer Twelve Road DAC Voltage
		m_Hard->ComputerTwelveRoadVoltage();
		//Set Twelve Road DAC Voltage
		m_Hard->SetDACVoltageforTwelveRoad();
		//
		m_Hard->m_bStartNormalCollect = TRUE;
		CString position_str;
		position_str.Format(L"%d", nLevel);
		GetDlgItem(IDC_V_Position_S)->SetWindowText(position_str);
	}
	if (pScrollBar == pSliderTri)
	{
		ShowTrigger();
	}
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CDSOSampleDlg::ShowTrigger()
{
	CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_Tri_Level);
	int nLevel = pSlidCtrl->GetPos();//取得当前位置值  
	m_Hard->m_Trigger.m_nLeverPos[m_Hard->m_Trigger.m_nSource] = nLevel;
	//Computer Twelve Road DAC Voltage
	m_Hard->ComputerTwelveRoadVoltage();
	//Set Twelve Road DAC Voltage
	m_Hard->SetDACVoltageforTwelveRoad();
	//
	m_Hard->m_bStartNormalCollect = TRUE;
	CString position_str;
	position_str.Format(L"%d", nLevel);
	GetDlgItem(IDC_Tri_Level_S)->SetWindowText(position_str);
	rootv->MakeTriLine(m_Hard->m_Trigger.m_nSource, nLevel);
}


void CAboutDlg::OnStnClickedStaticPic()
{
	// TODO: Add your control notification handler code here
	//从资源中加载图片
	CBitmap bitmap;
	//加载指定位图资源 Bmp图片ID
	bitmap.LoadBitmap(IDB_BITMAP1);
	//获取对话框上的句柄 图片控件ID
	CStatic *p = (CStatic *)GetDlgItem(IDC_STATIC_PIC);
	//设置静态控件窗口风格为位图居中显示
	p->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
	//将图片设置到Picture控件上
	p->SetBitmap(bitmap);
}


void CDSOSampleDlg::OnBnClickedButtonAbout()
{
	// TODO: Add your control notification handler code here
	CAboutDlg AboutDlg;
	AboutDlg.DoModal();

}
