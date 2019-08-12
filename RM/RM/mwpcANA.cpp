#include "stdafx.h"
#include "mwpcANA.h"

MWPCANA::MWPCANA(CListBox *output)
	: output_message(_T(""))
{
	SLICESIZE = 50001; //max slice(800ns) number in 40ms
	SIGNALSIZE = 145; // XCHANNELNUM+YCHANNELNUM+1
	XCHANNELNUM = 50; // index from 1 to 50
	YCHANNELNUM = 94; // index from 51 to 144
	QMIN = 30.;  // Q-base threshold
	QMAX = 0.;  // hit charge threshold
	MATCHWINDOW = 80; // time window, 40=1us, 1 unit for 25ns
	STRIPGAP = 1; // allow for not immediate channels, not used currently
	TOFRANGE1 = 0; // fixed start value for tof bin range
	TOFRANGE2 = 1600000; // fixed end value for tof bin range
	WIDELIMITX = 2; // least strip size of one hitX
	WIDELIMITY = 2; // least strip size of one hitY
	QSUMX = 0;  // sumQ for hitX in one neutron
	QSUMY = 0;  // sumQ for hitY in one neutron
	FASTMATCH1 = 1; // set to 1 if MATCHWINDOW is above 32
	FASTMATCH2 = 1; // set to 1 if MATCHWINDOW is above 64
	pCtrl = output;
}
void MWPCANA::Processing(CString filename)
{
	CString tmp_name =filename+ ".dat";
	char *aux_string = (char*)tmp_name.GetBuffer(0);
	long len = wcslen(tmp_name); //the length of "salut"
	wcstombs(aux_string, tmp_name, len); //conversion to char *	
	aux_string[len] = '\0';	 //don't forget to put the caracter of terminated string

	f0.open(aux_string, ios::in | ios::binary);

	if (!f0.is_open())
	{
		AfxMessageBox(_T("Error! Can not opne the raw data!"));
		return;
	}
	
	CString tmp_name1 = filename + ".root";
	char *aux_string1 = (char*)tmp_name1.GetBuffer(0);
	len = wcslen(tmp_name1); //the length of "salut"
	wcstombs(aux_string1, tmp_name1, len); //conversion to char *	
	aux_string1[len] = '\0';	 //don't forget to put the caracter of terminated string

	TFile *f1 = new TFile(aux_string1, "RECREATE");

	buf = (char*)malloc(BUFFERSIZE);
	tree0 = new TTree("t0", "the fired strip be stored");
	tree0->Branch("t0num", &t0Count, "t0num/I");
	tree0->Branch("charge", &chargeX, "charge/I");
	tree0->Branch("channel", &channelX, "channel/I");
	tree1 = new TTree("t1", "the neutron be stored");
	tree1->Branch("t0num", &(neutron.t0num), "t0num/I");
	tree1->Branch("px", &(neutron.x), "px/F");
	tree1->Branch("py", &(neutron.y), "py/F");
	tree1->Branch("tof", &(neutron.t), "tof/F");
	tree1->Branch("tofx", &(neutron.tx), "tofx/F");
	tree1->Branch("tofy", &(neutron.ty), "tofy/F");
	tree1->Branch("chargex", &(neutron.chargex), "chargex/F");
	tree1->Branch("chargey", &(neutron.chargey), "chargey/F");
	tree1->Branch("nsx", &(neutron.nsx), "nsx/I");
	tree1->Branch("nsy", &(neutron.nsy), "nsy/I");
	tree1->Branch("qsum", &(neutron.qsum), "qsum/F");
	tree1->Branch("qx", &(neutron.qx), "qx/F");
	tree1->Branch("qy", &(neutron.qy), "qy/F");
	tree1->Branch("basex", &(neutron.basex), "basex/F");
	tree1->Branch("basey", &(neutron.basey), "basey/F");
	tree1->Branch("dqX", &(neutron.dqx), "dqx/F");
	tree1->Branch("dT", &(neutron.dT), "dT/I");
	tree1->Branch("matchx", &(neutron.matchx), "matchx/I");
	tree1->Branch("matchy", &(neutron.matchy), "matchy/I");
	tree2 = new TTree("t2", "the hit be stored");
	tree2->Branch("center", &(hitT.center), "center/F");
	tree2->Branch("charge", &(hitT.charge), "charge/F");
	tree2->Branch("tof", &(hitT.tof), "tof/I");
	tree2->Branch("t0num", &(hitT.t0num), "t0num/I");
	tree2->Branch("nstrip", &(hitT.nstrip), "nstrip/I");
	tree2->Branch("dQ", &(hitT.dQ), "dQ/F");
	tree2->Branch("charge", &(hitT.charge), "charge/F");
	tree3 = new TTree("t3", "the match of hit");
	tree3->Branch("tof", &(hitT.tof), "tof/I");
	tree3->Branch("match", &(hitT.match), "match/I");
	tree3->Branch("dT1", &(hitT.dT1), "dT1/I");
	tree3->Branch("dT2", &(hitT.dT2), "dT2/I");
	tree3->Branch("centerx", &(hitT.center), "centerx/F");
	tree3->Branch("centery", &(hitY.center), "centery/F");
	tree3->Branch("charge", &(hitT.charge), "charge/F");
	tree3->Branch("nsx", &(hitT.nstrip), "nsx/I");

	n2xy = new TH2F("n2xy", "n2xy", 94 * 10, 0.5, 94.5, 50 * 10, 0.5, 50.5);
	//hsx = new TH1F("hsx", "hsx", 8, 0.5, 8.5);
	//hsy = new TH1F("hsy", "hsy", 8, 0.5, 8.5);
	//npx = new TH1F("npx", "npx", 94*40, 0.5, 94.5);
	npm = new TH1F("npm", "npm", 144, 0.5, 144.5);
	hBase = new TH1F*[SIGNALSIZE];
	hQ=new TH1F*[SIGNALSIZE]; 
	hTOF = new TH1F*[SIGNALSIZE];
	string hName;
	for (int i = 0; i<SIGNALSIZE; i++) {
		stringstream sh;
		sh << i;
		hName = "base" + sh.str();
		hBase[i] = new TH1F(hName.c_str(), hName.c_str(), 1025, 0.5, 1025.5);
		hName = "Q" + sh.str();
		hQ[i] = new TH1F(hName.c_str(), hName.c_str(), 1025, 0.5, 1025.5);
		hName = "TOF" + sh.str();
		hTOF[i] = new TH1F(hName.c_str(), hName.c_str(), 40000, 0., TOFRANGE2);
	}
	sampleT0 = 0;

	signalNum = 0;
	totalEvent = 0;
	validEvent = 0;

	int WINDOWSIZE = SLICESIZE*SIGNALSIZE;
	eventMapT = new uint32_t[WINDOWSIZE];
	eventMapC = new uint16_t[WINDOWSIZE];
	eventMapB = new uint16_t[WINDOWSIZE];
	eventMapSlice = new uint16_t[SLICESIZE];
	eventMapMin = new uint16_t[SLICESIZE];
	eventMapMax = new uint16_t[SLICESIZE];
	eventMapIdx = 0;
	sBuffer1 = new uint16_t[SIGNALSIZE];
	sBuffer2 = new uint16_t[SIGNALSIZE];
	signalMapXT = new uint32_t[SLICESIZE*XCHANNELNUM];
	signalMapYT = new uint32_t[SLICESIZE*YCHANNELNUM];
	signalMapXM = new uint16_t[SLICESIZE*XCHANNELNUM];
	signalMapYM = new uint16_t[SLICESIZE*YCHANNELNUM];
	signalMapXS = new uint16_t[SLICESIZE*XCHANNELNUM];
	signalMapYS = new uint16_t[SLICESIZE*YCHANNELNUM];
	signalMapXR = new uint16_t[SLICESIZE*XCHANNELNUM];
	signalMapYR = new uint16_t[SLICESIZE*YCHANNELNUM];
	signalMapXIdx = new uint32_t[SLICESIZE];
	signalMapYIdx = new uint32_t[SLICESIZE];
	matchX = new uint32_t[SLICESIZE*XCHANNELNUM];
	matchY = new uint32_t[SLICESIZE*XCHANNELNUM];
	matchIdx = 0;

	f0.seekg(0, f0.end);
	size_t fileloop = f0.tellg();
	m_Progress->SetRange(0, 100);
	f0.seekg(0, f0.beg);
	while (f0.read((char*)(buf), sizeof(uint32_t)))
	{
		swap32((uint32_t*)buf);
		if (PERSON_DEBUG) cout << hex << "head binary: " << setw(8) << setfill('0') << (*(uint32_t*)buf) << endl;
		if ((*(uint32_t*)buf) == 0xee1234ee) 
		{
			f0.read((char*)(buf), 15 * sizeof(uint32_t));
			swap32(((uint32_t*)buf) + 9);
			t0Count = ((uint32_t*)buf)[9];
			swap32(((uint32_t*)buf) + 10);
			packSize = ((uint32_t*)buf)[10];
			swap32(((uint32_t*)buf) + 11);
			sliceCount = ((uint32_t*)buf)[11];
			//pre_tDataId = 0;
			//pre_eventNumber = 0;
			//cur_tDataId = 0;
			//cur_eventNumber = 0;
			validEvent = 0;
			if (PERSON_DEBUG) cout << hex << "T0Cout: " << t0Count << ", PackSize: " << packSize << ", SliceCount: " << sliceCount << endl;
			neutron.t0num = t0Count;
			hitT.t0num = t0Count;

			if (eventMapIdx != 0)
			{
				sliceCount = eventMapIdx - 1;
				//memset(eventMapT, 0, SLICESIZE*SIGNALSIZE*sizeof(uint32_t));
				//memset(eventMapT, 0, ((eventMapSlice[sliceCount]+1)*SIGNALSIZE)<<2);
				memset(eventMapC, 0, ((eventMapSlice[sliceCount] + 1)*SIGNALSIZE) << 1);
				memset(eventMapB, 0, ((eventMapSlice[sliceCount] + 1)*SIGNALSIZE) << 1);
				eventMapIdx = 0;
				memset(signalMapXM, 0, signalMapXIdx[sliceCount] << 1);
				memset(signalMapYM, 0, signalMapYIdx[sliceCount] << 1);
				//memset(signalMapXIdx, 0, sliceCount<<2);
				//memset(signalMapYIdx, 0, sliceCount<<2);
				matchIdx = 0;
			}

			scanSlice();
			if (PERSON_DEBUG) cout << "process all Slices " << eventMapIdx << endl;
			processMap();
			matchNeutronY();
		}
		m_Progress->SetPos(100*f0.tellg()/fileloop);
	}

	tree0->Write("t0", TObject::kOverwrite);
	tree1->Write("t1", TObject::kOverwrite);
	tree2->Write("t2", TObject::kOverwrite);
	tree3->Write("t3", TObject::kOverwrite);
	n2xy->Write();
	//hsx->Write();
	//hsy->Write();
	//npx->Write();
	npm->Write();
	for (int i = 0; i<SIGNALSIZE; i++) {
		hBase[i]->Write();
		hQ[i]->Write();
		hTOF[i]->Write();
	}
	f1->Close();

	output_message.Format(_T("final T0 number: %d, totalEvent: %d"),neutron.t0num, totalEvent);
	pCtrl->AddString(output_message);
	output_message.Format(_T("validEvent: %d, signal : %d"),validEvent, signalNum);
	pCtrl->AddString(output_message);
	output_message.Format(_T("ROOT file is constructed!"));
	pCtrl->AddString(output_message);
	free(buf);
	delete [] hBase;
	delete [] hQ;
	delete [] hTOF;
	delete eventMapT; //[SLICESIZE][SIGNALSIZE];
	delete eventMapC; //[SLICESIZE][SIGNALSIZE];
	delete eventMapB; //[SLICESIZE][SIGNALSIZE];
	delete eventMapSlice, eventMapMin, eventMapMax; //[0-SLICESIZE]
	delete sBuffer1, sBuffer2;
	delete signalMapXT, signalMapYT; // inordered tof record for each slice signal in X and Y
	delete signalMapXM, signalMapYM, signalMapXS, signalMapYS, signalMapXR, signalMapYR; // matchN, slice, range((strip_high<<8)|strip_low) for each tof from above record in X and Y 
	delete signalMapXIdx, signalMapYIdx; // end number of record for each slice signal in X and y
	delete matchX, matchY; // idx of matched Y for X

	f0.close();
}

void MWPCANA::scanSlice() {
	uint32_t *eventMapTS;
	uint16_t *eventMapCS, *eventMapBS;;
	uint32_t tof, value;
	uint16_t channel_ck, channel, base, Q, bareQ, minChannel, maxChannel;
	int sliceHead = 0, sliceIdx = 0;
	uint16_t slice_eventNumber = 0;
	while (f0.read((char*)&buf64, sizeof(uint64_t))) {
		swap64(&buf64);
		if ((buf64 >> 32) == 0xee1234ee || (buf64 & 0xffffffff) == 0xee1234ee) {
			f0.seekg(-8, ios::cur);
			sliceHead = -1;
			break;
		}

		else if (((buf64 >> 24) & 0xff) == 0xaa) {
			if (PERSON_DEBUG) cout << hex << "slice " << sliceHead << " th binary: " << setw(16) << setfill('0') << buf64 << endl;
			//if(cur_eventNumber!=0) {
			//	pre_tDataId = cur_tDataId;
			//	pre_eventNumber = cur_eventNumber;
			//	cur_eventNumber = 0;
			//}
			//cur_tDataId = buf64&0xffffff;
			cur_eventNumber = buf64 >> 32;
			totalEvent += cur_eventNumber;
			sliceHead++;
			if (slice_eventNumber != 0) {
				//if(eventMapCS[DEADCHANNEL-1]!=0 && eventMapCS[DEADCHANNEL+1]!=0) {
				//    eventMapCS[DEADCHANNEL] = (eventMapCS[DEADCHANNEL-1]+eventMapCS[DEADCHANNEL+1])>>1;
				//    eventMapTS[DEADCHANNEL] = (eventMapCS[DEADCHANNEL-1]>eventMapCS[DEADCHANNEL+1]) ? eventMapTS[DEADCHANNEL-1] : eventMapTS[DEADCHANNEL+1];
				//}
				eventMapSlice[eventMapIdx] = sliceIdx;
				eventMapMin[eventMapIdx] = minChannel;
				eventMapMax[eventMapIdx] = maxChannel;
				eventMapIdx++;
				validEvent += slice_eventNumber;
				slice_eventNumber = 0;
			}
			sliceIdx = buf64 & 0xffffff;
			eventMapTS = &eventMapT[SIGNALSIZE*sliceIdx];
			eventMapCS = &eventMapC[SIGNALSIZE*sliceIdx];
			eventMapBS = &eventMapB[SIGNALSIZE*sliceIdx];
			minChannel = SIGNALSIZE;
			maxChannel = 0;
		}
		else {
			if (PERSON_DEBUG) cout << hex << "event binary: " << setw(16) << setfill('0') << buf64 << endl;
			channel_ck = (buf64 >> 24) & 0xff;
			tof = buf64 & 0xffffff;
			value = buf64 >> 32;
			channel = (value >> 24);
			base = ((value >> 12) & 0xfff); // >>12+>>3, divide by 8
			Q = value & 0xfff;
			bareQ = Q - base;
			if (PERSON_DEBUG) cout << hex << "event: " << buf64 << ", ch: " << channel << ", base: " << base << ", Q: " << Q << ", bareQ: " << bareQ << ", tof: " << tof << ", sliceIdx: " << sliceIdx << ", t0Count: " << t0Count << endl;
			if (tof >= TOFRANGE1 && tof <= TOFRANGE2) {
				hBase[channel]->Fill(base);
				hQ[channel]->Fill(Q);
				hTOF[channel]->Fill(tof);
			}
			if (tof>TOFRANGE2) {
				if (1)
				{
					output_message.Format(_T("tof error! sliceIdx:%d, tof"), tof);
					pCtrl->AddString(output_message);
				}
				//continue;
			}
			if ((channel == channel_ck) && (bareQ >= QMIN) && (Q >= base)) {
				eventMapTS[channel] = tof;
				eventMapCS[channel] = Q;
				eventMapBS[channel] = base;
				slice_eventNumber++;
				if (channel<minChannel)
					minChannel = channel;
				if (channel>maxChannel)
					maxChannel = channel;

				channelX = channel;
				chargeX = Q - base;
				tree0->Fill();
			}
		}
	}

	if (slice_eventNumber != 0) {
		//if(eventMapCS[DEADCHANNEL-1]!=0 && eventMapCS[DEADCHANNEL+1]!=0) {
		//    eventMapCS[DEADCHANNEL] = (eventMapCS[DEADCHANNEL-1]+eventMapCS[DEADCHANNEL+1])>>1;
		//    eventMapTS[DEADCHANNEL] = (eventMapCS[DEADCHANNEL-1]>eventMapCS[DEADCHANNEL+1]) ? eventMapTS[DEADCHANNEL-1] : eventMapTS[DEADCHANNEL+1];
		//}
		eventMapSlice[eventMapIdx] = sliceIdx;
		eventMapMin[eventMapIdx] = minChannel;
		eventMapMax[eventMapIdx] = maxChannel;
		eventMapIdx++;
		validEvent += slice_eventNumber;
	}

	sampleT0++;
    //return sliceHead;
}

void MWPCANA::processMap() {
	int sliceNumber = eventMapIdx;
	if (PERSON_DEBUG) cout << "slice total number: " << sliceNumber << endl;

	if (sliceNumber == 0) {
		//pre_tDataId = 0;
		//cur_tDataId = 0;
		return;
	}
	sliceNumber--; // fast calc

	uint32_t *eventMapTS1, *eventMapTS2, *eventMapTS;
	uint16_t *eventMapCS1, *eventMapCS2, *eventMapBS1, *eventMapBS2;
	int wideLimit, sliceIdx1, sliceIdx2, pre_SigIdx, cur_SigIdx, dCH, signalIdx1, signalIdx2, center;
	uint32_t pre_TOF = 0, cur_TOF = 0, time, sxIdx = 0, syIdx = 0;
	uint16_t cQ, cB, cross1, cross2, minCh, maxCh;
	int dTOF = 0, sumQ;
	for (int idx = 0; idx<sliceNumber; idx++) {
		sliceIdx1 = eventMapSlice[idx];
		sliceIdx2 = eventMapSlice[idx + 1];//sliceIdx1+1;
		if (PERSON_DEBUG) cout << "process slice " << sliceIdx1 << ", next " << sliceIdx2 << endl;

		signalNum = 0;
		pre_TOF = 0, cur_TOF = 0, dTOF = 0;
		if ((sliceIdx1 + 1) == sliceIdx2) {
			eventMapTS1 = &eventMapT[sliceIdx1*SIGNALSIZE];
			eventMapTS2 = &eventMapT[sliceIdx2*SIGNALSIZE];
			eventMapCS1 = &eventMapC[sliceIdx1*SIGNALSIZE];
			eventMapCS2 = &eventMapC[sliceIdx2*SIGNALSIZE];
			eventMapBS1 = &eventMapB[sliceIdx1*SIGNALSIZE];
			eventMapBS2 = &eventMapB[sliceIdx2*SIGNALSIZE];

			pre_SigIdx = -1;
			cur_SigIdx = -1;
			signalIdx1 = -1;
			signalIdx2 = -1;
			minCh = (eventMapMin[idx] <= eventMapMin[idx + 1]) ? eventMapMin[idx] : eventMapMin[idx + 1];
			maxCh = (eventMapMax[idx] >= eventMapMax[idx + 1]) ? eventMapMax[idx] : eventMapMax[idx + 1];
			for (uint16_t cIdx = minCh; cIdx <= maxCh; cIdx++) {
				cQ = (eventMapCS1[cIdx] | eventMapCS2[cIdx]);
				cB = (eventMapBS1[cIdx] | eventMapBS2[cIdx]);
				if (((int)cQ - (int)cB)>QMAX) {
#ifdef FASTMATCH2
#else
					eventMapTS = eventMapCS1[cIdx] == 0 ? eventMapTS2 : eventMapTS1;
					pre_TOF = cur_TOF;
					cur_TOF = eventMapTS[cIdx];
#endif
					pre_SigIdx = cur_SigIdx;
					cur_SigIdx = cIdx;
					if (signalIdx1 == -1) {
						signalIdx1 = cur_SigIdx;
						signalIdx2 = cur_SigIdx;
						cross1 = eventMapCS1[cur_SigIdx];
						cross2 = eventMapCS2[cur_SigIdx];
						sBuffer1[0] = cQ;
						sBuffer2[0] = cB;
						sBufferIdx = 1;
						sumQ = cQ - cB;
					}
					if (PERSON_DEBUG) cout << "find one strip(>QMAX) in 2 slice: " << cIdx << ", tof: " << cur_TOF << ", Q: " << cQ << ", B: " << cB << ", corss: " << cross1 << "|" << cross2 << ". preIdx " << pre_SigIdx << endl;

					if (pre_SigIdx>0) {
#ifdef FASTMATCH2
#else
						dTOF = abs((int)cur_TOF - (int)pre_TOF);
#endif
						dCH = cur_SigIdx - pre_SigIdx;

						if (dTOF <= MATCHWINDOW && dCH <= STRIPGAP && (signalIdx1>XCHANNELNUM || cur_SigIdx <= XCHANNELNUM)) {
							signalIdx2 = cur_SigIdx;
							cross1 |= eventMapCS1[cur_SigIdx];
							cross2 |= eventMapCS2[cur_SigIdx];
							sBuffer1[sBufferIdx] = cQ;
							sBuffer2[sBufferIdx] = cB;
							sBufferIdx++;
							sumQ += cQ - cB;
						}
						else {
							if (cross1>0) {
								if (PERSON_DEBUG) cout << "find signal " << signalIdx1 << ", " << signalIdx2 << endl;
								//processSignal(sliceIdx1, signalIdx1, signalIdx2); // [signalIdx1, signalIdx2], record on next adjon slice will be swap
								wideLimit = (signalIdx1 <= XCHANNELNUM) ? WIDELIMITX : WIDELIMITY;
								if ((signalIdx1 + wideLimit - 1) <= signalIdx2) {
									center = (signalIdx1 + signalIdx2) >> 1;
									eventMapTS = eventMapCS1[center] == 0 ? eventMapTS2 : eventMapTS1;
									time = eventMapTS[center];
									if (center <= XCHANNELNUM) {
										if (sumQ >= QSUMX) {
											signalMapXT[sxIdx] = time;
											signalMapXS[sxIdx] = sliceIdx1;
											signalMapXR[sxIdx] = uint16_t((signalIdx2 << 8) | signalIdx1);
											if ((signalIdx2 - signalIdx1)>0 && PERSON_DEBUG) cout << "find Hit X " << sxIdx << "th with slice " << sliceIdx1 << " tof " << time << " range " << signalIdx1 << ", " << signalIdx2 << endl;
											//hsx->Fill(signalIdx2-signalIdx1+1);
											sxIdx++;
										}
									}
									else {
										if (sumQ >= QSUMY) {
											signalMapYT[syIdx] = time;
											signalMapYS[syIdx] = sliceIdx1;
											signalMapYR[syIdx] = uint16_t((signalIdx2 << 8) | signalIdx1);
											if (PERSON_DEBUG) cout << "find Hit Y " << syIdx << "th with slice " << sliceIdx1 << " tof " << time << " range " << signalIdx1 << ", " << signalIdx2 << endl;
											//hsy->Fill(signalIdx2-signalIdx1+1);
											syIdx++;
										}
									}
									//signalNum++;
									signalNum += signalIdx2 - signalIdx1 + 1;
									if (cross2 != 0) {
										memcpy(&eventMapCS1[signalIdx1], sBuffer1, sBufferIdx << 1);
										memcpy(&eventMapBS1[signalIdx1], sBuffer2, sBufferIdx << 1);
										memset(&eventMapCS2[signalIdx1], 0, sBufferIdx << 1);
										memset(&eventMapBS2[signalIdx1], 0, sBufferIdx << 1);
									}
									getHit(sliceIdx1, uint16_t((signalIdx2 << 8) | signalIdx1), hitT);
									hitT.tof = time;
									tree2->Fill();
								}
							}
							signalIdx1 = cur_SigIdx;
							signalIdx2 = cur_SigIdx;
							cross1 = eventMapCS1[cur_SigIdx];
							cross2 = eventMapCS2[cur_SigIdx];
							sBuffer1[0] = cQ;
							sBuffer2[0] = cB;
							sBufferIdx = 1;
							sumQ = cQ - cB;
						}
					}
				}
			}
			// last signal
			if (signalIdx1 != -1) {
				if (PERSON_DEBUG) cout << "find signal " << signalIdx1 << ", " << signalIdx2 << endl;
				if (cross1>0) {
					//processSignal(sliceIdx1, signalIdx1, signalIdx2); // [signalIdx1, signalIdx2]
					wideLimit = (signalIdx1 <= XCHANNELNUM) ? WIDELIMITX : WIDELIMITY;
					if ((signalIdx1 + wideLimit - 1) <= signalIdx2) {
						center = (signalIdx1 + signalIdx2) >> 1;
						eventMapTS = eventMapCS1[center] == 0 ? eventMapTS2 : eventMapTS1;
						time = eventMapTS[center];
						if (center <= XCHANNELNUM) {
							if (sumQ >= QSUMX) {
								signalMapXT[sxIdx] = time;
								signalMapXS[sxIdx] = sliceIdx1;
								signalMapXR[sxIdx] = uint16_t((signalIdx2 << 8) | signalIdx1);
								if ((signalIdx2 - signalIdx1)>0 && PERSON_DEBUG) cout << "find Hit X " << sxIdx << "th with slice " << sliceIdx1 << " tof " << time << " range " << signalIdx1 << ", " << signalIdx2 << endl;
								//hsx->Fill(signalIdx2-signalIdx1+1);
								sxIdx++;
							}
						}
						else {
							if (sumQ >= QSUMY) {
								signalMapYT[syIdx] = time;
								signalMapYS[syIdx] = sliceIdx1;
								signalMapYR[syIdx] = uint16_t((signalIdx2 << 8) | signalIdx1);
								if (PERSON_DEBUG) cout << "find Hit Y " << syIdx << "th with slice " << sliceIdx1 << " tof " << time << " range " << signalIdx1 << ", " << signalIdx2 << endl;
								//hsy->Fill(signalIdx2-signalIdx1+1);
								syIdx++;
							}
						}
						//signalNum++;
						signalNum += signalIdx2 - signalIdx1 + 1;
						if (cross2 != 0) {
							memcpy(&eventMapCS1[signalIdx1], sBuffer1, sBufferIdx << 1);
							memcpy(&eventMapBS1[signalIdx1], sBuffer2, sBufferIdx << 1);
							memset(&eventMapCS2[signalIdx1], 0, sBufferIdx << 1);
							memset(&eventMapBS2[signalIdx1], 0, sBufferIdx << 1);
						}
						getHit(sliceIdx1, uint16_t((signalIdx2 << 8) | signalIdx1), hitT);
						hitT.tof = time;
						tree2->Fill();
					}
				}
			}
		}
		else {
			// single slice
			pre_SigIdx = -1;
			cur_SigIdx = -1;
			signalIdx1 = -1;
			signalIdx2 = -1;
			eventMapCS1 = &eventMapC[sliceIdx1*SIGNALSIZE];
			eventMapTS1 = &eventMapT[sliceIdx1*SIGNALSIZE];
			eventMapBS1 = &eventMapB[sliceIdx1*SIGNALSIZE];
			minCh = eventMapMin[idx];
			maxCh = eventMapMax[idx];
			for (int cIdx = minCh; cIdx <= maxCh; cIdx++) {
				cQ = eventMapCS1[cIdx];
				cB = eventMapBS1[cIdx];
				if (((int)cQ - (int)cB)>QMAX) {
#ifdef FASTMATCH1
#else
					pre_TOF = cur_TOF;
					cur_TOF = eventMapTS1[cIdx];
#endif
					pre_SigIdx = cur_SigIdx;
					cur_SigIdx = cIdx;
					if (signalIdx1 == -1) {
						signalIdx1 = cur_SigIdx;
						signalIdx2 = cur_SigIdx;
						sumQ = cQ - cB;
					}
					if (PERSON_DEBUG) cout << "find one strip(>QMAX) in 1 slice: " << cIdx << ", tof: " << cur_TOF << ", Q: " << cQ << ", B: " << cB << ", corss: front" << endl;

					if (pre_SigIdx >= 0) {
#ifdef FASTMATCH1
#else
						dTOF = abs((int)cur_TOF - (int)pre_TOF);
#endif
						dCH = cur_SigIdx - pre_SigIdx;

						if (dTOF <= MATCHWINDOW && dCH <= STRIPGAP && (signalIdx1>XCHANNELNUM || cur_SigIdx <= XCHANNELNUM)) {
							signalIdx2 = cur_SigIdx;
							sumQ += cQ - cB;
						}
						else {
							if (PERSON_DEBUG) cout << "find signal " << signalIdx1 << ", " << signalIdx2 << endl;
							//processSignal(sliceIdx1, signalIdx1, signalIdx2); // [idx1, idx2]
							wideLimit = (signalIdx1 <= XCHANNELNUM) ? WIDELIMITX : WIDELIMITY;
							if ((signalIdx1 + wideLimit - 1) <= signalIdx2) {
								center = (signalIdx1 + signalIdx2) >> 1;
								time = eventMapTS1[center];
								if (center <= XCHANNELNUM) {
									if (sumQ >= QSUMX) {
										signalMapXT[sxIdx] = time;
										signalMapXS[sxIdx] = sliceIdx1;
										signalMapXR[sxIdx] = uint16_t((signalIdx2 << 8) | signalIdx1);
										if ((signalIdx2 - signalIdx1)>0 && PERSON_DEBUG) cout << "find Hit X " << sxIdx << "th with slice " << sliceIdx1 << " tof " << time << " range " << signalIdx1 << ", " << signalIdx2 << endl;
										//hsx->Fill(signalIdx2-signalIdx1+1);
										sxIdx++;
									}
								}
								else {
									if (sumQ >= QSUMY) {
										signalMapYT[syIdx] = time;
										signalMapYS[syIdx] = sliceIdx1;
										signalMapYR[syIdx] = uint16_t((signalIdx2 << 8) | signalIdx1);
										if (PERSON_DEBUG) cout << "find Hit Y " << syIdx << "th with slice " << sliceIdx1 << " tof " << time << " range " << signalIdx1 << ", " << signalIdx2 << endl;
										//hsy->Fill(signalIdx2-signalIdx1+1);
										syIdx++;
									}
								}
								//signalNum++;
								signalNum += signalIdx2 - signalIdx1 + 1;
								getHit(sliceIdx1, uint16_t((signalIdx2 << 8) | signalIdx1), hitT);
								hitT.tof = time;
								tree2->Fill();
							}
							signalIdx1 = cur_SigIdx;
							signalIdx2 = cur_SigIdx;
							sumQ = cQ - cB;
						}
			}
		}
	}
			// last signal
			if (signalIdx1 != -1) {
				if (PERSON_DEBUG) cout << "find signal " << signalIdx1 << ", " << signalIdx2 << endl;
				//processSignal(sliceIdx1, signalIdx1, signalIdx2); // [signalIdx1, signalIdx2]
				wideLimit = (signalIdx1 <= XCHANNELNUM) ? WIDELIMITX : WIDELIMITY;
				if ((signalIdx1 + wideLimit - 1) <= signalIdx2) {
					center = (signalIdx1 + signalIdx2) >> 1;
					time = eventMapTS1[center];
					if (center <= XCHANNELNUM) {
						if (sumQ >= QSUMX) {
							signalMapXT[sxIdx] = time;
							signalMapXS[sxIdx] = sliceIdx1;
							signalMapXR[sxIdx] = uint16_t((signalIdx2 << 8) | signalIdx1);
							if ((signalIdx2 - signalIdx1)>0 && PERSON_DEBUG) cout << "find Hit X " << sxIdx << "th with slice " << sliceIdx1 << " tof " << time << " range " << signalIdx1 << ", " << signalIdx2 << endl;
							//hsx->Fill(signalIdx2-signalIdx1+1);
							sxIdx++;
						}
					}
					else {
						if (sumQ >= QSUMY) {
							signalMapYT[syIdx] = time;
							signalMapYS[syIdx] = sliceIdx1;
							signalMapYR[syIdx] = uint16_t((signalIdx2 << 8) | signalIdx1);
							if (PERSON_DEBUG) cout << "find Hit Y " << syIdx << "th with slice " << sliceIdx1 << " tof " << time << " range " << signalIdx1 << ", " << signalIdx2 << endl;
							//hsy->Fill(signalIdx2-signalIdx1+1);
							syIdx++;
						}
					}
					//signalNum++;
					signalNum += signalIdx2 - signalIdx1 + 1;
					getHit(sliceIdx1, uint16_t((signalIdx2 << 8) | signalIdx1), hitT);
					hitT.tof = time;
					tree2->Fill();
				}
			}
}
		signalMapXIdx[idx] = sxIdx;
		signalMapYIdx[idx] = syIdx;
		if (PERSON_DEBUG && (idx>1)) cout << dec << "slice " << sliceIdx1 << " accumulate signalX " << sxIdx - signalMapXIdx[idx - 1] << ", signalY " << syIdx - signalMapYIdx[idx - 1] << endl;
	}

	// last slice
	signalNum = 0;
	pre_TOF = 0, cur_TOF = 0, dTOF = 0;
	pre_SigIdx = -1;
	cur_SigIdx = -1;
	signalIdx1 = -1;
	signalIdx2 = -1;
	sliceIdx1 = eventMapSlice[sliceNumber];
	eventMapCS1 = &eventMapC[sliceIdx1*SIGNALSIZE];
	eventMapTS1 = &eventMapT[sliceIdx1*SIGNALSIZE];
	eventMapBS1 = &eventMapB[sliceIdx1*SIGNALSIZE];
	minCh = eventMapMin[sliceNumber];
	maxCh = eventMapMax[sliceNumber];
	for (int cIdx = minCh; cIdx <= maxCh; cIdx++) {
		cQ = eventMapCS1[cIdx];
		cB = eventMapBS1[cIdx];
		if (((int)cQ - (int)cB)>QMAX) {
#ifdef FASTMATCH1
#else
			pre_TOF = cur_TOF;
			cur_TOF = eventMapTS1[cIdx];
#endif
			pre_SigIdx = cur_SigIdx;
			cur_SigIdx = cIdx;
			if (signalIdx1 == -1) {
				signalIdx1 = cur_SigIdx;
				signalIdx2 = cur_SigIdx;
				sumQ = cQ - cB;
			}
			if (PERSON_DEBUG) cout << "find one strip(>QMAX) in last slice: " << cIdx << ", tof: " << cur_TOF << ", Q: " << cQ << ", B: " << cB << ", corss: front" << endl;

			if (pre_SigIdx>0) {
#ifdef FASTMATCH1
#else
				dTOF = abs((int)cur_TOF - (int)pre_TOF);
#endif
				dCH = cur_SigIdx - pre_SigIdx;

				if (dTOF <= MATCHWINDOW && dCH <= STRIPGAP && (signalIdx1>XCHANNELNUM || cur_SigIdx <= XCHANNELNUM)) {
					signalIdx2 = cur_SigIdx;
					sumQ += cQ - cB;
				}
				else {
					if (PERSON_DEBUG) cout << "find signal " << signalIdx1 << ", " << signalIdx2 << endl;
					//processSignal(sliceIdx1, signalIdx1, signalIdx2); // [idx1, idx2]
					wideLimit = (signalIdx1 <= XCHANNELNUM) ? WIDELIMITX : WIDELIMITY;
					if ((signalIdx1 + wideLimit - 1) <= signalIdx2) {
						center = (signalIdx1 + signalIdx2) >> 1;
						time = eventMapTS1[center];
						if (center <= XCHANNELNUM) {
							if (sumQ >= QSUMX) {
								signalMapXT[sxIdx] = time;
								signalMapXS[sxIdx] = sliceIdx1;
								signalMapXR[sxIdx] = uint16_t((signalIdx2 << 8) | signalIdx1);
								if ((signalIdx2 - signalIdx1)>0 && PERSON_DEBUG) cout << "find Hit X " << sxIdx << "th with slice " << sliceIdx1 << " tof " << time << " range " << signalIdx1 << ", " << signalIdx2 << endl;
								//hsx->Fill(signalIdx2-signalIdx1+1);
								sxIdx++;
							}
						}
						else {
							if (sumQ >= QSUMY) {
								signalMapYT[syIdx] = time;
								signalMapYS[syIdx] = sliceIdx1;
								signalMapYR[syIdx] = uint16_t((signalIdx2 << 8) | signalIdx1);
								if (PERSON_DEBUG) cout << "find Hit Y " << syIdx << "th with slice " << sliceIdx1 << " tof " << time << " range " << signalIdx1 << ", " << signalIdx2 << endl;
								//hsy->Fill(signalIdx2-signalIdx1+1);
								syIdx++;
							}
						}
						//signalNum++;
						signalNum += signalIdx2 - signalIdx1 + 1;
						getHit(sliceIdx1, uint16_t((signalIdx2 << 8) | signalIdx1), hitT);
						hitT.tof = time;
						tree2->Fill();
					}
					signalIdx1 = cur_SigIdx;
					signalIdx2 = cur_SigIdx;
					sumQ = cQ - cB;
				}
			}
	}
	}
	// last signal
	if (signalIdx1 != -1) {
		if (PERSON_DEBUG) cout << "find signal " << signalIdx1 << ", " << signalIdx2 << endl;
		//processSignal(sliceIdx1, signalIdx1, signalIdx2); // [signalIdx1, signalIdx2]
		wideLimit = (signalIdx1 <= XCHANNELNUM) ? WIDELIMITX : WIDELIMITY;
		if ((signalIdx1 + wideLimit - 1) <= signalIdx2) {
			center = (signalIdx1 + signalIdx2) >> 1;
			time = eventMapTS1[center];
			if (center <= XCHANNELNUM) {
				if (sumQ >= QSUMX) {
					signalMapXT[sxIdx] = time;
					signalMapXS[sxIdx] = sliceIdx1;
					signalMapXR[sxIdx] = uint16_t((signalIdx2 << 8) | signalIdx1);
					if ((signalIdx2 - signalIdx1)>0 && PERSON_DEBUG) cout << "find Hit X " << sxIdx << "th with slice " << sliceIdx1 << " tof " << time << " range " << signalIdx1 << ", " << signalIdx2 << endl;
					//hsx->Fill(signalIdx2-signalIdx1+1);
					sxIdx++;
				}
			}
			else {
				if (sumQ >= QSUMY) {
					signalMapYT[syIdx] = time;
					signalMapYS[syIdx] = sliceIdx1;
					signalMapYR[syIdx] = uint16_t((signalIdx2 << 8) | signalIdx1);
					if (PERSON_DEBUG) cout << "find Hit Y " << syIdx << "th with slice " << sliceIdx1 << " tof " << time << " range " << signalIdx1 << ", " << signalIdx2 << endl;
					//hsy->Fill(signalIdx2-signalIdx1+1);
					syIdx++;
				}
			}
			//signalNum++;
			signalNum += signalIdx2 - signalIdx1 + 1;
			getHit(sliceIdx1, uint16_t((signalIdx2 << 8) | signalIdx1), hitT);
			hitT.tof = time;
			tree2->Fill();
		}
	}
	signalMapXIdx[sliceNumber] = sxIdx;
	signalMapYIdx[sliceNumber] = syIdx;
	if (PERSON_DEBUG) cout << dec << "last slice " << sliceIdx1 << " accumulate signalX " << sxIdx - signalMapXIdx[sliceNumber - 1] << ", signalY " << syIdx - signalMapYIdx[sliceNumber - 1] << endl;

	if (PERSON_DEBUG) cout << "processMap end." << endl;
}

void MWPCANA::matchNeutronX() {
	int dT1, dT2, tx, ty, sliceIdx, sliceNumber = eventMapIdx;
	uint32_t xStart = 0, xEnd = 0, yStart = 0, yEnd = 0, yStartM, yEndM;
	int i, j, m[100], preIdx, aftIdx;
	matchIdx = 0;
	for (int idx = 0; idx<eventMapIdx; idx++) {
		sliceIdx = eventMapSlice[idx];
		xStart = xEnd;
		xEnd = signalMapXIdx[idx];

		//if(MATCHWINDOW>=32 && (yEnd-yStart)>1)
		//    continue;

		preIdx = idx - 1;
		aftIdx = idx + 1;

		preIdx--;
		yStartM = (preIdx >= 0) ? signalMapYIdx[preIdx] : 0;
		while (preIdx >= 0 && ((sliceIdx - eventMapSlice[preIdx]) << 5) <= MATCHWINDOW) {
			preIdx--;
			yStartM = (preIdx >= 0) ? signalMapYIdx[preIdx] : 0; // signalMapYIdx[idx] store the size of signalY after the end of eventMapSlice[idx]
		}
		yEndM = (aftIdx<sliceNumber) ? signalMapYIdx[aftIdx] : signalMapYIdx[sliceNumber - 1];
		while (aftIdx<sliceNumber && ((eventMapSlice[aftIdx] - sliceNumber) << 5) <= MATCHWINDOW) {
			aftIdx++;
			yEndM = (aftIdx<sliceNumber) ? signalMapYIdx[aftIdx] : signalMapYIdx[sliceNumber - 1];
		}

		if (PERSON_DEBUG) cout << "matching slice " << sliceIdx << endl;
		for (i = xStart; i<xEnd; i++) {
			tx = signalMapXT[i];
			dT1 = 500;
			dT2 = 500;
			multiHitSize = 0;
			for (j = yStartM; j<yEndM; j++) {
				ty = signalMapYT[j];
				getHit(signalMapYS[j], signalMapYR[j], hitT);
				hitT.tof = ty;

				if (abs(ty - tx)<abs(dT1)) {
					dT2 = dT1;
					dT1 = ty - tx;
				}
				else {
					if (abs(ty - tx)<abs(dT2)) {
						dT2 = ty - tx;
					}
				}

				if (abs(ty - tx) <= MATCHWINDOW) {
					if (PERSON_DEBUG) cout << "pre-match1 X-" << i << " tof " << tx << ", Y-" << j << " tof " << signalMapYT[j] << endl;
					signalMapXM[i]++;
					signalMapYM[j]++;
					m[multiHitSize] = j;
					multiHits[multiHitSize] = hitT;
					multiHitSize++;
				}
			}
			if (PERSON_DEBUG) cout << dec << "scan match X-" << i << " tof " << tx << " to Ys " << yStartM << ", " << yEndM << ", ms " << signalMapXM[i] << endl;
			if (signalMapXM[i] >= 1) {
				matchX[matchIdx] = i;
				for (int mIdx = 0; mIdx<multiHitSize; mIdx++) {
					//matchY[matchIdx][mIdx] = m[mIdx];
					int s1 = multiHits[mIdx].strip1st;
					int s2 = multiHits[mIdx].strip1st + multiHits[mIdx].nstrip - 1;
					if (PERSON_DEBUG) cout << "pre-match2 X-" << i << " tof " << tx << ", Y-" << m[mIdx] << " tof " << signalMapYT[m[mIdx]] << endl;
					//for(int sIdx=s1; sIdx<=s2; sIdx++)
					//npm->Fill(sIdx);
				}
				matchY[matchIdx] = m[0];
				matchIdx++;
				hitY.center = multiHits[0].center;
			}
			else {
				hitY.center = -1;
			}
			getHit(signalMapXS[i], signalMapXR[i], hitT);
			hitT.tof = tx;
			hitT.dT1 = dT1;
			hitT.dT2 = dT2;
			hitT.match = signalMapXM[i];
			tree3->Fill();
		}
	}

	int bm, nm;
	uint32_t xIdx, yIdx, tn = 0;
	uint16_t sliceX, sliceY, rangeX, rangeY;
	float wavelength;
	for (int mIdx = 0; mIdx<matchIdx; mIdx++) {
		xIdx = matchX[mIdx];
		yIdx = matchY[mIdx];
		if (PERSON_DEBUG) cout << "checking " << mIdx << "th neutron with xIdx " << xIdx << " and yIdx " << yIdx << ", Y tof " << signalMapYT[yIdx] << " match number " << signalMapYM[yIdx] << endl;
		if (signalMapYM[yIdx] >= 1) {
			hitX.tof = signalMapXT[xIdx];
			hitY.tof = signalMapYT[yIdx];
			sliceX = signalMapXS[xIdx];
			sliceY = signalMapYS[yIdx];
			rangeX = signalMapXR[xIdx];
			rangeY = signalMapYR[yIdx];
			getHit(sliceX, rangeX, hitX);
			getHit(sliceY, rangeY, hitY);
			if (PERSON_DEBUG) cout << dec << "neutron X range: " << ((rangeX >> 8) & 0xff) << ", " << (rangeX & 0xff) << ", slice: " << sliceX << ", center: " << hitX.center << ", Y range: " << ((rangeY >> 8) & 0xff) << ", " << (rangeY & 0xff) << ", slice: " << sliceY << ", center: " << hitY.center << endl;
			//neutron.x = hitX.center;
			//neutron.y = hitY.center - (float)XCHANNELNUM;
			neutron.x = (hitY.center - (float)XCHANNELNUM);//*2.2;
			neutron.y = ((float)XCHANNELNUM - hitX.center);//*4.0;
			neutron.t = (hitX.tof + hitY.tof) >> 1;
			neutron.ty = hitX.tof;
			neutron.tx = hitY.tof;
			neutron.nsy = hitX.nstrip;
			neutron.nsx = hitY.nstrip;
			neutron.chargey = hitX.charge;
			neutron.chargex = hitY.charge;
			neutron.qsum = hitX.charge + hitY.charge;
			neutron.qy = hitX.qstrip[int(hitX.nstrip / 2)];
			neutron.qx = hitY.qstrip[int(hitY.nstrip / 2)];
			neutron.basey = hitX.bstrip[int(hitX.nstrip / 2)];
			neutron.basex = hitY.bstrip[int(hitY.nstrip / 2)];
			neutron.dqx = hitY.dQ;
			neutron.dT = hitY.tof - hitX.tof;
			neutron.matchx = signalMapYM[yIdx];
			neutron.matchy = signalMapXM[xIdx];
			//lamda=tof/(252.778*tofLength)  us,m,A
			neutron.wl = float(neutron.t) / (40 * 252.778*14.9);
			tree1->Fill();
			n2xy->Fill(neutron.x, neutron.y);
			//npx->Fill(neutron.x);
			//bm = npx->FindBin(neutron.x);
			//nm = neutron.nsx;
			//if(bm==1640||bm==1641||bm==1639) {
			//if(bm-1624==0||bm-1624==1||bm-1624==-1) {
			//if(bm==1433||bm==1434||bm==1435) {
			//if(bm==1674||bm==1673) {
			//    npm->Fill(neutron.x);
			//    if(PERSON_DEBUG) cout << "hit in bin " << bm << " with ns " << nm << ", pos " << neutron.x << ", T0 " << neutron.t0num << ", tof " << hitY.tof << ", matchIdx " << yIdx << endl;
			//    for(int j=0; j<nm; j++) {
			//        if(PERSON_DEBUG) cout << "strip " << j+hitY.strip1st << ",Q " << hitY.qstrip[j] << ", base " << hitY.bstrip[j] << ", charge(Q-B) " << hitY.cstrip[j] << ", T0 " << neutron.t << ", TOF " << hitY.tstrip[j] << endl;
			//    }
			//}
			tn++;
			if (PERSON_DEBUG) cout << hex << "find neutron: " << neutron.x << ", " << neutron.y << ", " << neutron.t << endl;
			if (PERSON_DEBUG) cout << dec << "find neutron: " << setprecision(3) << neutron.x / 2.2 << " in binY " << n2xy->GetYaxis()->FindBin(neutron.x) << ", " << neutron.y / 4.0 << " in binX " << n2xy->GetXaxis()->FindBin(neutron.y) << endl;
		}
	}
	if (PERSON_DEBUG) cout << dec << "T0 num " << neutron.t0num << ", validEvent " << validEvent << ", candidate hitX " << matchIdx << ", match neutron " << tn << endl;
}

void MWPCANA::matchNeutronY() {
	int dT1, dT2, tx, ty, sliceIdx, sliceNumber = eventMapIdx;
	uint32_t xStart = 0, xEnd = 0, yStart = 0, yEnd = 0, yStartM, yEndM;
	int i, j, m[100], preIdx, aftIdx;
	matchIdx = 0;
	for (int idx = 0; idx<eventMapIdx; idx++) {
		sliceIdx = eventMapSlice[idx];
		xStart = xEnd;
		xEnd = signalMapYIdx[idx];

		//if(MATCHWINDOW>=32 && (yEnd-yStart)>1)
		//    continue;

		preIdx = idx - 1;
		aftIdx = idx + 1;

		preIdx--;
		yStartM = (preIdx >= 0) ? signalMapXIdx[preIdx] : 0;
		while (preIdx >= 0 && ((sliceIdx - eventMapSlice[preIdx]) << 5) <= MATCHWINDOW) {
			preIdx--;
			yStartM = (preIdx >= 0) ? signalMapXIdx[preIdx] : 0; // signalMapXIdx[idx] store the size of signalY after the end of eventMapSlice[idx]
		}
		yEndM = (aftIdx<sliceNumber) ? signalMapXIdx[aftIdx] : signalMapXIdx[sliceNumber - 1];
		while (aftIdx<sliceNumber && ((eventMapSlice[aftIdx] - sliceNumber) << 5) <= MATCHWINDOW) {
			aftIdx++;
			yEndM = (aftIdx<sliceNumber) ? signalMapXIdx[aftIdx] : signalMapXIdx[sliceNumber - 1];
		}

		if (PERSON_DEBUG) cout << "matching slice " << sliceIdx << endl;
		for (i = xStart; i<xEnd; i++) {
			tx = signalMapYT[i];
			dT1 = 500;
			dT2 = 500;
			multiHitSize = 0;
			for (j = yStartM; j<yEndM; j++) {
				ty = signalMapXT[j];
				getHit(signalMapXS[j], signalMapXR[j], hitT);
				hitT.tof = ty;

				if (abs(ty - tx)<abs(dT1)) {
					dT2 = dT1;
					dT1 = ty - tx;
				}
				else {
					if (abs(ty - tx)<abs(dT2)) {
						dT2 = ty - tx;
					}
				}

				if (abs(ty - tx) <= MATCHWINDOW) {
					if (PERSON_DEBUG) cout << "pre-match1 Y-" << i << " tof " << tx << ", X-" << j << " tof " << signalMapXT[j] << endl;
					signalMapYM[i]++;
					signalMapXM[j]++;
					m[multiHitSize] = j;
					multiHits[multiHitSize] = hitT;
					multiHitSize++;
				}
			}
			if (PERSON_DEBUG) cout << dec << "scan match Y-" << i << " tof " << tx << " to Xs " << yStartM << ", " << yEndM << ", ms " << signalMapYM[i] << endl;
			if (signalMapYM[i] >= 1) {
				matchY[matchIdx] = i;
				for (int mIdx = 0; mIdx<multiHitSize; mIdx++) {
					//matchY[matchIdx][mIdx] = m[mIdx];
					int s1 = multiHits[mIdx].strip1st;
					int s2 = multiHits[mIdx].strip1st + multiHits[mIdx].nstrip - 1;
					if (PERSON_DEBUG) cout << "pre-match2 Y-" << i << " tof " << tx << ", X-" << m[mIdx] << " tof " << signalMapXT[m[mIdx]] << endl;
					//for(int sIdx=s1; sIdx<=s2; sIdx++)
					//npm->Fill(sIdx);
				}
				matchX[matchIdx] = m[0];
				matchIdx++;
				hitY.center = multiHits[0].center;
			}
			else {
				hitY.center = -1;
			}
			getHit(signalMapYS[i], signalMapYR[i], hitT);
			hitT.tof = tx;
			hitT.dT1 = dT1;
			hitT.dT2 = dT2;
			hitT.match = signalMapYM[i];
			tree3->Fill();
		}
	}

	int bm, nm;
	uint32_t xIdx, yIdx, tn = 0;
	uint16_t sliceX, sliceY, rangeX, rangeY;
	float wavelength;
	for (int mIdx = 0; mIdx<matchIdx; mIdx++) {
		xIdx = matchX[mIdx];
		yIdx = matchY[mIdx];
		if (PERSON_DEBUG) cout << "checking " << mIdx << "th neutron with xIdx " << xIdx << " and yIdx " << yIdx << ", Y tof " << signalMapYT[yIdx] << " match number " << signalMapYM[yIdx] << endl;
		if (signalMapXM[yIdx] >= 1) {
			hitX.tof = signalMapXT[xIdx];
			hitY.tof = signalMapYT[yIdx];
			sliceX = signalMapXS[xIdx];
			sliceY = signalMapYS[yIdx];
			rangeX = signalMapXR[xIdx];
			rangeY = signalMapYR[yIdx];
			getHit(sliceX, rangeX, hitX);
			getHit(sliceY, rangeY, hitY);
			if (PERSON_DEBUG) cout << dec << "neutron X range: " << ((rangeX >> 8) & 0xff) << ", " << (rangeX & 0xff) << ", slice: " << sliceX << ", center: " << hitX.center << ", Y range: " << ((rangeY >> 8) & 0xff) << ", " << (rangeY & 0xff) << ", slice: " << sliceY << ", center: " << hitY.center << endl;
			//neutron.x = hitX.center;
			//neutron.y = hitY.center - (float)XCHANNELNUM;
			neutron.x = (hitY.center - (float)XCHANNELNUM);//*2.2;
			neutron.y = ((float)XCHANNELNUM - hitX.center);//*4.0;
			neutron.t = (hitX.tof + hitY.tof) >> 1;
			neutron.ty = hitX.tof;
			neutron.tx = hitY.tof;
			neutron.nsy = hitX.nstrip;
			neutron.nsx = hitY.nstrip;
			neutron.chargey = hitX.charge;
			neutron.chargex = hitY.charge;
			neutron.qsum = hitX.charge + hitY.charge;
			neutron.qy = hitX.qstrip[int(hitX.nstrip / 2)];
			neutron.qx = hitY.qstrip[int(hitY.nstrip / 2)];
			neutron.basey = hitX.bstrip[int(hitX.nstrip / 2)];
			neutron.basex = hitY.bstrip[int(hitY.nstrip / 2)];
			neutron.dqx = hitY.dQ;
			neutron.dT = hitY.tof - hitX.tof;
			neutron.matchx = signalMapYM[yIdx];
			neutron.matchy = signalMapXM[xIdx];
			//lamda=tof/(252.778*tofLength)  us,m,A
			neutron.wl = float(neutron.t) / (40 * 252.778*14.9);
			tree1->Fill();
			n2xy->Fill(neutron.x, neutron.y);
			//npx->Fill(neutron.x);
			//bm = npx->FindBin(neutron.x);
			//nm = neutron.nsx;
			//if(bm==1640||bm==1641||bm==1639) {
			//if(bm-1624==0||bm-1624==1||bm-1624==-1) {
			//if(bm==1433||bm==1434||bm==1435) {
			//if(bm==1674||bm==1673) {
			//    npm->Fill(neutron.x);
			//    if(PERSON_DEBUG) cout << "hit in bin " << bm << " with ns " << nm << ", pos " << neutron.x << ", T0 " << neutron.t0num << ", tof " << hitY.tof << ", matchIdx " << yIdx << endl;
			//    for(int j=0; j<nm; j++) {
			//        if(PERSON_DEBUG) cout << "strip " << j+hitY.strip1st << ",Q " << hitY.qstrip[j] << ", base " << hitY.bstrip[j] << ", charge(Q-B) " << hitY.cstrip[j] << ", T0 " << neutron.t << ", TOF " << hitY.tstrip[j] << endl;
			//    }
			//}
			tn++;
			if (PERSON_DEBUG) cout << hex << "find neutron: " << neutron.x << ", " << neutron.y << ", " << neutron.t << endl;
			if (PERSON_DEBUG) cout << dec << "find neutron: " << setprecision(3) << neutron.x / 2.2 << " in binY " << n2xy->GetYaxis()->FindBin(neutron.x) << ", " << neutron.y / 4.0 << " in binX " << n2xy->GetXaxis()->FindBin(neutron.y) << endl;
		}
	}
	if (PERSON_DEBUG) cout << dec << "T0 num " << neutron.t0num << ", validEvent " << validEvent << ", candidate hitX " << matchIdx << ", match neutron " << tn << endl;
}


MWPCANA::~MWPCANA()
{
}
