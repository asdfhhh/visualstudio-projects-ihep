
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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUSBtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUSBtestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CUSBtestDlg::OnBnClickedOk)
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
		AfxMessageBox(strDeviceData);
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
				else outEpAddress= ept->Address;
				//strTemp.Format(L"%d  Bytes,", ept->MaxPktSize);
				//strData += strTemp;
				//
				//if(m_selectedUSBDevice->BcdUSB == USB30)
				//{
				//    strTemp.Format(L"%d  MaxBurst,", ept->ssmaxburst);
				//    strData += strTemp;
				//}

				strTemp.Format(L"AltInt - %d and EpAddr - 0x%02X", nDeviceInterfaces, ept->Address);
				strData += strTemp;
				AfxMessageBox(strData);
				//if (ept->bIn) this->m_cboEndpointIN.AddString(strData);
				//else this->m_cboEndpointOUT.AddString(strData);
			}
		}
	}

	//if (m_cboEndpointOUT.GetCount() > 0) m_cboEndpointOUT.SetCurSel(0);
	//if (m_cboEndpointIN.GetCount() > 0) m_cboEndpointIN.SetCurSel(0);

	//this->m_btnStart.EnableWindow((m_cboEndpointIN.GetCount() > 0 && m_cboEndpointIN.GetCount() > 0));

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
	epBulkOut = m_selectedUSBDevice->EndPointOf(outEpAddress);
	epBulkIn = m_selectedUSBDevice->EndPointOf(inEpAddress);
	if (epBulkOut == NULL || epBulkIn == NULL) return 0;

	epBulkIn->SetXferSize(IN_SIZE);
	epBulkOut->SetXferSize(CMD_LEN);
	LONG inlength = IN_SIZE;
	epBulkOut->TimeOut = 10;
	int status=Send_USB_CMD(0xAA, 0xEA, 0, 0, 0, 0xCC);
	/*UINT32 gate_value=1;
	UINT16 value;
	if ((gate_value<4000) && (gate_value >= 0))
	{
		value = gate_value / 4000.0 * 4096;  //convert mV to ADC bin
		status=Send_USB_CMD(0xAA, 0xEB, 0, 0, value >> 8, value);
	}*/
	memset(inBuffer, 0, inlength);
	while(!status)status=epBulkIn->XferData(inBuffer, inlength);
	CString strError;
	strError.Format(L"Error code: %d\r\n", epBulkIn->LastError);	// This example assumes that the device automatically sends back,
	// over its bulk-IN endpoint, any bytes that were received over its
	// bulk-OUT endpoint (commonly referred to as a loopback function)
	/*
	OVERLAPPED outOvLap, inOvLap;
	outOvLap.hEvent = CreateEvent(NULL, false, false, L"CYUSB_OUT");
	inOvLap.hEvent = CreateEvent(NULL, false, false, L"CYUSB_IN");
	unsigned char inBuf[128];
	ZeroMemory(inBuf, 128);
	unsigned char buffer[128];
	LONG length = 128;
	// Just to be cute, request the return data before initiating the loopback
	UCHAR *inContext = m_selectedUSBDevice->BulkInEndPt->BeginDataXfer(inBuf, length, &inOvLap);
	UCHAR *outContext = m_selectedUSBDevice->BulkOutEndPt->BeginDataXfer(buffer, length,
		&outOvLap);
	m_selectedUSBDevice->BulkOutEndPt->WaitForXfer(&outOvLap, 100);
	m_selectedUSBDevice->BulkInEndPt->WaitForXfer(&inOvLap, 100);
	m_selectedUSBDevice->BulkOutEndPt->FinishDataXfer(buffer, length, &outOvLap, outContext);
	m_selectedUSBDevice->BulkInEndPt->FinishDataXfer(inBuf, length, &inOvLap, inContext);
	CloseHandle(outOvLap.hEvent);
	CloseHandle(inOvLap.hEvent);
*/
	/*Send_USB_CMD(0xAA, 0xEA, 0, 0, 0, 0xCC);//EA AA 00 00 CC 00
	int gate_value = 200;
	int value;
	char buf[100];
	sscanf(buf, "%d", &gate_value);
	if ((gate_value < 4000) && (gate_value >= 50))
	{
		value = gate_value / 4000.0 * 4096;  //convert mV to ADC bin
		Send_USB_CMD(0xAA, 0xEB, 0, 0, value >> 8, value);
	}
	else
		printf("Set gate_value [%d] error!\n", gate_value);*/
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
	return epBulkOut->XferData(outBuffer, outBytes);

	/*outBulkControl.pipeNum = 0; //EP2 OUT

	if (!m_selectedUSBDevice)
	{
		printf("Send_USB_CMD Error : hDevice=NULL!\n");
		return;
	}
	int status = DeviceIoControl(
		hDevice,
		IOCTL_EZUSB_BULK_WRITE,
		&outBulkControl,
		sizeof(BULK_TRANSFER_CONTROL),
		outBuffer,
		outBytes,
		&nBytes,
		NULL);
		
	if (status)
		printf("Send USB CMD %d Bytes: 0x%02X 0x%02X  0x%02X 0x%02X  0x%02X 0x%02X\n", nBytes, outBuffer[1], outBuffer[0], outBuffer[3], outBuffer[2], outBuffer[5], outBuffer[4]);
	else
		printf("Send_USB_CMD Error, Return Status!=0 !\n");*/
}
