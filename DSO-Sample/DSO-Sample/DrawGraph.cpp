#include "stdafx.h"
#include "DrawGraph.h"
#include "TAxis.h"


DrawGraph::DrawGraph()
	: firstrun(true)
{
	NGraph = 0;
	XGraph = 0;
	XGraph = 0;
	Wave = 0;
}


DrawGraph::~DrawGraph()
{
	if (Wave)delete Wave;
}

TGraph* DrawGraph::MakeTGraph()
{
	Wave = new TGraph(NGraph, XGraph, YGraph);
	Wave->SetLineColor(5);
	Wave->GetXaxis()->SetTitle("X title");
	Wave->GetXaxis()->SetAxisColor(18);
	Wave->GetXaxis()->SetTitleColor(18);
	Wave->GetXaxis()->SetLabelColor(18);
	Wave->GetYaxis()->SetTitle("Y title");
	Wave->GetYaxis()->SetAxisColor(18);
	Wave->GetYaxis()->SetTitleColor(18);
	Wave->GetYaxis()->SetLabelColor(18);
	firstrun = false;
	return Wave;
}
