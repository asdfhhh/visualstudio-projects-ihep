// FPGADlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FPGA.h"
#include "FPGADlg.h"
#include <map>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFPGADlg 对话框




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


// CFPGADlg 消息处理程序

BOOL CFPGADlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFPGADlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
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
	CString OutName;
	if (!f_in.Open(StrFileName,CFile::modeRead|CFile::typeBinary,NULL))
	{
		AfxMessageBox(_T("Invalid File Name!"));
		return;
	}
	OutName=StrFileName+_T(".txt");
	//long a=f_in.GetLength();
	if(!f_out.Open(OutName,CFile::modeCreate|CFile::modeReadWrite,NULL))
	{
		return;
	}
	sprintf(out_char,"Error code:1 upset, 2 length error");
	f_out.Write(out_char,::strlen(out_char));
	f_out.Write("\r\n",2);
	sprintf(out_char,"code\t position\t ori\t prt\t memory");
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
		if((f_in.GetPosition()%(f_in.GetLength()/100))==0)
		{
			m_Progress.StepIt();
			//			Sleep(0.1);
		}
		if((tmp_data&0xfe00)==0xfe00)
		{
			offset=f_in.GetPosition();
			bit_data[count]=unsigned int(tmp_data&0x0000ffff);
			count++;
			for(;count<MEM_NUM;count++)
			{
				f_in.Read(&tmp_data,2);
				if((f_in.GetPosition()%(f_in.GetLength()/100))==0)
				{
					m_Progress.StepIt();
					//			Sleep(0.1);
				}
			bit_data[count]=unsigned int(tmp_data&0x0000ffff);
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
		if((tmp_data&0xfe00)==0x0000fe00)//head check
		{
			if((f_in.GetPosition()-offset)%MEM_NUM!=0)
			{
				sprintf(out_char,"2\t %d\t ",f_in.GetPosition());
				f_out.Write(out_char,::strlen(out_char));
					f_out.Write("\r\n",2);
			bit_data[count]=unsigned int(tmp_data&0x0000ffff);
			}
			count=1;
			for(;count<MEM_NUM;count++)
			{
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
					sprintf(out_char,"\t %x\t %x\t %d",bit_data[count],tmp_data&0x0000ffff,count);
					f_out.Write(out_char,::strlen(out_char));
					f_out.Write("\r\n",2);
				}
			bit_data[count]=unsigned int(tmp_data&0x0000ffff);
			}
		}
		/*else if((tmp_data&0x01ff)!=(bit_data[count]&0x01ff))
		{
		err++;
		sprintf(out_char,"1\t %d",f_in.GetPosition());
		f_out.Write(out_char,::strlen(out_char));
		sprintf(out_char,"\t %x\t %x\t %d",bit_data[count],tmp_data,count);
		f_out.Write(out_char,::strlen(out_char));
		f_out.Write("\r\n",2);
		}
		bit_data[count]=tmp_data;
		count++;*/
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

