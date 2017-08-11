{
    char filename[100];
    char rootname[100];
    char histname[50];
    char rsuffix[10]="_pic.root";
    char dsuffix[10]="_0.root" ;
    cout<< "please input the binary file name(without'_0.root'):" ;
    cin>>filename;
    strcpy(rootname,filename);
    strcat(filename,dsuffix);
    //initial root file
    strcat(rootname,rsuffix);
    TFile f(filename);
    TTree*bank=(TTree*)f.Get("bank");

    UShort_t adc_data[64][512];
	int Inf_time;
    int det_ch=0;

    float baseline[64];
    float peak[64];
    int ptime[64];
    float rtime[64];


    bank->SetBranchAddress("adc_data",&adc_data);
    bank->SetBranchAddress("Inf_time",&Inf_time);
    bank->SetBranchAddress("det_ch",&det_ch);

    int total=bank->GetEntries();

    int pic_num=20;

    TFile * rootf= new TFile(rootname,"RECREATE" );
    TH1F *h1[pic_num][64];
    TH1F *h2[pic_num];

    for(int i=1;i<=pic_num;i++)
    {
        bank->GetEntry(int(i*total/pic_num));
        sprintf(histname,"distribution_%d",i-1);
        h2[i-1]=new TH1F(histname,histname,64,0,64);
        for(int j=0;j<64;j++)
        {
            sprintf(histname,"hist_%d_%d",i-1,j);
            h1[i-1][j]=new TH1F(histname,histname,512,0,512);
        }
        for(int j=0;j<64;j++)
        {
            for(int jj=0;jj<512;jj++)
            {
                h1[i-1][j]->Fill(jj,adc_data[j][jj]);
            }
        }
        for(int j=0;j<64;j++)h2[i-1]->Fill(j,h1[i-1][j]->GetBinContent(h1[i-1][j]->GetMaximumBin()));
    }
    rootf->cd();
    for(int i=0;i<pic_num;i++)
    {
        h2[i]->Write();
        for(int j=0;j<64;j++)h1[i][j]->Write();
    }
    rootf->Close();
    f.Close();
}