#ifndef DAQ_H
#define DAQ_H 1
#define	MAX_HISTO_CHANNELS	16		
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <bitset>
#include <fstream>
#include "TH1F.h"
#include "TFile.h"
#include "TRandom.h"
#include "TBrowser.h"
#include "vme_api_en.h"

using namespace std;

extern TH1F*total;
class viewer;


class daq
{
private:
	EN_PCI_IMAGE_DATA idata;
	int devHandle,result;
	UINT8 buffer[4];
	UINT32 data;
	UINT32 geo;
	UINT32 ch;
	UINT32 adc;
	UINT8 tmp_data;

	TRandom*rnd;
	TFile*f;
	char address[10];
	int read_events;
	int Hview;
	char Hname[16];
	TH1F*h1[MAX_HISTO_CHANNELS];
	char name[16]; 
	bool run_flag; 
	bool pause_flag;
	int num;
	int fmode;
	int daq_time;
	int daq_counts;
public:
	daq();
	~daq();
	int Getdata();
	void Pause();
	void Stop();
	char* Write();
	void Reset();
	void SetHit(int fh){Hview=fh-1;}
	void SetMode(const int);
	void SetAdd(const char*fadd)
	{
		strcpy(address,fadd);
	};
	void SetParamters(int tmp_t,int tmp_c)
	{
		daq_time=tmp_t;
		daq_counts=tmp_c;
	}
};
#endif
