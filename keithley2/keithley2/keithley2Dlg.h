// keithley2Dlg.h : ͷ�ļ�
//

#pragma once


// Ckeithley2Dlg �Ի���
class Ckeithley2Dlg : public CDialog
{
	// ����
public:
	Ckeithley2Dlg(CWnd* pParent = NULL);	// ��׼���캯��

	// �Ի�������
	enum { IDD = IDD_KEITHLEY2_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	// ʵ��
protected:
	HICON m_hIcon;
	CString time_str;
	CString time_limit_str;
	CString v_set_str;

	int time_limit;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	CTime time;
	bool operation_flag;
	CString StrFileName;
	int v_set;
	CStdioFile f_out;
	char *gnu_plot_filename;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEdit1();
	void OnTimer(UINT);
	afx_msg void OnEnChangeEdit2();
};
