
// USBtestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "USBtest.h"
#include "USBtestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUSBtestDlg dialog



CUSBtestDlg::CUSBtestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_USBTEST_DIALOG, pParent)
	, s_Th(_T("200"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUSBtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, s_Th);
}

BEGIN_MESSAGE_MAP(CUSBtestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CUSBtestDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CUSBtestDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CUSBtestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUSBtestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDCANCEL, &CUSBtestDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CUSBtestDlg message handlers

BOOL CUSBtestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_selectedUSBDevice = new CCyUSBDevice(this->m_hWnd, CYUSBDRV_GUID, true);
	int  nDeviceCount = m_selectedUSBDevice->DeviceCount();


	for (int nIdx = 0; nIdx < m_selectedUSBDevice->DeviceCount(); nIdx++)
	{
		CString strDeviceData;
		m_selectedUSBDevice->Open(nIdx);
		strDeviceData.Format(L"(0x%04X - 0x%04X) %s", m_selectedUSBDevice->VendorID, m_selectedUSBDevice->ProductID, CString(m_selectedUSBDevice->FriendlyName));
		//AfxMessageBox(strDeviceData);
	}
	//DeviceIoControl(
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUSBtestDlg::OnPaint()
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
	GetDlgItem(IDC_BUTTON1)->EnableWindow(0);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUSBtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



// Get USB port Informations
int CUSBtestDlg::FindEndPoint()
{
	int nDeviceIndex = 0;
	// Is there any FX device connected to system?
	//if ((nDeviceIndex = m_cboDevices.GetCurSel()) == -1 || m_selectedUSBDevice == NULL) return FALSE;
	inEpAddress = 0x0;
	outEpAddress = 0x0;
	// There are devices connected in the system.       
	m_selectedUSBDevice->Open(nDeviceIndex);
	int interfaces = this->m_selectedUSBDevice->AltIntfcCount() + 1;
	//m_cboEndpointIN.ResetContent();
	//m_cboEndpointOUT.ResetContent();

	for (int nDeviceInterfaces = 0; nDeviceInterfaces < interfaces; nDeviceInterfaces++)
	{
		m_selectedUSBDevice->SetAltIntfc(nDeviceInterfaces);
		int eptCnt = m_selectedUSBDevice->EndPointCount();

		// Fill the EndPointsBox
		for (int endPoint = 1; endPoint < eptCnt; endPoint++)
		{
			CCyUSBEndPoint *ept = m_selectedUSBDevice->EndPoints[endPoint];

			// INTR, BULK and ISO endpoints are supported.
			if (ept->Attributes == 2)
			{
				CString strData(L""), strTemp;

				strData += ((ept->Attributes == 1) ? L"ISOC " : ((ept->Attributes == 2) ? L"BULK " : L"INTR "));
				strData += (ept->bIn ? L"IN, " : L"OUT, ");
				if (ept->bIn) inEpAddress = ept->Address;
				else outEpAddress = ept->Address;
							}
		}
	}

	epBulkOut = m_selectedUSBDevice->EndPointOf(outEpAddress);
	epBulkIn = m_selectedUSBDevice->EndPointOf(inEpAddress);
	if (epBulkOut == NULL || epBulkIn == NULL) return 0;

	epBulkIn->SetXferSize(IN_SIZE);
	epBulkOut->SetXferSize(CMD_LEN);
	outOvLap.hEvent = CreateEvent(NULL, false, false, L"CYUSB_OUT");
	//epBulkOut->TimeOut = 10;
	int status = Send_USB_CMD(0xAA, 0xEA, 0, 0, 0, 0xCC);

	GetDlgItem(IDOK)->EnableWindow(0);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(1);
	return 1;
}


void CUSBtestDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	FindEndPoint();
	TestUSB();
}


// this is a test function
int CUSBtestDlg::TestUSB()
{
	UpdateData(TRUE);
	UINT32 gate_value = _tstoi(s_Th);
	int i_NSample = _tstoi(s_Th);
	if (i_NSample > 4000)
	{
		AfxMessageBox(_T("Error! Input Number must less than 4000!"));
		s_Th = _T("4000");
		UpdateData(FALSE);
		return 0;
	}
	if (i_NSample < 50)
	{
		AfxMessageBox(_T("Error! Input Number must biger than 50!"));
		s_Th = _T("50");
		UpdateData(FALSE);
		return 0;
	}
	UINT16 value;
	int status;
	if ((gate_value < 4000) && (gate_value >= 0))
	{
		value = gate_value / 4000.0 * 4096;  //convert mV to ADC bin
											 //while (status)
		{
			status = Send_USB_CMD(0xAA, 0xEB, 0, 0, value >> 8, value);
			Sleep(100);
		}
	}
	return 1;
}


int CUSBtestDlg::Send_USB_CMD(BYTE cmd5, BYTE cmd4, BYTE cmd3, BYTE cmd2, BYTE cmd1, BYTE cmd0)
{
	outBuffer[1] = cmd5;
	outBuffer[0] = cmd4;
	outBuffer[3] = cmd3;
	outBuffer[2] = cmd2;
	outBuffer[5] = cmd1;
	outBuffer[4] = cmd0;
	LONG outBytes = CMD_LEN;
	// Just to be cute, request the return data before initiating the loopback
	UCHAR *outContext = epBulkOut->BeginDataXfer(outBuffer, outBytes,
		&outOvLap);
	epBulkOut->WaitForXfer(&outOvLap, 100);
	epBulkOut->FinishDataXfer(outBuffer, outBytes, &outOvLap, outContext);

	return outBytes;
}


void CUSBtestDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	return;
}


void CUSBtestDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	TestUSB();
}


void CUSBtestDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON2)->EnableWindow(0);
	inOvLap.hEvent = CreateEvent(NULL, false, false, L"CYUSB_IN");

	LONG inlength = 0;
	memset(inBuffer, 0, inlength);
	FILE *fp_save;
	fp_save = fopen("test.dat", "wb");
	int status = 0;
	if (!fp_save)
	{
		AfxMessageBox(_T("Error! Can not Open File!"));
		return;
	}
	//asynchronous trancefer
	// Just to be cute, request the return data before initiating the loopback
	while(!inlength)
	{
		inlength = IN_SIZE;
		UCHAR *inContext = epBulkIn->BeginDataXfer(inBuffer, inlength, &inOvLap);
		epBulkIn->WaitForXfer(&inOvLap, 100);
		epBulkIn->FinishDataXfer(inBuffer, inlength, &inOvLap, inContext);
	}
	fwrite(inBuffer, inlength, 8, fp_save);   //数据缓存
	fclose(fp_save);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(1);
	CloseHandle(inOvLap.hEvent);

	return;
}

//处理一个数据包
//type=0xA0表示不输出文件&第一个包，type=0xA1表示不输出文件&非第一个包
//type=0xB0表示输出文件&第一个包，type=0xB1表示输出文件&非第一个包
UINT8 find_head = 0;
UINT64 last_time_code_1s = 0;
UINT32 event_count_1s = 0;
char s_buf[100];
void CUSBtestDlg::process_one_packet(unsigned char *p_buf, unsigned int length, unsigned char type)
{
	int i;
	UINT64 *p_data;
	UINT64 time_code;
	UINT32 bin_index;
	UINT32*p_spec_buf = (UINT32*)malloc(sizeof(UINT32)*2048);
	memset((void*)p_spec_buf, 0, sizeof(UINT32)*2048);
	p_data = (UINT64*)p_buf;

	if ((type & 0x0f) == 0) //是第一个包，所以需要找头
		find_head = 0;

	for (i = 0; i<length / 8; i++) //遍历文件
	{
		if ((find_head == 0) && (p_data[i] == 0xAA55AA55AA55AA55)) //如果还没找到头，那么尝试寻找到正确的头!
		{
			find_head = 1;
			continue;
		}

		if (find_head == 0)  //仍然还没找到头
			continue;

		bin_index = (p_data[i] & 0x0000000000000fff) >> 1; //11-bit ADC
		if (bin_index<0x7ff)
			p_spec_buf[bin_index]++;
		time_code = (p_data[i] >> 16) & 0x00ffffffffff; // 50 ns unit   

		if (type == 0xB1)  //离线模式，产生时间数据
			//fprintf(fp_event, "%lld\t\t%d\n", time_code * 50, bin_index); //输出数据到文件夹中(严重影响采集计数率，建议离线处理!) 

		event_count_1s++;
		if (last_time_code_1s == 0)
		{
			last_time_code_1s = time_code;
			event_count_1s = 0;
		}
		else if (time_code >= last_time_code_1s + 20000000) //新的1s到来，绘制秒的计数
		{
			last_time_code_1s = time_code;
			//PlotStripChartPoint(panelHandle, PANEL_STRIPCHART, event_count_1s);  //绘制chart
			sprintf(s_buf, "%d", event_count_1s);
			//SetCtrlVal(panelHandle, PANEL_IDC_TEXT_EVENTRATE, s_buf);
			event_count_1s = 0;
		}
	}
	Sleep(10);
	return;
	//删除旧图,绘制新图   
	//DeleteGraphPlot(panelHandle, PANEL_GRAPH, -1, VAL_IMMEDIATE_DRAW);
	//PlotY(panelHandle, PANEL_GRAPH, p_spec_buf, ENG_CHN_NUM, VAL_UNSIGNED_INTEGER, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_RED);
}

void CUSBtestDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CloseHandle(outOvLap.hEvent);
	CDialogEx::OnCancel();
}
