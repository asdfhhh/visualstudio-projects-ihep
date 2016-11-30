
// USBtestDlg.h : header file
//

#pragma once
#include "CyAPI.h"


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

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
