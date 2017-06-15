// keithley1Dlg.h : 头文件
//

#pragma once

class Ckeithley1DlgAutoProxy;


// Ckeithley1Dlg 对话框
class Ckeithley1Dlg : public CDialog
{
	DECLARE_DYNAMIC(Ckeithley1Dlg);
	friend class Ckeithley1DlgAutoProxy;

// 构造
public:
	Ckeithley1Dlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~Ckeithley1Dlg();
	CFile f_out;
	CString StrFileName;
	int m_waittime;
	int m_maxvoltage;
	int m_stepvoltage;
	bool operation_flag;
	CListBox *pCtrl ;
	CWinThread* m_ThreadOne;


// 对话框数据
	enum { IDD = IDD_KEITHLEY1_DIALOG };
	CString	m_str_read;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	Ckeithley1DlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnLbnSelchangeList1();
public:
	afx_msg void OnCbnSelchangeCombo2();
public:
	afx_msg void OnBnClickedAbout();
	afx_msg void OnBnClickedCheck1();
	bool ZRC_flag;
};
