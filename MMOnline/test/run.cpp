{
    char filename[100];
    char rootname[100];
    char rsuffix[10]="_2.root";
    char dsuffix[10]="_1.root" ;
    cout<< "please input the binary file name(without'_1.root'):" ;
    cin>>filename;
    strcpy(rootname,filename);
    strcat(filename,dsuffix);
    //initial root file
    strcat(rootname,rsuffix);
    TFile f(filename);
    TTree*ana=(TTree*)f.Get("ana");

    int det_ch=0;
    float baseline[64];
    float peak[64];
    int ptime[64];
    float rtime[64];

    ana->SetBranchAddress("det_ch",&det_ch);
    ana->SetBranchAddress("baseline",&baseline);
    ana->SetBranchAddress("peak",&peak);
    ana->SetBranchAddress("ptime",&ptime);
    ana->SetBranchAddress("rtime",&rtime);
 
    TFile * rootf= new TFile(rootname,"RECREATE" );

	float pos1 = 0;
	float ene1 = 0;
	float pos2 = 0;
	float ene2 = 0;
	int size_p1 = 0;
	int size_p2 = 0;
	TTree*output = new TTree("output", "the results of analysis");
	output->Branch("pos1", &pos1, "pos1/F");
	output->Branch("ene1", &ene1, "ene1/F");
	output->Branch("pos2", &pos2, "pos2/F");
	output->Branch("ene2", &ene2, "ene2/F");
	output->Branch("size_p1", &size_p1, "size_p1/I");
	output->Branch("size_p2", &size_p2, "size_p2/I");

    float F_th=400;
    float S_th=200;
    for (int i = 1; i <= total; i++)
	{
		ana->GetEntry(i);
		int max_p = 0;
		for (int j = 0; j < 64; j++)
		{
			max_p = (peak[max_p] > peak[j]) ? max_p : j;
		}
		if (det_ch == 208)
		{
			if (peak[max_p] > S_th)
			{
				int j = 1;
				size_p1 = 1;

				ene1 = peak[max_p];
				pos1 = ene1*max_p;

				while (((max_p - j) > -1) && (peak[max_p - j] > F_th))
				{
					ene1 += peak[max_p - j];
					pos1 += peak[max_p - j] * (max_p - j);
					j++;
					size_p1++;
				}
				j = 1;
				while (((max_p + j) < 64) && (peak[max_p + j] > F_th))
				{
					ene1 += peak[max_p + j];
					pos1 += peak[max_p + j] * (max_p + j);
					j++;
					size_p1++;
				}
				pos1 = pos1 / ene1;
			}
		}
		else if (det_ch == 704)
		{
			if (peak[max_p] > S_th)
			{
				int j = 1;
				size_p2 = 1;

				ene2 = peak[max_p];
				pos2 = ene2*max_p;

				while (((max_p - j) > -1) && (peak[max_p - j] > F_th))
				{
					ene2 += peak[max_p - j];
					pos2 += peak[max_p - j] * (max_p - j);
					j++;
					size_p2++;
				}
				j = 1;
				while (((max_p + j) < 64) && (peak[max_p + j] > F_th))
				{
					ene2 += peak[max_p + j];
					pos2 += peak[max_p + j] * (max_p + j);
					j++;
					size_p2++;
				}
				pos2 = pos2 / ene2;
			}
			output->Fill();
		}
	}
    t->Write();
    rootf->Close();
}