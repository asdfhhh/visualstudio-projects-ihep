#pragma once


// Processing dialog

class Processing : public CDialogEx
{
	DECLARE_DYNAMIC(Processing)

public:
	Processing(CWnd* pParent = NULL);   // standard constructor
	virtual ~Processing();
	CProgressCtrl m_Progress;
	inline CProgressCtrl * GetCP(){return &m_Progress;}
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult);
};
