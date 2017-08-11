#pragma once
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TSystem.h"
// Viewer �Ի���

class Viewer : public CDialogEx
{
	DECLARE_DYNAMIC(Viewer)

public:
	Viewer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Viewer();
	TCanvas * daq_canvas;
	TH1F*drawing1;
	TH2F*drawing2;
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	virtual BOOL OnInitDialog();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	int FillHist(TH1F*);
	int FillHist(TH2F*);
	int UpdateViewer();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void OnRefreshTimer();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};
