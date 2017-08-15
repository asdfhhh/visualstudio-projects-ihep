
// MMOnlineDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MMOnline.h"
#include "MMOnlineDlg.h"
#include "afxdialogex.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif



// CMMOnlineDlg 对话框



CMMOnlineDlg::CMMOnlineDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MMONLINE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	view = new Viewer(this);
	t = 0;
	root_file = 0;
	h1 = 0;
	h2 = 0;
	output = 0;
	s_X_F_th = _T("200");
	s_X_S_th = _T("400");
	s_Y_F_th = _T("200");
	s_Y_S_th = _T("400");
	s_T_th = _T("0.1");
	s_NSample = _T("100");
	s_R_ch = _T("30");
}

void CMMOnlineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, s_NSample);
	DDX_Text(pDX, IDC_EDIT2, s_X_F_th);
	DDX_Text(pDX, IDC_EDIT3, s_X_S_th);
	DDX_Text(pDX, IDC_EDIT4, s_T_th);
	DDX_Text(pDX, IDC_EDIT5, s_Y_F_th);
	DDX_Text(pDX, IDC_EDIT6, s_Y_S_th);
	DDX_Text(pDX, IDC_EDIT7, s_R_ch);

	DDX_Control(pDX, IDC_CHECK1, m_chkChEnable);

}

BEGIN_MESSAGE_MAP(CMMOnlineDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMMOnlineDlg::OnBnClickedOpenFile)
	//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CMMOnlineDlg::OnNMCustomdrawProgress1)
	ON_BN_CLICKED(IDOK, &CMMOnlineDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMMOnlineDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CMMOnlineDlg::OnBnClickedDrawEX)
	ON_BN_CLICKED(IDC_BUTTON3, &CMMOnlineDlg::OnBnClickedDrawPX)
	ON_BN_CLICKED(IDC_BUTTON4, &CMMOnlineDlg::OnBnClickedDrawSizeX)
	ON_BN_CLICKED(IDC_BUTTON5, &CMMOnlineDlg::OnBnClickedDrawXY)
	ON_BN_CLICKED(IDC_BUTTON10, &CMMOnlineDlg::OnBnClickedDrawEY)
	ON_BN_CLICKED(IDC_BUTTON11, &CMMOnlineDlg::OnBnClickedDrawPY)
	ON_BN_CLICKED(IDC_BUTTON12, &CMMOnlineDlg::OnBnClickedDrawSizeY)
	ON_BN_CLICKED(IDC_BUTTON7, &CMMOnlineDlg::OnBnClickedOpenPed)
	ON_BN_CLICKED(IDC_BUTTON8, &CMMOnlineDlg::OnBnClickedSavePed)
	ON_BN_CLICKED(IDC_BUTTON9, &CMMOnlineDlg::OnBnClickedDrawPed)
	ON_BN_CLICKED(IDC_BUTTON6, &CMMOnlineDlg::OnBnClickedSnapShoot)
	ON_EN_CHANGE(IDC_EDIT1, &CMMOnlineDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT7, &CMMOnlineDlg::OnEnChangeEdit7)
	ON_BN_CLICKED(IDC_CHECK1, &CMMOnlineDlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CMMOnlineDlg 消息处理程序

BOOL CMMOnlineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMMOnlineDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMMOnlineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMMOnlineDlg::OnBnClickedOpenFile()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE,
		_T(".dat"),
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT | OFN_ENABLESIZING,
		_T("RAW DATA (*.dat)|*.dat|ROOT FILES (*.root)|*.root||"),
		NULL);
	if (dlg.DoModal() == IDOK)
	{
		m_FilePath = dlg.GetPathName();////////取出文件路径 
		m_FileExt = dlg.GetFileExt();
		//UpdateData(FALSE);
	}

	if (m_FileExt == _T("dat"))RawDataProcess();
	else if (m_FileExt == _T("root"))
	{
		CString tmp_name = m_FilePath;
		char *aux_string = (char*)tmp_name.GetBuffer(0);
		long len = wcslen(tmp_name); //the length of "salut"
		wcstombs(aux_string, tmp_name, len); //conversion to char *	
		aux_string[len] = '\0';	 //don't forget to put the caracter of terminated string
		root_file = new TFile(aux_string);
		t = (TTree*)root_file->Get("ana");
	}
}


// 处理RAW的程序
int CMMOnlineDlg::RawDataProcess()
{
	UpdateData(TRUE);

	UShort_t adc_data[64][512];
	int Inf_time;
	int tag;
	float f_T_th = _tstof(s_T_th);
	int i_NSample = _tstoi(s_NSample);
	int ext_ped = m_chkChEnable.GetCheck();
	UShort_t data_bulk[66];
	UShort_t *adc = 0;
	//读入文件
	CString tmp_name = m_FilePath;
	char *aux_string = (char*)tmp_name.GetBuffer(0);
	long len = wcslen(tmp_name); //the length of "salut"
	wcstombs(aux_string, tmp_name, len); //conversion to char *	
	aux_string[len] = '\0';	 //don't forget to put the caracter of terminated string

	ifstream f(aux_string, ifstream::binary);
	if (f.is_open())
	{

		Processing *P_GUI = new Processing(this);
		if (P_GUI->GetSafeHwnd() == NULL)P_GUI->Create(MAKEINTRESOURCE(IDD_DIALOG2), this);
		P_GUI->ShowWindow(SW_SHOW);
		m_Progress = P_GUI->GetCP();
		t = new TTree("ana", "the results of analysis");
		t->Branch("baseline", baseline, "baseline[64]/F");
		t->Branch("peak", peak, "peak[64]/F");
		t->Branch("ptime", ptime, "ptime[64]/I");
		t->Branch("rtime", rtime, "rtime[64]/F");
		t->Branch("det_ch", &det_ch, "det_ch/I");

		//TH1F*h1=new TH1F("test","test",512,0,512);
		int count = 0;
		int E_count = 0;
		f.seekg(0, f.end);
		int file_size = f.tellg();
		int process_cur = 0;
		m_Progress->SetRange(0, 100);
		m_Progress->SetPos(0);
		f.seekg(0, f.beg);
		while (!f.eof())
		{
			f.read((char*)&tag, 1);
			process_cur = f.tellg() * 100 / file_size;
			m_Progress->SetPos(process_cur);
			if ((tag & 0xFF) == 0xEE)
			{
				f.read((char*)&tag, 1);
				if ((tag & 0xFF) == 0xEE)
				{
					f.read((char*)&tag, 1);
					if ((tag & 0xFF) == 0xE0)
					{
						f.read((char*)&tag, 1);
						if ((tag & 0xFF) == 0x00)
						{
							f.read((char*)&Inf_time, 4);
							for (int i = 0; i < 512; i++)
							{
								f.read((char*)&data_bulk, 66 * 2);
								for (int ii = 0; ii < 64; ii++)
								{
									adc = data_bulk + ii + 2;
									adc_data[ii][i] = ((*adc << 8) & 0x0f00) + ((*adc >> 8) & 0x00ff);
								}
							}
							det_ch = *data_bulk;

							f.read((char*)&tag, 2);
							if ((tag & 0xFFFF) == 0xFFFF)
							{
								count++;
							}
							else if ((tag & 0xFFFF) == 0xEEEE)
							{
								adc_data[63][511] = adc_data[63][510];
								f.seekg(-2, ios::cur);
								count++;
								E_count++;
								continue;
							}
							else if ((tag & 0xFFFF) == 0xFFBC)
							{
								E_count++;
								continue;
							}
							else
							{
								if (!f.eof())
								{
									E_count++;
									continue;
								}
							}
							//get the information
							for (int j = 0; j < 64; j++)
							{
								if (ext_ped)
								{
									if (det_ch == 208)baseline[j] = ped_data[j];
									else if (det_ch == 704)baseline[j] = ped_data[j + 64];
								}
								else
								{
									baseline[j] = 0;
									for (int jj = 0; jj < i_NSample; jj++)
									{
										baseline[j] += adc_data[j][jj];
									}
									baseline[j] = baseline[j] / i_NSample;
								}
								ptime[j] = 0;
								rtime[j] = 0;
								peak[j] = 0;
								for (int jj = 0; jj < 512; jj++)
								{
									if (peak[j] < (adc_data[j][jj] - baseline[j]))
									{
										peak[j] = adc_data[j][jj] - baseline[j];
										ptime[j] = jj;
									}
								}
								for (int jj = ptime[j]; jj > 0; jj--)
								{
									rtime[j] = jj;
									if ((adc_data[j][jj] - baseline[j]) < (peak[j] * f_T_th))break;
								}
							}
							t->Fill();
						}
					}
				}
			}
		}

		tmp_name = m_FilePath;
		tmp_name.TrimRight(_T(".dat"));
		tmp_name += _T(".root");
		aux_string = (char*)tmp_name.GetBuffer(0);
		len = wcslen(tmp_name); //the length of "salut"
		wcstombs(aux_string, tmp_name, len); //conversion to char *	
		aux_string[len] = '\0';	 //don't forget to put the caracter of terminated string	
		root_file = new TFile(aux_string, "RECREATE");
		f.close();
		P_GUI->DestroyWindow();
		delete P_GUI;
		return 0;
	}
	else
	{
		return -1;
	}

}


//void CMMOnlineDlg::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	*pResult = 0;
//}


void CMMOnlineDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	if (t)
	{
		RootProcessing();
	}
}


void CMMOnlineDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if (t) t->Write();
	if (root_file)root_file->Close();
	CDialogEx::OnCancel();
}


int CMMOnlineDlg::RootProcessing()
{
	UpdateData(TRUE);

	int count = 0;
	float enex = 0;
	float eney = 0;
	int size_px = 0;
	int size_py = 0;
	float posx = 0;
	float posy = 0;

	output = new TTree("output", "the results of analysis");
	output->Branch("posx", &posx, "posx/F");
	output->Branch("posy", &posy, "posy/F");
	output->Branch("enex", &enex, "enex/F");
	output->Branch("eney", &eney, "eney/F");
	output->Branch("size_px", &size_px, "size_px/I");
	output->Branch("size_py", &size_py, "size_py/I");

	int total = t->GetEntries();
	t->SetBranchAddress("det_ch", &det_ch);
	t->SetBranchAddress("baseline", &baseline);
	t->SetBranchAddress("peak", &peak);
	t->SetBranchAddress("ptime", &ptime);
	t->SetBranchAddress("rtime", &rtime);
	int i_X_F_th = _tstoi(s_X_F_th);
	int i_X_S_th = _tstoi(s_X_S_th);
	int i_Y_F_th = _tstoi(s_Y_F_th);
	int i_Y_S_th = _tstoi(s_Y_S_th);

	Processing *P_GUI = new Processing(this);
	if (P_GUI->GetSafeHwnd() == NULL)P_GUI->Create(MAKEINTRESOURCE(IDD_DIALOG2), this);
	P_GUI->ShowWindow(SW_SHOW);
	m_Progress = P_GUI->GetCP();

	m_Progress->SetRange(0, total);
	m_Progress->SetPos(0);
	m_Progress->SetStep(1);
	for (int i = 1; i <= total; i++)
	{
		t->GetEntry(i);
		m_Progress->StepIt();
		int max_p = 0;
		for (int j = 0; j < 64; j++)
		{
			max_p = (peak[max_p] > peak[j]) ? max_p : j;
		}
		if (det_ch == 208)
		{
			if (peak[max_p] > i_X_S_th)
			{
				int j = 1;
				size_px = 1;

				enex = peak[max_p];
				posx = enex*max_p;

				while (((max_p - j) > -1) && (peak[max_p - j] > i_X_F_th))
				{
					enex += peak[max_p - j];
					posx += peak[max_p - j] * (max_p - j);
					j++;
					size_px++;
				}
				j = 1;
				while (((max_p + j) < 64) && (peak[max_p + j] > i_X_F_th))
				{
					enex += peak[max_p + j];
					posx += peak[max_p + j] * (max_p + j);
					j++;
					size_px++;
				}
				posx = posx / enex;
			}
		}
		else if (det_ch == 704)
		{
			if (peak[max_p] > i_Y_S_th)
			{
				int j = 1;
				size_py = 1;

				eney = peak[max_p];
				posy = eney*max_p;

				while (((max_p - j) > -1) && (peak[max_p - j] > i_Y_F_th))
				{
					eney += peak[max_p - j];
					posy += peak[max_p - j] * (max_p - j);
					j++;
					size_py++;
				}
				j = 1;
				while (((max_p + j) < 64) && (peak[max_p + j] > i_Y_F_th))
				{
					eney += peak[max_p + j];
					posy += peak[max_p + j] * (max_p + j);
					j++;
					size_py++;
				}
				posy = posy / eney;
			}
			output->Fill();
			count++;
		}
	}
	P_GUI->DestroyWindow();
	delete P_GUI;

	output->Fill();
	return count;
}


void CMMOnlineDlg::OnBnClickedDrawEX()
{
	// TODO: Add your control notification handler code here
	//energy spectrum
	if (!output)return;
	//open ROOT viewer
	if (view->GetSafeHwnd() == NULL)view->Create(MAKEINTRESOURCE(IDD_DIALOG1), this);
	//GetDlgItem(IDC)->SetWindowText(_T("Stop DAQ"));
	view->ShowWindow(SW_SHOW);
	if (h1)delete h1;
	output->Draw("enex>>h1");
	h1 = (TH1F*)gDirectory->Get("h1");
	view->FillHist(h1);
	view->UpdateViewer();
}


void CMMOnlineDlg::OnBnClickedDrawPX()
{
	// TODO: Add your control notification handler code here
	//X distribution 
	if (!output)return;
	//open ROOT viewer
	if (view->GetSafeHwnd() == NULL)view->Create(MAKEINTRESOURCE(IDD_DIALOG1), this);
	//GetDlgItem(IDC)->SetWindowText(_T("Stop DAQ"));
	view->ShowWindow(SW_SHOW);
	if (h1)delete h1;
	output->Draw("posx>>h1");
	h1 = (TH1F*)gDirectory->Get("h1");
	view->FillHist(h1);
	view->UpdateViewer();
}


void CMMOnlineDlg::OnBnClickedDrawSizeX()
{
	// TODO: Add your control notification handler code here
	//X cluster size distribution
	if (!output)return;
	//open ROOT viewer
	if (view->GetSafeHwnd() == NULL)view->Create(MAKEINTRESOURCE(IDD_DIALOG1), this);
	//GetDlgItem(IDC)->SetWindowText(_T("Stop DAQ"));
	view->ShowWindow(SW_SHOW);
	if (h1)delete h1;
	output->Draw("size_px>>h1");
	h1 = (TH1F*)gDirectory->Get("h1");
	view->FillHist(h1);
	view->UpdateViewer();
}


void CMMOnlineDlg::OnBnClickedDrawXY()
{
	// TODO: Add your control notification handler code here
	//X-Y distribution
	if (!output)return;
	//open ROOT viewer
	if (view->GetSafeHwnd() == NULL)view->Create(MAKEINTRESOURCE(IDD_DIALOG1), this);
	//GetDlgItem(IDC)->SetWindowText(_T("Stop DAQ"));
	view->ShowWindow(SW_SHOW);
	if (h2)delete h2;
	output->Draw("posx:posy>>h2");
	h2 = (TH2F*)gDirectory->Get("h2");
	view->FillHist(h2);
	view->UpdateViewer();
}


void CMMOnlineDlg::OnBnClickedDrawEY()
{
	// TODO: Add your control notification handler code here
	//energy spectrum
	if (!output)return;
	//open ROOT viewer
	if (view->GetSafeHwnd() == NULL)view->Create(MAKEINTRESOURCE(IDD_DIALOG1), this);
	//GetDlgItem(IDC)->SetWindowText(_T("Stop DAQ"));
	view->ShowWindow(SW_SHOW);
	if (h1)delete h1;
	output->Draw("eney>>h1");
	h1 = (TH1F*)gDirectory->Get("h1");
	view->FillHist(h1);
	view->UpdateViewer();
}


void CMMOnlineDlg::OnBnClickedDrawPY()
{
	// TODO: Add your control notification handler code here
	//Y distribution 
	if (!output)return;
	//open ROOT viewer
	if (view->GetSafeHwnd() == NULL)view->Create(MAKEINTRESOURCE(IDD_DIALOG1), this);
	//GetDlgItem(IDC)->SetWindowText(_T("Stop DAQ"));
	view->ShowWindow(SW_SHOW);
	if (h1)delete h1;
	output->Draw("posy>>h1");
	h1 = (TH1F*)gDirectory->Get("h1");
	view->FillHist(h1);
	view->UpdateViewer();
}


void CMMOnlineDlg::OnBnClickedDrawSizeY()
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	//Y cluster size distribution
	if (!output)return;
	//open ROOT viewer
	if (view->GetSafeHwnd() == NULL)view->Create(MAKEINTRESOURCE(IDD_DIALOG1), this);
	//GetDlgItem(IDC)->SetWindowText(_T("Stop DAQ"));
	view->ShowWindow(SW_SHOW);
	if (h1)delete h1;
	output->Draw("size_py>>h1");
	h1 = (TH1F*)gDirectory->Get("h1");
	view->FillHist(h1);
	view->UpdateViewer();
}


//void CMMOnlineDlg::OnChangeEdit2()
//{
//	// TODO:  If this is a RICHEDIT control, the control will not
//	// send this notification unless you override the CDialogEx::OnInitDialog()
//	// function and call CRichEditCtrl().SetEventMask()
//	// with the ENM_CHANGE flag ORed into the mask.
//
//	// TODO:  Add your control notification handler code here
//}


void CMMOnlineDlg::OnBnClickedOpenPed()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE,
		_T(".ped"),
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT | OFN_ENABLESIZING,
		_T("pedestal DATA (*.ped)|*.ped||"),
		NULL);
	if (dlg.DoModal() == IDOK)
	{
		m_FilePath = dlg.GetPathName();////////取出文件路径 
		m_FileExt = dlg.GetFileExt();
		UpdateData(FALSE);
	}
	if (m_FileExt == _T("ped"))PedProcessing();
	else return;
}


int CMMOnlineDlg::PedProcessing()
{
	//读入文件
	CString tmp_name = m_FilePath;
	char *aux_string = (char*)tmp_name.GetBuffer(0);
	long len = wcslen(tmp_name); //the length of "salut"
	wcstombs(aux_string, tmp_name, len); //conversion to char *	
	aux_string[len] = '\0';	 //don't forget to put the caracter of terminated string

	ifstream f(aux_string);
	for (int i = 0; i < 128; i++)
	{
		f >> ped_data[i];
	}
	f.close();
	return 0;
}


void CMMOnlineDlg::OnBnClickedSavePed()
{
	// TODO: Add your control notification handler code here
	if (!root_file)return;
	//写入文件

	CString tmp_name = m_FilePath;
	tmp_name.TrimRight(_T(".dat"));
	tmp_name += _T(".ped");

	char *aux_string = (char*)tmp_name.GetBuffer(0);
	long len = wcslen(tmp_name); //the length of "salut"
	wcstombs(aux_string, tmp_name, len); //conversion to char *	
	aux_string[len] = '\0';	 //don't forget to put the caracter of terminated string

	ofstream f(aux_string);

	int total = t->GetEntries();
	t->SetBranchAddress("baseline", &baseline);
	t->SetBranchAddress("det_ch", &det_ch);

	Processing *P_GUI = new Processing(this);
	if (P_GUI->GetSafeHwnd() == NULL)P_GUI->Create(MAKEINTRESOURCE(IDD_DIALOG2), this);
	P_GUI->ShowWindow(SW_SHOW);
	m_Progress = P_GUI->GetCP();

	m_Progress->SetRange(0, total);
	m_Progress->SetPos(0);
	m_Progress->SetStep(1);
	for (int i = 0; i < 128; i++)ped_data[i] = 0;
	for (int i = 1; i <= total; i++)
	{
		t->GetEntry(i);
		m_Progress->StepIt();
		if (det_ch == 208)
		{
			for (int j = 0; j < 64; j++)
			{
				ped_data[j] += baseline[j];
			}
		}
		else if (det_ch == 704)
		{
			for (int j = 0; j < 64; j++)
			{
				ped_data[j + 64] += baseline[j];
			}
		}
	}
	P_GUI->DestroyWindow();
	delete P_GUI;

	for (int i = 0; i < 128; i++)
	{
		ped_data[i] = ped_data[i] * 2 / total;
		f << ped_data[i] << endl;
	}

	f.close();
}


void CMMOnlineDlg::OnBnClickedDrawPed()
{
	// TODO: Add your control notification handler code here
	//open ROOT viewer
	if (view->GetSafeHwnd() == NULL)view->Create(MAKEINTRESOURCE(IDD_DIALOG1), this);
	//GetDlgItem(IDC)->SetWindowText(_T("Stop DAQ"));
	view->ShowWindow(SW_SHOW);
	if (h1)delete h1;
	h1 = new TH1F("Ped", "Pedestal distribution", 128, 0, 128);
	for (int i = 0; i < 128; i++)h1->Fill(i, ped_data[i]);
	view->FillHist(h1);
	view->UpdateViewer();

}


void CMMOnlineDlg::OnBnClickedSnapShoot()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	UShort_t adc_data[64][512];
	int Inf_time;
	int tag;
	float f_T_th = _tstof(s_T_th);
	int i_NSample = _tstoi(s_NSample);
	int ext_ped = m_chkChEnable.GetCheck();
	UShort_t data_bulk[66];
	UShort_t *adc = 0;
	int i_R_ch = _tstoi(s_R_ch);
	//读入文件
	CString tmp_name = m_FilePath;
	char *aux_string = (char*)tmp_name.GetBuffer(0);
	long len = wcslen(tmp_name); //the length of "salut"
	wcstombs(aux_string, tmp_name, len); //conversion to char *	
	aux_string[len] = '\0';	 //don't forget to put the caracter of terminated string

	ifstream f(aux_string, ifstream::binary);
	if (f.is_open())
	{
		f.seekg(0, f.end);
		int file_size = f.tellg();
		static std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(0, file_size);
		int number = distribution(generator);
		f.seekg(number);
		while (1)
		{
			f.read((char*)&tag, 1);
			if ((tag & 0xFF) == 0xEE)
			{
				f.read((char*)&tag, 1);
				if ((tag & 0xFF) == 0xEE)
				{
					f.read((char*)&tag, 1);
					if ((tag & 0xFF) == 0xE0)
					{
						f.read((char*)&tag, 1);
						if ((tag & 0xFF) == 0x00)
						{
							break;
						}
					}
				}
			}
		}
		f.read((char*)&Inf_time, 4);
		for (int i = 0; i < 512; i++)
		{
			f.read((char*)&data_bulk, 66 * 2);
			for (int ii = 0; ii < 64; ii++)
			{
				adc = data_bulk + ii + 2;
				adc_data[ii][i] = ((*adc << 8) & 0x0f00) + ((*adc >> 8) & 0x00ff);
			}
		}
		if (h1)delete h1;
		h1 = new TH1F("wave", "Signal for random", 512, 0, 512);
		for (int i = 0; i < 512; i++)h1->Fill(i, adc_data[i_R_ch][i]);
		//open ROOT viewer
		if (view->GetSafeHwnd() == NULL)view->Create(MAKEINTRESOURCE(IDD_DIALOG1), this);
		//GetDlgItem(IDC)->SetWindowText(_T("Stop DAQ"));
		view->ShowWindow(SW_SHOW);
		view->FillHist(h1);
		view->UpdateViewer();

		f.close();
		return;
	}
	else
	{
		return;
	}

}


void CMMOnlineDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
	int i_NSample = _tstoi(s_NSample);
	if (i_NSample > 512) 
	{
		AfxMessageBox(_T("Error! Input Number must less than 512!"));
		s_NSample = _T("512");
		UpdateData(FALSE);
		return;
	}
	if (i_NSample < 1)
	{
		AfxMessageBox(_T("Error! Input Number must biger than 0!"));
		s_NSample = _T("1");
		UpdateData(FALSE);
		return;
	}
	return;
}


void CMMOnlineDlg::OnEnChangeEdit7()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
	int i_R_ch = _tstoi(s_R_ch);
	if (i_R_ch > 128)
	{
		AfxMessageBox(_T("Error! Input Number must less than 128!"));
		s_R_ch = _T("127");
		UpdateData(FALSE);
		return;
	}
	if (i_R_ch < 1)
	{
		AfxMessageBox(_T("Error! Input Number must biger than 0!"));
		s_R_ch = _T("0");
		UpdateData(FALSE);
		return;
	}
	return;
}


void CMMOnlineDlg::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int ext_ped = m_chkChEnable.GetCheck();
	if (ext_ped)
	{
		CFileDialog dlg(TRUE,
			_T(".ped"),
			NULL,
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT | OFN_ENABLESIZING,
			_T("pedestal DATA (*.ped)|*.ped||"),
			NULL);
		if (dlg.DoModal() == IDOK)
		{
			m_FilePath = dlg.GetPathName();////////取出文件路径 
			m_FileExt = dlg.GetFileExt();
			UpdateData(FALSE);
		}
		if (!m_FilePath.IsEmpty())
		{
			if (m_FileExt == _T("ped"))PedProcessing();
			else return;
		}
		else
		{
			m_chkChEnable.SetCheck(0);
			UpdateData(FALSE);
			return;
		}
	}
	else return;
}
