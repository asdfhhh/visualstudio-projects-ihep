
// MFCApplication_rootDlg.h : ͷ�ļ�
//
#pragma once
#include "viewer.h"
#include "MakeNTuple.h"
// CMFCApplication_rootDlg �Ի���
class CMFCApplication_rootDlg : public CDialogEx
{
// ����
public:
	CMFCApplication_rootDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCAPPLICATION_ROOT_DIALOG };
	viewer *rootv;
	MakeNTuple *Ntuple;
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
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
