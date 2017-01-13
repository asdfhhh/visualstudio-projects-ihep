#pragma once


// viewer 对话框

class viewer : public CDialogEx
{
	DECLARE_DYNAMIC(viewer)

public:
	CWnd* pParent=NULL;
	viewer(CWnd* );   // 标准构造函数
	virtual ~viewer();
	TH1F*h;
// 对话框数据
	enum { IDD = IDD_DIALOG1 };
	inline void SetHist(TH1F*hist) { h = hist; };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	TCanvas * fCanvas;
	virtual BOOL OnInitDialog();
	//afx_msg void OnPaint();
	afx_msg void OnTimer(UINT);
	DECLARE_MESSAGE_MAP()
public:
	BOOL Create();
};
