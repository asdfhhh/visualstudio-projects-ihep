// MCA1Dlg.h : ͷ�ļ�
//

#pragma once
#include "PmcaCom.h"
#include "PmcaErr.h"
#include "IEEE-C.H"
#define MAX_MEMORY 32768
#define ADC_GAIN 2048

// CMCA1Dlg �Ի���
class CMCA1Dlg : public CDialog
{
	// ����
public:
	CMCA1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

	// �Ի�������
	enum { IDD = IDD_MCA1_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	// ʵ��
protected:
	HICON m_hIcon;
	CString time_str;
	CString time_limit_str;
	CString v_set_str;

	float time_limit;

	// ���ɵ���Ϣӳ�亯��
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
