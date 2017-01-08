
// DSO-SampleDlg.h : header file
//

#pragma once
#include "Hard.h"
#include <iostream>
#include <fstream>
#include "Viewer.h"

using namespace std;
// CDSOSampleDlg dialog
class CDSOSampleDlg : public CDialogEx
{
// Construction
public:
	CDSOSampleDlg(CWnd* pParent = NULL);	// standard constructor
	CHard m_Hard;
	Viewer *rootv;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DSOSAMPLE_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// initial the DSO hardware
	bool InitHardDevice();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
