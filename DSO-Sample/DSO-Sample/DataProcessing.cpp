#include "stdafx.h"
#include "DataProcessing.h"


DataProcessing::DataProcessing()
	: output1(NULL)
	, output2(NULL)
{
	len = 0;
	Ch1 = NULL;
	Ch2 = NULL;
	daqgf = new MakeDAQGraph();
	daq_c.cutoff = 0.01;
	daq_c.MCA_MAX = 1000;
	daq_c.RT_MAX = 10;
	daqgf->Initial(daq_c);
}


DataProcessing::~DataProcessing()
{
	if (output1)delete output1;
	if (output2)delete output2;
	if (daqgf)delete daqgf;
}


// this function for the thread
UINT DataProcessing::BeginThread()
{
	//insert the thread of DSP
	Initial();
	THREADDATA* pData = new THREADDATA;
	pData->ibuf1 = Ch1;
	pData->ibuf2 = Ch2;
	pData->obuf1 = output1;
	pData->obuf2 = output2;
	pData->ilen = len;
	pData->cutoff = daq_c.cutoff;
	pData->rt1 = &risingtime1;
	pData->rt2 = &risingtime2;
	CWinThread* mythread = AfxBeginThread((AFX_THREADPROC)TreadFunction, pData, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	return 0;
}


UINT DataProcessing::TreadFunction(LPVOID lParam)
{
	//initial
	THREADDATA* pData = (THREADDATA*)lParam;
	LowPassFilter*lowp= new LowPassFilter();
	HighPassFilter*highp = new HighPassFilter();
	RisingTimeCal* rtcal = new RisingTimeCal(pData->ilen);
	lowpstuff lowp_p;
	highpstuff highp_p;
	lowp_p.cutoff = highp_p.cutoff = pData->cutoff;
	//ch1
	//energy
	lowp->Initial(&lowp_p);
	highp->Initial(&highp_p);
	double baseline = 0;
	for (int i = 0; i < pData->ilen / 3; i++)baseline = baseline + pData->ibuf1[i];
	if(pData->ilen)baseline = baseline / (pData->ilen / 3);
	for (int i = 0; i < pData->ilen; i++)
	{
		highp_p.outm1 = highp->Processing(&highp_p, pData->ibuf1[i] - baseline);
		lowp_p.outm1=lowp->Processing(&lowp_p, highp_p.outm1);
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
	//rising time
	rtcal->Initial();
	*pData->rt1 = rtcal->Processing(pData->ibuf1);
	/*//Ch2
	//energy
	lowp->Initial(&lowp_p);
	highp->Initial(&highp_p);
	baseline = 0;
	for (int i = 0; i < pData->ilen / 3; i++)baseline = baseline + pData->ibuf2[i];
	if (pData->ilen)baseline = baseline / (pData->ilen / 3);

	for (int i = 0; i < pData->ilen; i++)
	{
		lowp_p.outm1 = lowp->Processing(&lowp_p, pData->ibuf2[i]-baseline);
		highp_p.outm1 = highp->Processing(&highp_p, lowp_p.outm1);
		pData->obuf2[i] = highp_p.outm1;
	}
	//rising time
	rtcal->Initial();
	rtcal->Processing(pData->ibuf2);
	*pData->rt2 = rtcal->Calculate();*/
	delete rtcal;
	delete pData;
	delete lowp;
	delete highp;
	return 0;
}


int DataProcessing::Initial()
{
	if (output1)delete output1;
	if (output2)delete output2;
	output1 = new double[len];
	output2 = new double[len];
	return 0;
}



int DataProcessing::FillHist()
{
	daqgf->FillHist(len, output1, risingtime1);
	return 0;
}
