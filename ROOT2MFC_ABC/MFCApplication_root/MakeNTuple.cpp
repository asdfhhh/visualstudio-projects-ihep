#include "stdafx.h"
#include "MakeNTuple.h"


MakeNTuple::MakeNTuple()
{
	h = new TH1F("test", "test", 100, -10, 10);
}


MakeNTuple::~MakeNTuple()
{
	delete h;
}

void MakeNTuple::fillrandom(int num)
{
	h->FillRandom("gaus", num);
}