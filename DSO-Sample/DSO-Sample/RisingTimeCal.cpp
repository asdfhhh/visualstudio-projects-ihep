#include "stdafx.h"
#include "RisingTimeCal.h"


RisingTimeCal::RisingTimeCal(int n)
{
	nBin = n;
}


RisingTimeCal::~RisingTimeCal()
{
}


int RisingTimeCal::Initial()
{
	return 0;
}


double RisingTimeCal::Processing(double* ibuf)
{
	double data_tmp = 0;
	int peak_ch=0;
	for (int i = 1; i < nBin; i++)
	{
		if (data_tmp <= (ibuf[i] - ibuf[i - 1]))
		{
			data_tmp = ibuf[i] - ibuf[i - 1];
			peak_ch = i;
		}
	}
	int seek_num = 1;
	int thr = 1;
	while (((ibuf[peak_ch - seek_num] -ibuf[peak_ch-seek_num-1])- thr) > 0)seek_num++;
	return seek_num;
}


