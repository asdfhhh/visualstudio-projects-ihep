
// MMOnlineDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MMOnline.h"
#include "MMOnlineDlg.h"
#include "afxdialogex.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif



// CMMOnlineDlg �Ի���



CMMOnlineDlg::CMMOnlineDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MMONLINE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	view = new Viewer(this);
	t = 0;
	root_file = 0;
}

void CMMOnlineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
}

BEGIN_MESSAGE_MAP(CMMOnlineDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMMOnlineDlg::OnBnClickedButton1)
	//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CMMOnlineDlg::OnNMCustomdrawProgress1)
	ON_BN_CLICKED(IDOK, &CMMOnlineDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMMOnlineDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMMOnlineDlg ��Ϣ�������

BOOL CMMOnlineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMMOnlineDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMMOnlineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMMOnlineDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE,
		_T(".dat"),
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT | OFN_ENABLESIZING,
		_T("RAW DATA (*.dat)|*.dat|ROOT FILES (*.root)|*.root||"),
		NULL);
	if (dlg.DoModal() == IDOK)
	{
		m_FilePath = dlg.GetPathName();////////ȡ���ļ�·�� 
		m_FileExt = dlg.GetFileExt();
		UpdateData(FALSE);
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


// ����RAW�ĳ���
int CMMOnlineDlg::RawDataProcess()
{
	UShort_t adc_data[64][512];
	int Inf_time;
	int tag;

	UShort_t data_bulk[66];
	UShort_t *adc = 0;
	//�����ļ�
	CString tmp_name = m_FilePath;
	char *aux_string = (char*)tmp_name.GetBuffer(0);
	long len = wcslen(tmp_name); //the length of "salut"
	wcstombs(aux_string, tmp_name, len); //conversion to char *	
	aux_string[len] = '\0';	 //don't forget to put the caracter of terminated string

	ifstream f(aux_string, ifstream::binary);
	if (f.is_open())
	{
		t = new TTree("ana", "the results of analysis");
		t->Branch("baseline", baseline, "baseline[64]/F");
		t->Branch("peak", peak, "peak[64]/F");
		t->Branch("ptime", ptime, "ptime[64]/I");
		t->Branch("rtime", rtime, "rtime[64]/F");
		t->Branch("det_ch", &det_ch, "det_ch/I");
		TH1F *h1 = new TH1F("test", "test", 512, 0, 512);

		//TH1F*h1=new TH1F("test","test",512,0,512);
		int count = 0;
		int E_count = 0;
		f.seekg(0, f.end);
		int file_size = f.tellg();
		int process_cur = 0;
		m_Progress.SetRange(0, 100);
		m_Progress.SetPos(0);
		f.seekg(0, f.beg);
		while (!f.eof())
		{
			f.read((char*)&tag, 1);
			process_cur = f.tellg() * 100 / file_size;
			m_Progress.SetPos(process_cur);
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
							}
							else if ((tag & 0xFFFF) == 0xFFBC)
							{
								E_count++;
							}
							else
							{
								if (!f.eof())
								{
									E_count++;
								}
							}
							h1->Reset();
							for (int j = 0; j < 64; j++)
							{
								for (int jj = 0; jj < 512; jj++)
								{
									if (jj == 0)baseline[j] = 0;
									if (jj < 100)baseline[j] += adc_data[j][jj];
									if (jj == 100)baseline[j] = baseline[j] / 100;
									h1->Fill(jj, adc_data[j][jj]);
								}
								ptime[j] = h1->GetMaximumBin();
								peak[j] = h1->GetBinContent(ptime[j]) - baseline[j];
								for (int jj = 0; jj < ptime[j]; jj++)
								{
									rtime[j] = jj;
									if ((h1->GetBinContent(jj) - baseline[j]) > (peak[j] / 10.0))break;
								}
							}
							t->Fill();
						}
					}
				}
			}
		}
		m_FilePath.TrimRight(_T(".dat"));
		m_FilePath += _T(".root");
		aux_string = (char*)m_FilePath.GetBuffer(0);
		len = wcslen(m_FilePath); //the length of "salut"
		wcstombs(aux_string, m_FilePath, len); //conversion to char *	
		aux_string[len] = '\0';	 //don't forget to put the caracter of terminated string	
		root_file = new TFile(aux_string, "RECREATE");
		f.close();
		m_Progress.SetPos(0);
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
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	*pResult = 0;
//}


void CMMOnlineDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	//open ROOT viewer
	if (view->GetSafeHwnd() == NULL)view->Create(MAKEINTRESOURCE(IDD_DIALOG1), this);
	//GetDlgItem(IDC)->SetWindowText(_T("Stop DAQ"));
	view->ShowWindow(SW_SHOW);
	RootProcessing();
}


void CMMOnlineDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(t) t->Write();
	if(root_file)root_file->Close();
	CDialogEx::OnCancel();
}


int CMMOnlineDlg::RootProcessing()
{
	float pos;
	float ene;
	int size_p;

	int total = t->GetEntries();
	t->SetBranchAddress("det_ch", &det_ch);
	t->SetBranchAddress("baseline", &baseline);
	t->SetBranchAddress("peak", &peak);
	t->SetBranchAddress("ptime", &ptime);
	t->SetBranchAddress("rtime", &rtime);
	float F_th = 400;
	float S_th = 200;

	m_Progress.SetRange(0, total);
	m_Progress.SetPos(0);
	m_Progress.SetStep(1);
	for (int i = 1; i <= total; i++)
	{
		t->GetEntry(i);
		m_Progress.StepIt();
		int max_p = 0;
		for (int j = 0; j<64; j++)
		{
			max_p = (peak[max_p]>peak[j]) ? max_p : j;
		}
		if (peak[max_p]>S_th)
		{
			int j = 1;
			size_p = 1;
			ene = peak[max_p];
			pos = ene*max_p;
			while (((max_p - j)>-1) && (peak[max_p - j]>F_th))
			{
				ene += peak[max_p - j];
				pos += peak[max_p - j] * (max_p - j);
				j++;
				size_p++;
			}
			j = 1;
			while (((max_p + j)<64) && (peak[max_p + j]>F_th))
			{
				ene += peak[max_p + j];
				pos += peak[max_p + j] * (max_p + j);
				j++;
				size_p++;
			}
			pos = pos / ene;
		}
		view->FillHist(ene);
	}
	m_Progress.SetPos(0);
	return 0;
}
