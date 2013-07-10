// FPGADlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FPGA.h"
#include "FPGADlg.h"
#include <map>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFPGADlg �Ի���




CFPGADlg::CFPGADlg(CWnd* pParent /*=NULL*/)
: CDialog(CFPGADlg::IDD, pParent)
, StrFileName(_T("test.bin"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFPGADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1,StrFileName);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
}

BEGIN_MESSAGE_MAP(CFPGADlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CFPGADlg::OnBnClickedOk)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CFPGADlg::OnNMCustomdrawProgress1)
END_MESSAGE_MAP()


// CFPGADlg ��Ϣ�������

BOOL CFPGADlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFPGADlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CFPGADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFPGADlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	unsigned int count=0;
	int err=0;
	unsigned long int offset=0;
	char out_char[100];
	CString message;
	if (!f_in.Open(StrFileName,CFile::modeRead|CFile::typeBinary,NULL))
	{
		AfxMessageBox(_T("Invalid File Name!"));
		return;
	}
	long a=f_in.GetLength();
	if(!f_out.Open(_T("output.txt"),CFile::modeCreate|CFile::modeReadWrite,NULL))
	{
		return;
	}
	sprintf(out_char,"Error code:1 upset, 2 length error");
	f_out.Write(out_char,::strlen(out_char));
	f_out.Write("\r\n",2);
	sprintf(out_char,"code\t position\t orignal\t present\t memory");
	f_out.Write(out_char,::strlen(out_char));
	f_out.Write("\r\n",2);

	unsigned int tmp_data;
	m_Progress.SetPos(0);
	m_Progress.SetRange(0,100);
	m_Progress.SetStep(1);
	//initial map
	while(1)
	{
		f_in.Read(&tmp_data,2);
		if((tmp_data&0xfe00)==0xfe00)
		{
			offset=f_in.GetPosition();
			bit_data[count]=tmp_data;
			count++;
			for(;count<14336;count++)
			{
				f_in.Read(&tmp_data,2);
				bit_data[count]=tmp_data;
			}
			break;
		}
	}
	count=0;
	while(f_in.GetPosition()<f_in.GetLength())
	{
		f_in.Read(&tmp_data,2);
		if((f_in.GetPosition()%(f_in.GetLength()/100))==0)
		{
			m_Progress.StepIt();
			//			Sleep(0.1);
		}
		if((tmp_data&0xfe00)==0xfe00)
		{
			if((f_in.GetPosition()-offset)%14336!=0)
			{
				sprintf(out_char,"2\t %d\t ",f_in.GetPosition());
				f_out.Write(out_char,::strlen(out_char));
			}
			count=0;
			if((tmp_data&0x01ff)!=(bit_data[count]&0x01ff))
			{
				err++;
				sprintf(out_char,"1\t %d",f_in.GetPosition());
				f_out.Write(out_char,::strlen(out_char));
				sprintf(out_char,"\t %x\t %x\t %d",bit_data[count],tmp_data,count);
				f_out.Write(out_char,::strlen(out_char));
				f_out.Write("\r\n",2);
			}
			count++;
			f_in.Read(&tmp_data,2);
			if((f_in.GetPosition()%(f_in.GetLength()/100))==0)
			{
				m_Progress.StepIt();
				//			Sleep(0.1);
			}
			if((tmp_data&0x01ff)!=(bit_data[count]&0x01ff))
			{
				err++;
				sprintf(out_char,"1\t %d",f_in.GetPosition());
				f_out.Write(out_char,::strlen(out_char));
				sprintf(out_char,"\t %x\t %x\t %d",bit_data[count],tmp_data,count);
				f_out.Write(out_char,::strlen(out_char));
				f_out.Write("\r\n",2);
			}
		}
		else if((tmp_data&0x01ff)!=(bit_data[count]&0x01ff))
		{
			err++;
			sprintf(out_char,"1\t %d",f_in.GetPosition());
			f_out.Write(out_char,::strlen(out_char));
			sprintf(out_char,"\t %x\t %x\t %d",bit_data[count],tmp_data,count);
			f_out.Write(out_char,::strlen(out_char));
			f_out.Write("\r\n",2);
		}
		bit_data[count]=tmp_data;
		count++;
	}
	message.Format(_T("error %d!"),err);
	AfxMessageBox(message);
	f_in.Close();
	f_out.Close();
}

void CFPGADlg::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

