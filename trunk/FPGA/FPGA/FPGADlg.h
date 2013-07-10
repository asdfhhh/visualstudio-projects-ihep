// FPGADlg.h : ͷ�ļ�
//

#pragma once


// CFPGADlg �Ի���
class CFPGADlg : public CDialog
{
	// ����
public:
	CFPGADlg(CWnd* pParent = NULL);	// ��׼���캯��

	// �Ի�������
	enum { IDD = IDD_FPGA_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString StrFileName;
	CFile f_out;
	CFile f_in;
	CProgressCtrl	m_Progress;
	unsigned int bit_data[14336];

	afx_msg void OnBnClickedOk();
	afx_msg void OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult);
};
