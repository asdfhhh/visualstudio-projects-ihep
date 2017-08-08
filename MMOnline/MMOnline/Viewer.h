#pragma once
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"

// Viewer 对话框

class Viewer : public CDialogEx
{
	DECLARE_DYNAMIC(Viewer)

public:
	Viewer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Viewer();
	TCanvas * daq_canvas;
	TH1F*drawing;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	virtual BOOL OnInitDialog();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	int FillHist(float);
	int UpdateViewer();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
