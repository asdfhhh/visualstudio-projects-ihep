
// RMDlg.h : ͷ�ļ�
//

#pragma once
#include "mwpcANA.h"
#include "Processing.h"

// CRMDlg �Ի���
class CRMDlg : public CDialogEx
{
// ����
public:
	CRMDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
