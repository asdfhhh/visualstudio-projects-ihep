#pragma once
/**
*  Filename: mwpc.c
*   Created: 2018-06-27 02:04:45
*      Desc: TODO (some description)
*    Author: Haiyun Teng, haiyun.teng@gmail.com
*   Company: CSNS
*/
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <vector>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <Windows4Root.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TPad.h>
#include "MWPCdef.h"

using namespace std;

class MWPCANA
{
public:
	MWPCANA(CListBox *output);
	~MWPCANA();
	void Processing(CString filename);
	int SLICESIZE;//max slice(800ns) number in 40ms
	int SIGNALSIZE;// XCHANNELNUM+YCHANNELNUM+1
	int XCHANNELNUM;// index from 1 to 50
	int YCHANNELNUM;// index from 51 to 144
	float QMIN;// Q-base threshold
	float QMAX;// hit charge threshold
	int MATCHWINDOW;// time window, 40=1us, 1 unit for 25ns
	int STRIPGAP;// allow for not immediate channels, not used currently
	int TOFRANGE1;// fixed start value for tof bin range
	int TOFRANGE2;// fixed end value for tof bin range
	int WIDELIMITX;// least strip size of one hitX
	int WIDELIMITY;// least strip size of one hitY
	int QSUMX;// sumQ for hitX in one neutron
	int QSUMY;// sumQ for hitY in one neutron
	int FASTMATCH1;// set to 1 if MATCHWINDOW is above 32
	int FASTMATCH2;// set to 1 if MATCHWINDOW is above 64
	inline void SetSLICESIZE(int par) { SLICESIZE = par; }
	inline void SetSIGNALSIZE(int par) { SIGNALSIZE = par; }
	inline void SetXCHANNELNUM(int par) { XCHANNELNUM = par; }
	inline void SetYCHANNELNUM(int par) { YCHANNELNUM = par; }
	inline void SetQMIN(float par) { QMIN = par; }
	inline void SetQMAX(float par) { QMAX = par; }
	inline void SetMATCHWINDOW(int par) { MATCHWINDOW = par; }
	inline void SetSTRIPGAP(int par) { STRIPGAP = par; }
	inline void SetTOFRANGE1(int par) { TOFRANGE1 = par; }
	inline void SetTOFRANGE2(int par) { TOFRANGE2 = par; }
	inline void SetWIDELIMITX(int par) { WIDELIMITX = par; }
	inline void SetWIDELIMITY(int par) { WIDELIMITY = par; }
	inline void SetQSUMX(int par) { QSUMX = par; }
	inline void SetQSUMY(int par) { QSUMY = par; }
	inline void SetFASTMATCH1(int par) { FASTMATCH1 = par; }
	inline void SetFASTMATCH2(int par) { FASTMATCH2 = par; }
	inline void SetProgress(CProgressCtrl*par) { m_Progress = par; }
	inline int GetSLICESIZE() { return SLICESIZE; }
	inline int GetSIGNALSIZE() { return SIGNALSIZE; }
	inline int GetXCHANNELNUM() { return XCHANNELNUM; }
	inline int GetYCHANNELNUM() { return YCHANNELNUM; }
	inline float GetQMIN() { return QMIN; }
	inline float GetQMAX() { return QMAX; }
	inline int GetMATCHWINDOW() { return MATCHWINDOW; }
	inline int GetSTRIPGAP() { return STRIPGAP; }
	inline int GetTOFRANGE1() { return TOFRANGE1; }
	inline int GetTOFRANGE2() { return TOFRANGE2; }
	inline int GetWIDELIMITX() { return WIDELIMITX; }
	inline int GetWIDELIMITY() { return WIDELIMITY; }
	inline int GetQSUMX() { return QSUMX; }
	inline int GetQSUMY() { return QSUMY; }
	inline int GetFASTMATCH1() { return FASTMATCH1; }
	inline int GetFASTMATCH2() { return FASTMATCH2; }

	CListBox *pCtrl;
	CProgressCtrl* m_Progress;

private:

	void scanSlice();
	void processMap();
	//void processSignal(int sliceIdx, int signalIdx1, int signalIdx2);
	void matchNeutronX();
	void matchNeutronY();
	inline void swap32(uint32_t *value) {
		// butterfly switch 0123->3210 
		*value = ((*value) << 16) | ((*value) >> 16); //2301
		*value = (((*value) << 8) & 0xff00ff00) | (((*value) >> 8) & 0x00ff00ff); //3210
	}

	inline void swap64(uint64_t *value) {
		// butterfly switch 01234567->32107654
		*value = (((*value) << 16) & 0xffff0000ffff0000) | (((*value) >> 16) & 0x0000ffff0000ffff); //23016745
		*value = (((*value) << 8) & 0xff00ff00ff00ff00) | (((*value) >> 8) & 0x00ff00ff00ff00ff); //32107654
	}

	inline void getHit(uint16_t sliceIdx, uint16_t range, Hit &hit) {
		uint32_t *eventMapTS = &eventMapT[sliceIdx*SIGNALSIZE];
		uint16_t *eventMapCS = &eventMapC[sliceIdx*SIGNALSIZE];
		uint16_t *eventMapBS = &eventMapB[sliceIdx*SIGNALSIZE];

		uint16_t signalIdx1 = range & 0xff;
		uint16_t signalIdx2 = (range >> 8) & 0xff;
		float Q, B, T, sumQ = 0., sumW = 0., minC = 10000., maxC = 0., dQ = 0.;
		for (uint16_t iter = signalIdx1, idx = 0; iter <= signalIdx2; iter++, idx++) {
			minC = (minC <= (float)eventMapCS[iter]) ? minC : (float)eventMapCS[iter];
			maxC = (maxC >= (float)eventMapCS[iter]) ? maxC : (float)eventMapCS[iter];
			T = (float)eventMapTS[iter];
			Q = (float)eventMapCS[iter];
			B = (float)eventMapBS[iter];
			hit.qstrip[idx] = Q;
			hit.bstrip[idx] = B;
			hit.cstrip[idx] = Q - B;
			hit.tstrip[idx] = T;
			sumQ += hit.cstrip[idx];
			sumW += hit.cstrip[idx] * (float)iter; // weighted strip number
			if (PERSON_DEBUG) cout << hex << "strip , ch: " << iter << ", charge: " << Q << endl;
		}
		hit.charge = sumQ;
		hit.nstrip = signalIdx2 - signalIdx1 + 1;
		hit.center = sumW / (sumQ + 0.000000001); // for safty
												  //hit.center = ((float)(signalIdx1+signalIdx2))/2.;
		hit.strip1st = signalIdx1;
		if ((hit.nstrip) % 2 == 1 && hit.nstrip>1) {
			hit.dQ = fabs((float)eventMapCS[(signalIdx1 + signalIdx2) / 2 - 1] - (float)eventMapCS[(signalIdx1 + signalIdx2) / 2 + 1]) / sumQ;
		}
		else {
			hit.dQ = fabs((float)eventMapCS[(int)((signalIdx1 + signalIdx2) / 2)] - (float)eventMapCS[(int)((signalIdx1 + signalIdx2) / 2) + 1]) / sumQ;
		}
	}

	char *buf;
	uint64_t buf64;
	ifstream f0;
	PulseHead pulse;
	SliceHead slice0, slice1;
	uint32_t t0Count, packSize, sliceCount, sliceNum = 0, pre_tDataId = 0, pre_eventNumber = 0, cur_tDataId, cur_eventNumber, channelX, chargeX;
	int totalEvent, validEvent;
	uint32_t *eventMapT; //[SLICESIZE][SIGNALSIZE];
	uint16_t *eventMapC; //[SLICESIZE][SIGNALSIZE];
	uint16_t *eventMapB; //[SLICESIZE][SIGNALSIZE];
	uint16_t *eventMapSlice, *eventMapMin, *eventMapMax; //[0-SLICESIZE]
	uint16_t eventMapIdx;
	uint16_t *sBuffer1, *sBuffer2;
	uint16_t sBufferIdx;
	uint32_t *signalMapXT, *signalMapYT; // inordered tof record for each slice signal in X and Y
	uint16_t *signalMapXM, *signalMapYM, *signalMapXS, *signalMapYS, *signalMapXR, *signalMapYR; // matchN, slice, range((strip_high<<8)|strip_low) for each tof from above record in X and Y 
	uint32_t *signalMapXIdx, *signalMapYIdx; // end number of record for each slice signal in X and y
	uint32_t *matchX, *matchY; // idx of matched Y for X
	uint32_t matchIdx;

	TH2F *n2xy, *q2xy;
	Neutron neutron;
	Hit hitT, hitX, hitY, multiHits[100];
	int multiHitSize;
	int signalNum;
	TH1F *hsx, *hsy, *npx, *npm;
	TH1F **hBase, **hQ, **hTOF;
	int sampleT0;
	TTree *tree0, *tree1, *tree2, *tree3;
public:
	CString output_message;
};
