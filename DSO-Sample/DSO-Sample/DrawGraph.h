#pragma once
#include "TGraph.h"
class DrawGraph
{
public:
	DrawGraph();
	~DrawGraph();
	inline TGraph* GetTGraph() {
		return Wave;
	};
	inline bool SetTGraph(int N, double *X, double *Y) {
		NGraph = N;
		XGraph = X;
		YGraph = Y;
		if(N)return true;
		return false;
	};
	TGraph* MakeTGraph();
	int NGraph;
	double *XGraph;
	double *YGraph;
	TGraph *Wave;
protected:
	bool firstrun;
};

