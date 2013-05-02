// keithley2Dlg.h : 头文件
//

#pragma once


// Ckeithley2Dlg 对话框
class Ckeithley2Dlg : public CDialog
{
	// 构造
public:
	Ckeithley2Dlg(CWnd* pParent = NULL);	// 标准构造函数

	// 对话框数据
	enum { IDD = IDD_KEITHLEY2_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	// 实现
protected:
	HICON m_hIcon;
	CString time_str;
	CString time_limit_str;
	CString v_set_str;

	int time_limit;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	CTime time;
	bool operation_flag;
	CString StrFileName;
	int v_set;
	CStdioFile f_out;
	char *gnu_plot_filename;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEdit1();
	void OnTimer(UINT);
	afx_msg void OnEnChangeEdit2();
};
