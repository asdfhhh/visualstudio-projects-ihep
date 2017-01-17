
// DSO-SampleDlg.h : header file
//

#pragma once
#include "Hard.h"
#include <iostream>
#include <fstream>
#include "Viewer.h"
#include "DrawGraph.h"

using namespace std;
// CDSOSampleDlg dialog
class CDSOSampleDlg : public CDialogEx
{
// Construction
public:
	CDSOSampleDlg(CWnd* pParent = NULL);	// standard constructor
	//CHard m_Hard;//this must be replace by a pointer, or will lead a stack overflow error in TFile.
	CHard *m_Hard;
	Viewer *rootv;
	DrawGraph*gf;
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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CComboBox	m_cboChVolt;
	CComboBox m_cboChCouple;
	CComboBox m_cboCH;
	CComboBox m_cboTimebase;
	CComboBox m_cboTrigSweep;
	CComboBox m_cboTrigSrc;
	CButton	m_chkChEnable;
	CComboBox m_cboTrigSlope;
	CComboBox m_cboTrigCouple;
	bool runflag;
	virtual BOOL DestroyWindow();
	afx_msg void OnCbnSelchangeVDiv();
	void InitControls();
	afx_msg void OnCbnSelchangeVCouple();
	void UpdateCtrls();
	afx_msg void OnBnClickedChOn();
	afx_msg void OnCbnSelchangeVCh();
	afx_msg void OnCbnSelchangeTDiv();
	afx_msg void OnCbnSelchangeTriSweep();
	afx_msg void OnCbnSelchangeTriSource();
	afx_msg void OnCbnSelchangeTriSlope();
	afx_msg void OnCbnSelchangeTriCouple();
};
