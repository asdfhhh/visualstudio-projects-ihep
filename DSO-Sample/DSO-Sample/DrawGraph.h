#pragma once
#include "TGraph.h"
#include "TMultiGraph.h"
class DrawGraph
{
public:
	DrawGraph();
	~DrawGraph();
	inline TGraph* GetTGraph(int Chn) {
		if (Chn == 1)return Wave1; 
		return Wave2;
	};
	inline bool SetTGraph(int N, double *X, double *Y1,double *Y2) {
		NGraph = N;
		XGraph = X;
		YGraph1 = Y1;
		YGraph2 = Y2;
		if(N)return true;
		return false;
	};
	TMultiGraph* MakeTGraph();
	int NGraph;
	double *XGraph;
	double *YGraph1;
	double *YGraph2;
	TMultiGraph *mg;
	TGraph *Wave1;
	TGraph *Wave2;
private:
	bool firstrun;
public:
	inline bool SetChOn(int Ch_n, bool On_flag)
	{
		if (Ch_n == 0)
		{
			Ch1_Flag = On_flag;
			return true;
		}
		else if (Ch_n == 1)
		{
			Ch2_Flag = On_flag;
			return true;
		}
		return false;
	}
	bool Ch1_Flag;
	bool Ch2_Flag;
};

