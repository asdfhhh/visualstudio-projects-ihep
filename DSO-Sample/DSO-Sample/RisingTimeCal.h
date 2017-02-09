#pragma once

class RisingTimeCal
{
public:
	RisingTimeCal(int n);
	~RisingTimeCal();
	int Initial();
	double Processing(double* ibuf);
private:
	int nBin;
};

