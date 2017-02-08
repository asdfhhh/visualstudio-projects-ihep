#include "stdafx.h"
#include "RisingTimeCal.h"


RisingTimeCal::RisingTimeCal(int n)
{
	nBin = n;
	data = NULL;
}


RisingTimeCal::~RisingTimeCal()
{
	if (data)delete data;
}


int RisingTimeCal::Initial()
{
	if (data)delete data;
	data = new TH1F("data", "data", nBin, 0, nBin);
	return 0;
}


double RisingTimeCal::Processing(double* ibuf)
{
	if (data)
	{
		double data_tmp = 0;
		for (int i = 0; i < nBin; i++)
		{
			if(i)data->Fill(i, ibuf[i] - data_tmp);
			data_tmp = ibuf[i];
			return 1;
		}
	}
	else return 0.0;
}


double RisingTimeCal::Calculate()
{
	int peak = data->GetMaximumBin();
	int seek_num = 1;
	int thr = 1;
	while ((data->GetBinContent(peak - seek_num) - thr) > 0)seek_num++;
	return seek_num;
}
