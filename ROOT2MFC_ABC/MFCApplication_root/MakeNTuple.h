#pragma once
#include "TH1F.h"
class MakeNTuple
{
public:
	MakeNTuple();
	~MakeNTuple();
	void fillrandom(int num);
private:
	TH1F*h;
public:
	inline TH1F* getntuple(){ return h; }
};

