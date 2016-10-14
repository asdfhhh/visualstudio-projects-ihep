// VCDlg.h : header file
//

#if !defined(AFX_VCDLG_H__014D95D6_1012_4E86_8C81_31B7225A7D23__INCLUDED_)
#define AFX_VCDLG_H__014D95D6_1012_4E86_8C81_31B7225A7D23__INCLUDED_

#include "Hard.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define MCA_CH 256
#include "Hard.h"
#include <iostream>
#include <fstream>
using namespace std;


/////////////////////////////////////////////////////////////////////////////
// CVCDlg dialog

class CVCDlg : public CDialog
{
//Attributes
public:
	CHard m_Hard;
	BOOL m_bRunStop;	//TRUE:Run  FALSE:Stop

	//Memory Drawing
	CRect m_rcMemory;
	CDC m_dcMemory;	
	CBitmap m_bmpMemory;

//Operations
public:
	void InitHardDevice();
	void InitVariables();
	void InitControls();
	void UpdateCtrls();
	
	//Drawing
	void DrawWave(CDC* pDC,CRect Rect);
	void DrawWaveInYT(CDC* pDC,CRect Rect,USHORT nCH);
	void CreateMemoryDC(CDC *pDC, CRect Rect);

// Construction
	CVCDlg(CWnd* pParent = NULL);	// standard constructor
public:
// Dialog Data
	//{{AFX_DATA(CVCDlg)
	enum { IDD = IDD_VC_DIALOG };
	CEdit	m_editTrigLevel;
	CEdit	m_editChLevel;
	CComboBox	m_cboTrigSweep;
	CComboBox	m_cboTrigCouple;
	CComboBox	m_cboTrigSlope;
	CComboBox	m_cboTrigSrc;
	CButton	m_btnRunStop;
	CComboBox	m_cboChVolt;
	CComboBox	m_cboChCouple;
	CButton	m_chkChEnable;
	CComboBox	m_cboCH;
	CComboBox	m_cboTimebase;
	CStatic	m_MainPanel;
	//}}AFX_DATA
	int mca[MCA_CH];
	ofstream f_out;
	bool mca_flag;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVCDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CVCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeCboTimebase();
	afx_msg void OnSelchangeCboCh();
	afx_msg void OnSelchangeCboChCouple();
	afx_msg void OnSelchangeCboChVolt();
	afx_msg void OnBtnRunStop();
	afx_msg void OnChkChEnable();
	afx_msg void OnSelchangeCboTrigSrc();
	afx_msg void OnSelchangeCboTrigSlope();
	afx_msg void OnSelchangeCboTrigCouple();
	afx_msg void OnSelchangeCboTrigSweep();
	afx_msg void OnKillfocusEditChLevel();
	afx_msg void OnKillfocusEditTrigLevel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCDLG_H__014D95D6_1012_4E86_8C81_31B7225A7D23__INCLUDED_)
