#pragma once
#include "TCanvas.h"
#include "TH1F.h"

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
	int MakeGraph(int nBin, double* Data);
};
