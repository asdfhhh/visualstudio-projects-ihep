
// RMDlg.h : 头文件
//

#pragma once
#include "mwpcANA.h"
#include "Processing.h"

// CRMDlg 对话框
class CRMDlg : public CDialogEx
{
// 构造
public:
	CRMDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RM_DIALOG };
#endif

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
	afx_msg void OnBnClickedButton1();
private:
	CString base_FilePath;
	CString m_FileExt;
	CArray<CString, CString> m_FilePath;
	int FileNum;
	MWPCANA *pMWPC;
	CProgressCtrl* m_Progress;
	enum PARLIST{ SLICESIZE=0, SIGNALSIZE ,XCHANNELNUM ,YCHANNELNUM ,QMIN ,QMAX ,MATCHWINDOW ,STRIPGAP  ,TOFRANGE1 ,TOFRANGE2 ,WIDELIMITX ,WIDELIMITY  ,QSUMX ,QSUMY ,FASTMATCH1,FASTMATCH2};
public:
	int NameProcessing();
	afx_msg void OnBnClickedOk();
	
	// //update the parameters painting
	void ShowParameter();
protected:
	// //parameters showing string
	CString ParaShow;
public:
//	afx_msg void OnEditchangeCombo1();
protected:
	int m_paralist;
public:
	CString m_value;
//	afx_msg void OnChangeEdit1();
	afx_msg void OnBnClickedButton2();
	// //the string to output
	CString m_output;
protected:
	CListBox *pCtrl;
public:
	afx_msg void OnBnClickedCancel();
};
