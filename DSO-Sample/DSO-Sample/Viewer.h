#pragma once
#include "TCanvas.h"
#include "TStyle.h"
#include "TMultiGraph.h"
#include "TGraph.h"
#include "TLine.h"
// Viewer dialog

class Viewer : public CDialogEx
{
	DECLARE_DYNAMIC(Viewer)

public:
	Viewer(CWnd* pParent = NULL);   // standard constructor
	virtual ~Viewer();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
//	afx_msg void OnTimer(UINT);
	TCanvas * viewer_canvas;
	TMultiGraph*drawing;
	TLine*trigger;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	virtual BOOL OnInitDialog();
	inline void GetGraph(TMultiGraph* s_wave) {
		drawing = s_wave;
	};
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	bool MakeTriLine(int Ch_n, double level);
	void Drawing();
};
