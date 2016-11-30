
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

