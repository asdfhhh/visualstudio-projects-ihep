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
};

