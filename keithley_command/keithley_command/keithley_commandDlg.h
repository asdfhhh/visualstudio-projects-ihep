// keithley_commandDlg.h : ͷ�ļ�
//

#pragma once


// Ckeithley_commandDlg �Ի���
class Ckeithley_commandDlg : public CDialog
{
// ����
public:
	Ckeithley_commandDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_KEITHLEY_COMMAND_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CString command_str;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
