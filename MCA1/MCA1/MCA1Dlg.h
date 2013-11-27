// MCA1Dlg.h : 头文件
//

#pragma once
#include "PmcaCom.h"
#include "PmcaErr.h"
#include "IEEE-C.H"
#define MAX_MEMORY 32768
#define ADC_GAIN 2048

// CMCA1Dlg 对话框
class CMCA1Dlg : public CDialog
{
	// 构造
public:
	CMCA1Dlg(CWnd* pParent = NULL);	// 标准构造函数

	// 对话框数据
	enum { IDD = IDD_MCA1_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	// 实现
protected:
	HICON m_hIcon;
	CString time_str;
	CString time_limit_str;
	CString v_set_str;

	float time_limit;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTime time;
	void OnTimer(UINT);

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();
	bool operation_flag;
	CString StrFileName;
	int v_set;
	CStdioFile f_out;
	char *gnu_plot_filename;
	unsigned long rate;
	int g_port;
	int g_baudRate;
	int g_gain;
	int g_scale;
	PmcaDeviceType g_device;
	PmcaFlagsType g_flags;
	PmcaStatusType g_status;
	char chBuff[32];
	unsigned long *buff;
	int maxGroup;

};
