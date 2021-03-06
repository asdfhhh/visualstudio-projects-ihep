#pragma once
#include "MakeDAQGraph.h"
#include "DataProcessing.h"
// DAQSetup dialog

class DAQSetup : public CDialogEx
{
	DECLARE_DYNAMIC(DAQSetup)

public:
	DAQSetup(CWnd* pParent = NULL);// standard constructor
	virtual ~DAQSetup();
	DAQCTRL DAQ_p;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DAQSetup };
#endif
	CEdit	m_editCutoff;
	CEdit	m_editMcaMax;
	CEdit m_editRTimemax;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnKillfocusEditDaqsetupCutoff();
	afx_msg void OnKillfocusEditDaqsetupMcamax();
	afx_msg void OnKillfocusEditDaqsetupRtimemax();
	virtual BOOL Create(DataProcessing*data,LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	virtual BOOL OnInitDialog();
	CButton	m_chkChEnable;
	CButton m_chkChSave;
	CButton m_chkCh1Rev;
	CButton m_chkCh2Rev;
	DataProcessing*data_p;
	afx_msg void OnBnClickedCheckSave();
	afx_msg void OnBnClickedCheckPsd();
	afx_msg void OnBnClickedCheckRevCh1();
	afx_msg void OnBnClickedCheckRevCh2();
};
