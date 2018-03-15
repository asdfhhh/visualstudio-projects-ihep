
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
#include "TROOT.h"
#include "Processing.h"
#include <random>

#define ASIC_CH 128
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
	CString m_FileExt;
	CArray<CString, CString> m_FilePath;
	CString base_FilePath;
	int FileNum;
	TFile *root_file;
	TTree*t;
	TTree*output;
	float baseline[ASIC_CH];
	float ped_data[ASIC_CH];
	float peak[ASIC_CH];
	int ptime[ASIC_CH];
	float rtime[ASIC_CH];
	Viewer*view;
	CString s_X_F_th;
	CString s_X_S_th;
	CString s_Y_F_th;
	CString s_Y_S_th;
	CString s_T_th;
	CString s_NSample;
	CString s_R_ch;
	CString cmd_test;
	CString cut_test;

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
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
};
