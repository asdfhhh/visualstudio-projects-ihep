#include "stdafx.h"
#include "DataProcessing.h"


DataProcessing::DataProcessing()
	: output1(NULL)
	, output2(NULL)
{
	len = DEF_READ_DATA_LEN;
	Ch1 = NULL;
	Ch2 = NULL;
	outf = NULL;
	outNtuple = NULL;
	daqgf = new MakeDAQGraph();
	daq_c.cutoff = 0.01;
	daq_c.MCA_MAX = 1000;
	daq_c.RT_MAX = 10;
	daq_c.PSD_flag = true;
	daq_c.SAVE_flag = false;
	daqgf->Initial(daq_c);
}


DataProcessing::~DataProcessing()
{
	if (output1)delete[] output1;
	if (output2)delete[] output2;
	if (daqgf)delete daqgf;
}


// this function for the thread
UINT DataProcessing::BeginThread()
{
	//insert the thread of DSP
	THREADDATA* pData = new THREADDATA;
	pData->ibuf1 = Ch1;
	pData->ibuf2 = Ch2;
	pData->obuf1 = output1;
	pData->obuf2 = output2;
	pData->ilen = len;
	pData->cutoff = daq_c.cutoff;
	pData->rt1 = &risingtime1;
	pData->rt2 = &risingtime2;
	pData->DSP_flag = daq_c.PSD_flag;
	pData->SAVE_flag = daq_c.SAVE_flag;
	pData->OUT_Ntuple = outNtuple;
	CWinThread* mythread = AfxBeginThread((AFX_THREADPROC)TreadFunction, pData, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	return 0;
}


UINT DataProcessing::TreadFunction(LPVOID lParam)
{
	//initial
	THREADDATA* pData = (THREADDATA*)lParam;
	if (pData->DSP_flag)
	{
		LowPassFilter*lowp = new LowPassFilter();
		HighPassFilter*highp = new HighPassFilter();
		lowpstuff lowp_p;
		highpstuff highp_p;
		//ch1
		//energy
		lowp_p.cutoff = highp_p.cutoff = pData->cutoff;
		lowp->Initial(&lowp_p);
		highp->Initial(&highp_p);
		double baseline = 0;
		for (int i = 0; i < pData->ilen / 3; i++)baseline = baseline + pData->ibuf1[i];
		if (pData->ilen)baseline = baseline / (pData->ilen / 3);
		for (int i = 0; i < pData->ilen; i++)
		{
			highp_p.outm1 = highp->Processing(&highp_p, pData->ibuf1[i] - baseline);
			lowp_p.outm1 = lowp->Processing(&lowp_p, highp_p.outm1);
			pData->obuf1[i] = highp_p.outm1;
		}
		for (int ii = 0; ii < 5; ii++)
		{
			for (int i = 0; i < pData->ilen; i++)
			{
				lowp_p.outm1 = lowp->Processing(&lowp_p, pData->obuf1[i]);
				pData->obuf1[i] = lowp_p.outm1;
			}
		}
		//ch2
		//energy
		lowp_p.cutoff = highp_p.cutoff = pData->cutoff;
		lowp->Initial(&lowp_p);
		highp->Initial(&highp_p);
		baseline = 0;
		for (int i = 0; i < pData->ilen / 3; i++)baseline = baseline + pData->ibuf2[i];
		if (pData->ilen)baseline = baseline / (pData->ilen / 3);
		for (int i = 0; i < pData->ilen; i++)
		{
			highp_p.outm1 = highp->Processing(&highp_p, baseline - pData->ibuf2[i]);
			lowp_p.outm1 = lowp->Processing(&lowp_p, highp_p.outm1);
			pData->obuf2[i] = highp_p.outm1;
		}
		for (int ii = 0; ii < 5; ii++)
		{
			for (int i = 0; i < pData->ilen; i++)
			{
				lowp_p.outm1 = lowp->Processing(&lowp_p, pData->obuf2[i]);
				pData->obuf2[i] = lowp_p.outm1;
			}
		}
		delete lowp;
		delete highp;
	}
	else
	{
		for (int i = 0; i < pData->ilen; i++)
		{
			pData->obuf1[i] = pData->ibuf1[i];
			pData->obuf2[i] = pData->ibuf2[i];
		}
	}
	double peak1 = 0;
	double peak2 = 0;
	for (int i = 0; i < pData->ilen; i++)
	{
		peak1 = (pData->obuf1[i] > peak1) ? pData->obuf1[i] : peak1;
		peak2 = (pData->obuf2[i] > peak2) ? pData->obuf2[i] : peak2;
	}

	RisingTimeCal* rtcal = new RisingTimeCal(pData->ilen);
	//ch1
	//rising time
	rtcal->Initial();
	*pData->rt1 = rtcal->Processing(pData->ibuf1);
	//ch2
	//rising time
	rtcal->Initial();
	*pData->rt2 = rtcal->Processing(pData->ibuf2);
	//saving file;
	if (pData->SAVE_flag)pData->OUT_Ntuple->Fill(peak1, *pData->rt1, peak2, *pData->rt2);
	delete rtcal;
	delete pData;
	return 0;
}


int DataProcessing::Initial()
{
	if (output1)delete[] output1;
	if (output2)delete[] output2;
	output1 = new double[len];
	output2 = new double[len];
	if (daq_c.SAVE_flag)
	{
		CTime time = CTime::GetTickCount();
		CString tmp_name = time.Format("%Y%m%d-%H%M%S.root");
		char *aux_string = (char*)tmp_name.GetBuffer(0);
		long len = wcslen(tmp_name); //the length of "salut"
		wcstombs(aux_string, tmp_name, len); //conversion to char *	
		aux_string[len] = '\0';	 //don't forget to put the caracter of terminated string	
		outf = new TFile(aux_string, "NEW");
		outNtuple = new TNtuple("outdata","outdata","E1:T1:E2:T2");
	}
	return 0;
}



int DataProcessing::FillHist()
{
	daqgf->FillHist(len, output1, risingtime1);
	return 0;
}


int DataProcessing::Stop()
{
	if (daq_c.SAVE_flag)
	{
		outNtuple->Write();
		outf->Close();
	}
	return 0;
}
