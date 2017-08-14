
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
#include "Processing.h"
#include <random>
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
	TTree*output;
	float baseline[64];
	float ped_data[128];
	float peak[64];
	int ptime[64];
	float rtime[64];
	int det_ch;
	Viewer*view;
	CString s_X_F_th;
	CString s_X_S_th;
	CString s_Y_F_th;
	CString s_Y_S_th;
	CString s_T_th;
	CString s_NSample;
	CString s_R_ch;

	CButton	m_chkChEnable;
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
	CProgressCtrl* m_Progress;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	int RootProcessing();
	TH1F *h1;
	TH2F *h2;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
//	afx_msg void OnChangeEdit2();
	afx_msg void OnBnClickedButton7();
	int PedProcessing();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnBnClickedCheck1();
};
