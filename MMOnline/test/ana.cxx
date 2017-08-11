{
    char filename[100];
    char rootname[100];
    char rsuffix[10]="_1.root";
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
    //TCanvas *c1=new TCanvas("testc","test canvas");
    TFile * rootf= new TFile(rootname,"RECREATE" );
    TTree*t=new TTree("ana","the results of analysis");
    t->Branch("baseline",baseline,"baseline[64]/F");
    t->Branch("peak",peak,"peak[64]/F");
    t->Branch("ptime",ptime,"ptime[64]/I");
    t->Branch("rtime",rtime,"rtime[64]/F");    
    t->Branch("det_ch",&det_ch,"det_ch/I");

    TH1F *h1=new TH1F("test","test",512,0,512);
    for(int i=1;i<=total;i++)
    {
        bank->GetEntry(i);
        for(int j=0;j<64;j++)
        {
            h1->Reset();
            for(int jj=0;jj<512;jj++)
            {
                if(jj==0)baseline[j]=0;
                if(jj<100)baseline[j]+=adc_data[j][jj];
                if(jj==100)baseline[j]=baseline[j]/100;
                h1->Fill(jj,adc_data[j][jj]);
                //cout<<adc_data[j][jj]<<endl;
            }
            //h1->Smooth(1);
            //h1->Draw();
            //c1->Modified();
            //c1->Update();
            ptime[j]=h1->GetMaximumBin();
            peak[j]=h1->GetBinContent(ptime[j])-baseline[j];
            for(int jj=0;jj<ptime[j];jj++)
            {
                rtime[j]=jj;
                if((h1->GetBinContent(jj)-baseline[j])>(peak[j]/10.0))break;
            }
        }
        t->Fill();
    }
    rootf->cd();
    t->Write();
    rootf->Close();
    f.Close();
}