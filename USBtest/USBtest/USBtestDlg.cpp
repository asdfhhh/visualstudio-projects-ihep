
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
	/*BYTE inEpAddress = 0x0, outEpAddress = 0x0;
	CCyUSBEndPoint *epBulkOut = m_selectedUSBDevice->EndPointOf(outEpAddress);
	CCyUSBEndPoint *epBulkIn = m_selectedUSBDevice->EndPointOf(inEpAddress);
	if (epBulkOut == NULL || epBulkIn == NULL) return 0;*/
	
	// This example assumes that the device automatically sends back,
	// over its bulk-IN endpoint, any bytes that were received over its
	// bulk-OUT endpoint (commonly referred to as a loopback function)
	
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
	return 1;
}
