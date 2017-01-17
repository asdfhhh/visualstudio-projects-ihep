#include "stdafx.h"
#include "DrawGraph.h"
#include "TAxis.h"


DrawGraph::DrawGraph()
	: firstrun(true)
	, Ch1_Flag(true)
	, Ch2_Flag(true)
{
	NGraph = 0;
	XGraph = 0;
	YGraph1 = 0;
	YGraph2 = 0;
	Wave1 = 0;
	Wave2 = 0;
	mg = 0;

}


DrawGraph::~DrawGraph()
{
	if (Wave1)delete Wave1;
	if (Wave2)delete Wave2;
}

TMultiGraph* DrawGraph::MakeTGraph()
{
	if (!(Ch1_Flag||Ch2_Flag)) return NULL;
	mg = new TMultiGraph();
	if (Ch1_Flag)
	{
		Wave1 = new TGraph(NGraph, XGraph, YGraph1);
		Wave1->SetLineColor(5);	
		mg->Add(Wave1);
	}
	if (Ch2_Flag)
	{
		Wave2 = new TGraph(NGraph, XGraph, YGraph2);
		Wave2->SetLineColor(4);
		mg->Add(Wave2);
	}
	return mg;
}
