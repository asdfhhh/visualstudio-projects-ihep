
// USBtestDlg.h : header file
//

#pragma once
#include "CyAPI.h"
#include "afxwin.h"
#define CMD_LEN 6 
#define IN_SIZE 1024 

// CUSBtestDlg dialog
class CUSBtestDlg : public CDialogEx
{
// Construction
public:
	CUSBtestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USBTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	//below is USB code
	CCyUSBDevice	*m_selectedUSBDevice;
	unsigned char outBuffer[CMD_LEN];  //用于发送命令
	unsigned char inBuffer[IN_SIZE]; //用于接收数据的缓存 
	ULONG outBytes, inBytes;
	BYTE inEpAddress, outEpAddress;
	CCyUSBEndPoint *epBulkOut;
	CCyUSBEndPoint *epBulkIn;
	OVERLAPPED outOvLap, inOvLap;
	ULONG nBytes;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// Get USB port Informations
	int FindEndPoint();
	afx_msg void OnBnClickedOk();
	// this is a test function
	int TestUSB();
	int Send_USB_CMD(BYTE cmd5, BYTE cmd4, BYTE cmd3, BYTE cmd2, BYTE cmd1, BYTE cmd0);
	afx_msg void OnEnChangeEdit1();
	void process_one_packet(unsigned char *p_buf, unsigned int length, unsigned char type);
	CString s_Th;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedCancel();
};
