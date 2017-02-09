#pragma once
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
// DAQ_Viewer dialog

class DAQ_Viewer : public CDialogEx
{
	DECLARE_DYNAMIC(DAQ_Viewer)

public:
	DAQ_Viewer(CWnd* pParent = NULL);   // standard constructor
	virtual ~DAQ_Viewer();
	TCanvas * daq_canvas;
	TH1F*drawing;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DAQ };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	virtual BOOL OnInitDialog();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	int Drawing();
	TH1F* mca;
	TH1F* risingtime_hist;
	TH2F* scatter;
	int Reset();

	void SetHist(TH1F*drawing_d, TH1F* mca_d,TH1F* risingtime_hist_d,TH2F* scatter_d)
	{
		drawing = drawing_d;
		mca = mca_d;
		risingtime_hist = risingtime_hist_d;
		scatter = scatter_d;
	}
};
