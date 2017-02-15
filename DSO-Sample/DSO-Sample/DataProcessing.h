#pragma once
#include "LowPassFilter.h"
#include "HighPassFilter.h"
#include "RisingTimeCal.h"
#include "MakeDAQGraph.h"
#include "TFile.h"
#include "TNtuple.h"

//线程数据结构
typedef struct ThreadData
{
	double* ibuf1;
	double* ibuf2;
	double cutoff;
	double* obuf1;
	double* obuf2;
	int ilen;
	double *rt1;
	double *rt2;
	bool DSP_flag;
	bool SAVE_flag;
	TNtuple*OUT_Ntuple;
}THREADDATA;

class DataProcessing
{
public:
	DataProcessing();
	~DataProcessing();
	// this function for the thread
	UINT BeginThread();
	static UINT TreadFunction(LPVOID lParam);
public:
	double *Ch1;
	double *Ch2;
	int len;
	// Get the data point
	inline int GetData(double* Ch1_d, double* Ch2_d, int len_d)
	{
		Ch1 = Ch1_d;
		Ch2 = Ch2_d;
		len = len_d;
		return 0;
	}
	double* output1;
	double* output2;
	double risingtime1;
	double risingtime2;
	int Initial();
	MakeDAQGraph*daqgf;
	DAQCTRL daq_c;
	TFile*outf;
	TNtuple*outNtuple;
	int SetDAQCtrl(DAQCTRL tmp_c)
	{
		daq_c = tmp_c;
		daqgf->DeleteHist();
		daqgf->Initial(daq_c);
		return 0;
	}
	inline DAQCTRL GetDAQCtrl()
	{
		return daq_c;
	}
	int FillHist();
	int Stop();
};

