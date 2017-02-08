#pragma once
#include "LowPassFilter.h"
#include "HighPassFilter.h"
#include "RisingTimeCal.h"
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
};

