{
    char filename[100];
    char rootname[100];
    char histname[100];
    char rsuffix[10]="_plot.root";
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
 


    int total=ana->GetEntries();

    int pic_num=20;

    TFile * rootf= new TFile(rootname,"RECREATE" );
    TH2F *h2[pic_num];

    for(int i=1;i<=pic_num;i++)
    {
        ana->GetEntry(int(i*total/pic_num));
        sprintf(histname,"distribution_%d",i-1);
        h2[i-1]=new TH2F(histname,histname,64,0,64,512,0,512);
        for(int j=0;j<64;j++)
        h2[i-1]->Fill(j,rtime[j],peak[j]);
    }
    rootf->cd();
    for(int i=0;i<pic_num;i++)
    {
        h2[i]->Write();
    }
    rootf->Close();
    f.Close();
}