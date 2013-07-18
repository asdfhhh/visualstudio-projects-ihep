// FPGADlg.h : 头文件
//

#pragma once

#define MEM_NUM 22528
// CFPGADlg 对话框
class CFPGADlg : public CDialog
{
	// 构造
public:
	CFPGADlg(CWnd* pParent = NULL);	// 标准构造函数

	// 对话框数据
	enum { IDD = IDD_FPGA_DIALOG };

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
	CString StrFileName;
	CFile f_out;
	CFile f_in;
	CProgressCtrl	m_Progress;
	unsigned int bit_data[MEM_NUM];

	afx_msg void OnBnClickedOk();
	afx_msg void OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult);
};
