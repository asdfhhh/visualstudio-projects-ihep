
// MMOnlineDlg.h : 头文件
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
// CMMOnlineDlg 对话框
class CMMOnlineDlg : public CDialogEx
{
// 构造
public:
	CMMOnlineDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MMONLINE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
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
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenFile();
	// 处理RAW的程序
	int RawDataProcess();
//	afx_msg void OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult);
	CProgressCtrl* m_Progress;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	int RootProcessing();
	TH1F *h1;
	TH2F *h2;
	afx_msg void OnBnClickedDrawEX();
	afx_msg void OnBnClickedDrawPX();
	afx_msg void OnBnClickedDrawSizeX();
	afx_msg void OnBnClickedDrawXY();
	afx_msg void OnBnClickedDrawEY();
	afx_msg void OnBnClickedDrawPY();
	afx_msg void OnBnClickedDrawSizeY();
//	afx_msg void OnChangeEdit2();
	afx_msg void OnBnClickedOpenPed();
	int PedProcessing();
	afx_msg void OnBnClickedSavePed();
	afx_msg void OnBnClickedDrawPed();
	afx_msg void OnBnClickedSnapShoot();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnBnClickedCheck1();
};
