#pragma once


// viewer �Ի���

class viewer : public CDialogEx
{
	DECLARE_DYNAMIC(viewer)

public:
	CWnd* pParent=NULL;
	viewer(CWnd* );   // ��׼���캯��
	virtual ~viewer();
	TH1F*h;
// �Ի�������
	enum { IDD = IDD_DIALOG1 };
	inline void SetHist(TH1F*hist) { h = hist; };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	TCanvas * fCanvas;
	virtual BOOL OnInitDialog();
	//afx_msg void OnPaint();
	afx_msg void OnTimer(UINT);
	DECLARE_MESSAGE_MAP()
public:
	BOOL Create();
};
