
// MFCApplication_rootDlg.h : 头文件
//
#pragma once
#include "viewer.h"
#include "MakeNTuple.h"
// CMFCApplication_rootDlg 对话框
class CMFCApplication_rootDlg : public CDialogEx
{
// 构造
public:
	CMFCApplication_rootDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCAPPLICATION_ROOT_DIALOG };
	viewer *rootv;
	MakeNTuple *Ntuple;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
