// He3MWPC.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1F.h"
#include <vector>
#define max_len 5000
void readdata(char*input);
void tran(char*input);
int main()
{
	char input[20];
	std::cout << "please input the binary file name(without'.dat'):";
	cin >> input;
	readdata(input);
	tran(input);
    return 0;
}

void readdata(char*input)
{
#define pick 1
	int data_length;
	unsigned char tag;
	bool data_flag = false;
	unsigned int adc;
	char filename[100];
	char rootname[100];
	char dsuffix[10] = ".dat";
	char rsuffix[10] = ".root";
	unsigned int data_bulk[max_len];
	unsigned int trigger;
	unsigned int T[max_len];
	float Q[max_len];
	float base[max_len];
	unsigned int ch[max_len];

	for (int dataloop = 1; dataloop<7; dataloop++)
	{
		int tmp_tr = 0xffffffff;
		//initial data file
		sprintf(filename, "BL04_RUN1_MODULE01_FILE%d_", dataloop);
		strcat(filename, input);
		strcpy(rootname, filename);
		strcat(filename, dsuffix);
		ifstream f(filename, ifstream::binary);
		if (f.is_open())
		{
			//initial root file
			strcat(rootname, rsuffix);
			cout << "Processing " << filename << endl;
			TFile * rootf = new TFile(rootname, "RECREATE");
			TTree*t = new TTree("bank", "the data be stored");
			t->Branch("data_length", &data_length, "data_length/I");
			t->Branch("T", &T, "T[data_length]/i");
			t->Branch("Q", &Q, "Q[data_length]/F");
			t->Branch("base", &base, "base[data_length]/F");
			t->Branch("ch", &ch, "ch[data_length]/i");
			t->Branch("trigger", &trigger, "trigger/i");

			TH1F*h1 = new TH1F("bigdata", "the big data distribution", 500, 0, 500);
			int count = 0;
			time_t start;
			time(&start);
			data_flag = true;
			ofstream outf("out.txt", std::ofstream::out | std::ofstream::app);
			while (f.good())
			{
				f.read((char*)&tag, 1);
				if (tag == 0xFA)
				{
					//data_flag=false;
					f.read((char*)&data_bulk, 7);
					f.read((char*)&data_length, 4);
					data_length = int((data_length << 24) & 0xff000000) + int((data_length << 8) & 0xff0000) + int((data_length >> 8) & 0xff00) + int((data_length >> 24) & 0xff);
					f.read((char*)&trigger, 4);
					trigger = int((trigger << 24) & 0xff000000) + int((trigger << 8) & 0xff0000) + int((trigger >> 8) & 0xff00) + int((trigger >> 24) & 0xff);
					if (trigger == 1)
					{
						if (tmp_tr != 0xffffffff)
						{
							cout << "Trigger ERROR! in " << trigger << endl;
							cout << "It happen in " << hex << f.tellg() << " !" << endl;
						}
					}
					else if (tmp_tr != (trigger - 1))
					{
						cout << "Trigger ERROR! in " << trigger << endl;
						cout << "It happen in " << hex << f.tellg() << " !" << endl;
					}
					tmp_tr = trigger;
					//cout<<data_length<<endl;
#ifdef pick
					if (data_length>192000)
					{
						cout << "The Big Data in " << hex << f.tellg() << " !" << endl;
						cout << "data length is: " << dec << data_length << endl;
						outf << "1\t" << trigger << endl;
						f.seekg(data_length - 16, ios::cur);
						cout << "Tht pointer jump to: " << hex << f.tellg() << endl;
						data_length = (data_length - 24) / 8;
						data_length /= 48;
						h1->Fill(data_length);
					}
					else
#endif
					{
						f.read((char*)&data_bulk, data_length - 16);
						data_length = (data_length - 24) / 8;
#ifdef pick
						/*if(data_length%24)
						{
						cout<<"not a whole data! at: "<<hex<<f.tellg()<<" in trigger: "<<trigger<<" !"<<endl;
						cout<<"The data length is: "<<dec<<data_length<<endl;
						outf<<"2\t"<<trigger<<endl;
						data_flag=false;
						}*/
#endif
						for (int i = 0; i<data_length; i++)
						{
							data_flag = true;
							adc = *(data_bulk + i * 2);
							ch[i] = int(adc & 0xff);
							//cout<<ch[i]<<endl;
							T[i] = int((adc << 8) & 0xff0000) + int((adc >> 8) & 0xff00) + int((adc >> 24) & 0xff);
							adc = *(data_bulk + 1 + i * 2);
#ifdef pick
							if (ch[i] != int(adc & 0xff))
							{
								cout << "Ch Error in " << hex << f.tellg() << " !" << endl;
								cout << "T ch: " << ch[i] << " E ch: " << int(adc & 0xff) << endl;
								cout << dec << data_length << endl;
								data_flag = false;
							}
							else
#endif
							{
								adc = int((adc >> 24) & 0xff) + int((adc << 8) & 0xff0000) + int((adc >> 8) & 0xff00);
								base[i] = int((adc >> 12) & 0xfff);
								base[i] /= 8;
								Q[i] = int(adc & 0xfff) - base[i];
							}
						}
						t->Fill();
						count++;
						data_length /= 48;
						h1->Fill(data_length);
					}

				}
				else
				{
					//cout << "Error in End!" << endl;
					//break;
				}
			}
			cout << "the last trigger: " << trigger << endl;
			time_t stop;
			time(&stop);
			double timelast = difftime(stop, start);
			cout << "there are " << count << " event recorded!" << endl;
			cout << "cost " << timelast << " second." << endl;
			f.close();
			outf.close();
			t->Write();
			h1->Write();
			rootf->Close();
		}
		else
		{
			cout << "Error opening file!\n";
			break;
		}
	}
	return;
}

void tran(char*input)
{
	unsigned int time_d = 25;

	char rootname[6][100];
	char outname[30];
	char rsuffix[10] = ".root";
	time_t start;
	time(&start);
	std::cout << "start transfer root!...\n";
	strcpy(outname, input);
	strcat(outname, rsuffix);
	for (int i = 1; i < 7; i++)
	{
		sprintf(rootname[i - 1], "BL04_RUN1_MODULE01_FILE%d_", i);
		strcat(rootname[i - 1], input);
		strcat(rootname[i - 1], rsuffix);
		std::cout << "Linking the File \"" << rootname[i - 1] << "\" ..." << endl;
	}
	TFile*datainput[6];
	TTree*bank[6];
	for (int i = 0; i < 6; i++)
	{
		datainput[i] = new TFile(rootname[i]);
		bank[i] = (TTree*)datainput[i]->Get("bank");
	}

	int loop_flag = 0;

	int data_length[6];
	unsigned int trigger[6];
	unsigned int T[6][max_len];
	float Q[6][max_len];
	float base[6][max_len];
	unsigned int ch[6][max_len];
	for (int i = 0; i < 6; i++)
	{
		bank[i]->SetBranchAddress("data_length", &data_length[i]);
		bank[i]->SetBranchAddress("trigger", &trigger[i]);
		bank[i]->SetBranchAddress("T", &T[i]);
		bank[i]->SetBranchAddress("Q", &Q[i]);
		bank[i]->SetBranchAddress("base", &base[i]);
		bank[i]->SetBranchAddress("ch", &ch[i]);
	}

	for (int i = 0; i < 6; i++)
	{
		if (loop_flag) loop_flag = loop_flag < bank[i]->GetEntries() ? loop_flag : bank[i]->GetEntries();
		else loop_flag = bank[i]->GetEntries();
	}
	//std::cout << "The mini data is: " << loop_flag << endl;
	float Qt[144];
	float Pedestal[144];
	float Qx[50];
	float Qy[94];

	unsigned int T_date;
	TFile * rootf = new TFile(outname, "RECREATE");
	TTree * t = new TTree("tran", "data translation");
	t->Branch("Qx", &Qx, "Qx[50]/F");
	t->Branch("Qy", &Qy, "Qy[94]/F");
	t->Branch("Pedestal", &Pedestal, "Pedestal[144]/F");
	t->Branch("T_date", &T_date, "T_date/i");
	t->Branch("trigger", &trigger, "trigger/i");
	TH1F *h1 = new TH1F("Event", "Events Number in every Trigger", 100, 0, 200);
	std::vector<unsigned int> Event_T;
	std::vector<unsigned int>::iterator it;
	for (int i = 0; i < loop_flag; i++)
	{
		unsigned int Tmp_T = 0;
		Event_T.clear();
		for (int j = 0; j < 144; j++)
		{
			Qt[j] = 0;
			Pedestal[j] = 0;
		}
		printf("Processing in %d/%d...\r", i, loop_flag);
		for (int ii = 0; ii < 6; ii++)
		{
			bank[ii]->GetEntry(i);
			if (ii)
			{
				if (trigger[ii] == trigger[ii - 1]);
				else std::cout << trigger[ii] << "\t" << trigger[ii - 1] << "Error in trigger!\n";
			}
		}
		for (int ii = 0; ii < 2; ii++)
		{
			if (ii)
			{
				if (Event_T.size())
				{
					for (int j = 0; j < 144; j++)
					{
						if (j < 50)Qx[j] = Qt[j];
						else Qy[j - 50] = Qt[j];
					}
					t->Fill();
				}
				Tmp_T = 0;
			}
			int outer_loop = data_length[ii];
			for (int j = 0; j < outer_loop; j++)
			{
				if (Event_T.size())
				{
					bool run_flag = true;
					it = Event_T.begin();
					//cout<<"There are "<<Event_T.size()<<" Events recorded"<<endl;
					for (int k = 0; k < Event_T.size() / 3; k++)
					{
						if (TMath::Abs(int(*it) - int(T[ii][j])) < time_d)
						{
							run_flag = false;
							//cout<<"TMath::Abs(int("<<*it<<")-int("<<T[j]<<"))>"<<time_d<<endl;
						}
						//else cout<<"TMath::Abs(int("<<*it<<")-int("<<T[j]<<"))>"<<time_d<<endl;
						it++; it++; it++;
					}
					if (run_flag)
					{
						if (Tmp_T)
						{
							for (int iii = ii + 1; iii < 6; iii++)
							{
								int inner_loop = data_length[iii];
								//cout<<"Getting the entry: "<<i+slit[iii-1]<<". There are: "<<data_length<<" Data!"<<endl;
								for (int jj = 0; jj < inner_loop; jj++)
								{
									//cout<<"Tmp_T: "<<Tmp_T<<" T["<<jj<<"]: "<<T[jj]<<endl;
									if (TMath::Abs(int(Tmp_T) - int(T[iii][jj])) < time_d)
									{
										Qt[ch[iii][jj] - 1] = Q[iii][jj];
										Pedestal[ch[iii][jj] - 1] = base[iii][jj];
										//cout<<"Qt["<<ch[jj]-1<<"]= Q["<<jj<<"]: "<<Q[jj]<<endl;
									}
								}
							}
							T_date = Tmp_T;

							for (int jj = 0; jj < 144; jj++)
							{
								if (jj < 50)Qx[jj] = Qt[jj];
								else Qy[jj - 50] = Qt[jj];
							}
							t->Fill();
						}
						for (int jj = 0; jj < 144; jj++)
						{
							Qt[jj] = 0;
							Pedestal[jj] = 0;
						}
						Event_T.push_back(T[ii][j]);
						Event_T.push_back(ii);
						Event_T.push_back(j);
						Tmp_T = T[ii][j];
						Qt[ch[ii][j] - 1] = Q[ii][j];
						Pedestal[ch[ii][j] - 1] = base[ii][j];
					}
					else
					{
						Qt[ch[ii][j] - 1] = Q[ii][j];
						Pedestal[ch[ii][j] - 1] = base[ii][j];
						//cout<<"Qt["<<ch[j]-1<<"]= Q["<<j<<"]: "<<Q[j]<<endl;
					}
				}
				else
				{
					Event_T.push_back(T[ii][j]);
					Event_T.push_back(ii);
					Event_T.push_back(j);
					Tmp_T = T[ii][j];
					Qt[ch[ii][j] - 1] = Q[ii][j];
					Pedestal[ch[ii][j] - 1] = base[ii][j];
					//cout<<"Qt["<<ch[j]-1<<"]= Q["<<j<<"]: "<<Q[j]<<endl;
				}
			}
		}
		if (Event_T.size())
		{
			for (int j = 0; j < 144; j++)
			{
				if (j < 50)Qx[j] = Qt[j];
				else Qy[j - 50] = Qt[j];
			}
			t->Fill();
		}
		//it=Event_T.begin();
		//for(int ii=0;ii<Event_T.size()/3;ii++){cout<<" T[j]: "<<*it;it++;cout<<" board: "<<*it;it++;cout<<" ch: "<<*it<<endl;it++;}
		//cout<<"There are "<<Event_T.size()/3<<" Events recorded"<<endl;
		h1->Fill(Event_T.size() / 3);
	}
	printf("Finished!\n");
	time_t stop;
	time(&stop);
	double timelast = difftime(stop, start);
	std::cout << "root transferring cost " << timelast << " second." << endl;
	rootf->cd();
	h1->Write();
	t->Write();
	rootf->Close();
	return;
}

