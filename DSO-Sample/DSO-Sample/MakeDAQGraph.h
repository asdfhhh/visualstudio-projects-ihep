#pragma once
#include "TH1F.h"
#include "TH2F.h"
typedef struct DAQControl
{
	int MCA_MAX;
	int RT_MAX;
	double cutoff;
	bool PSD_flag;
	bool SAVE_flag;
	bool Ch1_revert;
	bool Ch2_revert;
}DAQCTRL;
class MakeDAQGraph
{
public:
	MakeDAQGraph();
	~MakeDAQGraph();
	double Initial(DAQCTRL daq_c);
	TH1F* mca_con;
	TH1F* rt_con;
	TH1F*drawing_con;
	TH2F* scatter_con;
	int FillHist(int len, double* ibuf, double risingtime);
	int DeleteHist();
};

