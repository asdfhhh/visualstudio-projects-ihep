// keithley1Dlg.h : ͷ�ļ�
//

#pragma once

class Ckeithley1DlgAutoProxy;


// Ckeithley1Dlg �Ի���
class Ckeithley1Dlg : public CDialog
{
	DECLARE_DYNAMIC(Ckeithley1Dlg);
	friend class Ckeithley1DlgAutoProxy;

// ����
public:
	Ckeithley1Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~Ckeithley1Dlg();
	CFile f_out;
	CString StrFileName;
	int m_waittime;
	int m_maxvoltage;
	int m_stepvoltage;
	bool operation_flag;
	CListBox *pCtrl ;
	CWinThread* m_ThreadOne;


// �Ի�������
	enum { IDD = IDD_KEITHLEY1_DIALOG };
	CString	m_str_read;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	Ckeithley1DlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// ���ɵ���Ϣӳ�亯��
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
