
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
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDSOSampleDlg dialog



CDSOSampleDlg::CDSOSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DSOSAMPLE_DIALOG, pParent)
	, runflag(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	rootv = new Viewer(this);
	m_Hard = new CHard();
	gf = new DrawGraph();
}

void CDSOSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDSOSampleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDSOSampleDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDSOSampleDlg::OnBnClickedCancel)
	ON_WM_TIMER()
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
	SetTimer(1, 1, NULL);//set the data collection timer
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
		rootv->Create(MAKEINTRESOURCE(IDD_DIALOG1),this);
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
	if (runflag)
	{
		m_Hard->CollectData();
		if (m_Hard->m_nCollectState == 7 && m_Hard->m_nReadOK == 1)
		{
			int nBin = m_Hard->m_stControl.nReadDataLen;
			double* t_axis = new double[nBin];
			double* v_axis = new double[nBin];
			for (int i = 0; i < m_Hard->m_stControl.nReadDataLen; i++)
			{
				short adc = m_Hard->m_CH[0].m_pSrcData[i];
				t_axis[i] = i;
				v_axis[i] = adc;
			}
			gf->SetTGraph(nBin, t_axis, v_axis);
			rootv->GetGraph(gf->MakeTGraph());
		}
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
