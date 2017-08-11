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


    float pos;
    float ene;
    int size_p;
    
    int total=ana->GetEntries();
    TTree*t=new TTree("output","the results of analysis");
    t->Branch("pos",&pos,"pos/F");
    t->Branch("ene",&ene,"ene/F");
    t->Branch("size_p",&size_p,"size_p/I");
    float F_th=400;
    float S_th=200;
    for(int i=1;i<=total;i++)
    {
        ana->GetEntry(i);
        int max_p=0;
        for(int j=0;j<64;j++)
        {
            max_p = (peak[max_p]>peak[j]) ? max_p : j;
            //cout<<peak[j]<<endl;
        }
        //cout<<max_p<<endl;
        if(peak[max_p]>S_th)
        {
            int j=1;
            size_p=1;
            ene=peak[max_p];
            pos=ene*max_p;
            while(((max_p-j)>-1)&&(peak[max_p-j]>F_th))
            {
                ene+=peak[max_p-j];
                pos+=peak[max_p-j]*(max_p-j);
                j++;
                size_p++;
            }
            j=1;
            while(((max_p+j)<64)&&(peak[max_p+j]>F_th))
            {
                ene+=peak[max_p+j];
                pos+=peak[max_p+j]*(max_p+j);
                j++;
                size_p++;
            }
            pos=pos/ene;
            t->Fill();
        }
    }
    t->Write();
    rootf->Close();
}