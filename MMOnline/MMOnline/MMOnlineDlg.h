
// MMOnlineDlg.h : ͷ�ļ�
//

#pragma once
#include "TFile.h"
#include <fstream>
#include "TTree.h"
#include <iostream>     // std::cout
#include "afxcmn.h"
#include "TH1F.h"
#include "Viewer.h"
using namespace std;
// CMMOnlineDlg �Ի���
class CMMOnlineDlg : public CDialogEx
{
// ����
public:
	CMMOnlineDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MMONLINE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CString m_FilePath;
	CString m_FileExt;
	TFile *root_file;
	TTree*t;
	float baseline[64];
	float peak[64];
	int ptime[64];
	float rtime[64];
	int det_ch;
	Viewer*view;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	// ����RAW�ĳ���
	int RawDataProcess();
//	afx_msg void OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult);
	CProgressCtrl m_Progress;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	int RootProcessing();
};
