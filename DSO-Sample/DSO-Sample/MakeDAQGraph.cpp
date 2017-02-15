#include "stdafx.h"
#include "MakeDAQGraph.h"


MakeDAQGraph::MakeDAQGraph()
{
	mca_con = NULL;
	rt_con = NULL;
	scatter_con = NULL;
	drawing_con = NULL;
}


MakeDAQGraph::~MakeDAQGraph()
{
	DeleteHist();
}

double MakeDAQGraph::Initial(DAQCTRL daq_c)
{
	mca_con = new TH1F("mca", "the Energy Spectrum", 500, 0, daq_c.MCA_MAX);
	rt_con = new TH1F("rtime", "the rising time", 500, 0, daq_c.RT_MAX);
	scatter_con = new TH2F("evt", "energy vs risingtime", 500, 0, daq_c.MCA_MAX, 500, 0, daq_c.RT_MAX);
	drawing_con = new TH1F("PSDwave", "Wave after PSD", DEF_READ_DATA_LEN, 0, DEF_READ_DATA_LEN);
	return 1;
}


int MakeDAQGraph::FillHist(int len, double* ibuf, double risingtime)
{
	drawing_con->Reset();
	for (int i = 0; i < len; i++)drawing_con->Fill(i, ibuf[i]);
	double adc = drawing_con->GetBinContent(drawing_con->GetMaximumBin());
	mca_con->Fill(adc);
	rt_con->Fill(risingtime);
	scatter_con->Fill(adc, risingtime);
	return 0;
}


int MakeDAQGraph::DeleteHist()
{
	if(mca_con)delete mca_con;
	if(rt_con)delete rt_con;
	if(scatter_con)delete scatter_con;
	if(drawing_con)delete drawing_con;
	return 0;
}
