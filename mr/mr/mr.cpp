#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "TFile.h"
#include "TTree.h"

using namespace std;

void byteswap(unsigned int* rdpr, int intct)
{
	int ii = 0;
	unsigned int temp = 0;
	unsigned int* tempr = rdpr;
	for (; ii<intct; ii++)
	{
		temp = *tempr;
		temp = int((temp << 24) & 0xff000000) + int((temp << 8) & 0xff0000) + int((temp >> 8) & 0xff00) + int((temp >> 24) & 0xff);
		*tempr = temp;
		tempr++;
	}
}


void read()
{
	float X, Y, tof, Q, Qa, Qb;

	int T0 = 0, TubeNo = 0, hit = 0, ModuleID = 0, Step = 0;
	int TData = 0, Pu_Date = 0, Pl_Date = 0, Qu = 0, Ql = 0;
	
	int left_count = 0, T0_bytes = 0;
	char filename[100];
	char rootname[100];
	char dsuffix[10] = ".dat";
	char rsuffix[10] = ".root";
	//initial data file
	cout << "please input the binary file name(without'.dat'):";
	cin >> filename;
	strcpy(rootname, filename);
	strcat(filename, dsuffix);
	//initial root file
	strcat(rootname, rsuffix);

	//TCanvas *c1=new TCanvas("testc","test canvas");
	TFile * rootf = new TFile(rootname, "RECREATE");
	TTree*t = new TTree("bank", "the wave be stored");
	t->Branch("T0", &T0, "T0/I");
	t->Branch("TData", &TData, "TData/I");
	t->Branch("ModuleID", &ModuleID, "ModuleID/I");
	t->Branch("TubeNo", &TubeNo, "TubeNo/I");
	t->Branch("Step", &Step, "Step/I");
	t->Branch("Pu_Date", &Pu_Date, "Pu_Date/I");
	t->Branch("Pl_Date", &Pl_Date, "Pl_Date/I");
	t->Branch("Qu", &Qu, "Qu/I");
	t->Branch("Ql", &Ql, "Ql/I");
	t->Branch("X", &X, "X/F");
	t->Branch("Y", &Y, "Y/F");
	t->Branch("tof", &tof, "tof/F");
	t->Branch("Qa", &Qa, "Qa/F");
	t->Branch("Qb", &Qb, "Qb/F");
	t->Branch("Q", &Q, "Q/F");

	ifstream fin(filename, std::ios::binary);
	fin.seekg(0, fin.end);
	int totalsize = fin.tellg();
	cout << "totalsize: " << totalsize << endl;
	fin.seekg(0, fin.beg);


	int count = 0;

	//Recv head
	float total_bytes = 0;
	float rate = 0;

	int i = 0;
	int Ncount = 3;

	char *buffer;


	buffer = (char *)malloc(totalsize + 1);

	fin.read(buffer, sizeof(char)*totalsize);

	unsigned  int *int_addr = (unsigned int*)buffer;

	byteswap(int_addr + i, totalsize / 4);

	char tmp1[10];



	for (i = 0; i <totalsize / 4;)
	{
		if (((((*(int_addr + i)) & 0xff000000) >> 24)) == 0xfa)
		{
			/*cout << "i: " << i << endl;
			cout << "*(int_addr+i+4):" << "0x" << hex << *(int_addr + i + 4) << endl;
			cout << "*(int_addr+i+2):" << "0x" << hex << *(int_addr + i + 2) << endl;*/
			ModuleID = ((int_addr[i + 0]) & 0x000000ff);

			T0 = int_addr[i + 2];

			hit = 0;// ((int_addr[i + 3]) & 0xfffc0000) >> 18;

			/*if (hit > 600 * 12)
			{
				break;
			}*/

			Step = (int_addr[i + 3]) & 0x0000003f;


			for (int jj = i + 4; ((((*(int_addr + jj)) & 0xf0000000) >> 28)) == 0xe;)
			{
				//if (((((*(int_addr + jj)) & 0xf0000000) >> 28)) == 0xe)
				{
					TubeNo = (int_addr[jj] & 0x0f000000) >> 24;

					TData = int_addr[jj] & 0x00ffffff;

					Pu_Date = int_addr[jj + 1] & 0x000fffff;//0x00ffffff;
					Pl_Date = int_addr[jj + 2] & 0x000fffff; //0x00ffffff;
					Qu = (int_addr[jj + 3] >> 16) & 0x0000ffff;
					Ql = int_addr[jj + 3] & 0x0000ffff;;
					
					switch (TubeNo)
					{
						
						case 4:
							Y = (17 + 8.5) / 2;
							break;
						case 5:
							Y = (17 + 16.5) / 2;
							break;
						case 6:
							Y = (17 + 24.5) / 2;
							break;
						case 8:
							Y = (25.5 + 34) / 2;
							break;
						default:
							Y = 0;
							break;
					}
					Qa = Qu - Pu_Date / Step;
					Qb = Ql - Pl_Date / Step;
					Q = Qa + Qb;
					tof = TData*12.5 / 1000000;
					X = 150 + 150 * (Qa - Qb) / Q;
					t->Fill();
					hit++;
					jj = jj + 4;
				}
				//else
				//{

					//cout << "Datahead *(int_addr+i+4):" << "0x" << hex << *(int_addr + i + 4) << endl;

					//cout << "T0 *(int_addr+i+2):" << "0x" << hex << *(int_addr + i + 2) << endl;
					//break;

				//}
			}
			left_count = hit * 4 + 2;
			Ncount += hit;
			i = i + 4 + left_count;
			
		}
		else
		{
			cout << "ERROR!" << endl;
			break;
		}
	}

	free(buffer);
	fin.close();
	rootf->Write();
	rootf->Close();
}

int main()
{
	read();
	return 0;
}