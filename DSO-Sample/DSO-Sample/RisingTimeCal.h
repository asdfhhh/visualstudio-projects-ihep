#pragma once
#include "TH1F.h"

class RisingTimeCal
{
public:
	RisingTimeCal(int n);
	~RisingTimeCal();
	int Initial();
	double Processing(double* ibuf);
	double Calculate();
private:
	int nBin;
	TH1F*data;
};

