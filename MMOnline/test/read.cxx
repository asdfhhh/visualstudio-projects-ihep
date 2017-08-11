#!/home/rui/work/root/bin/root
{
    UShort_t adc_data[64][512];
	int Inf_time;
    int tag;
    char filename[100];
    char rootname[100];
    char dsuffix[10]=".dat" ;
    char rsuffix[10]="_0.root" ;
    UShort_t data_bulk[66];
    int det_ch=0;
	UShort_t *adc=0;
    //initial data file
    cout<< "please input the binary file name(without'.dat'):" ;
    cin>>filename;
    strcpy(rootname,filename);
    strcat(filename,dsuffix);
	ifstream f(filename,ifstream::binary);
    if(f.is_open())
    {
		//initial root file
        strcat(rootname,rsuffix);
		//TCanvas *c1=new TCanvas("testc","test canvas");
		TFile * rootf= new TFile(rootname,"RECREATE" );
		TTree*t=new TTree("bank","the wave be stored");
		t->Branch("Inf_time",&Inf_time,"Inf_time/I");
		t->Branch("adc_data",adc_data,"adc_data[64][512]/s");
		t->Branch("det_ch",&det_ch,"det_ch/I");
		//TH1F*h1=new TH1F("test","test",512,0,512);
		int count=0;
		int E_count=0;
		time_t start;
		time(&start);
		while (!f.eof())
		{
			f.read((char*)&tag,1);
			if((tag&0xFF)==0xEE)
			{
				f.read((char*)&tag,1);
				if((tag&0xFF)==0xEE)
				{
				f.read((char*)&tag,1);
				if((tag&0xFF)==0xE0)
				{
				f.read((char*)&tag,1);
				if((tag&0xFF)==0x00)
				{
					f.read((char*)&Inf_time,4);
					for(int i=0;i<512;i++)
					{
						f.read((char*)&data_bulk,66*2);
						for(int ii=0;ii<64;ii++)
						{
							adc=data_bulk+ii+2;
							adc_data[ii][i]=((*adc<<8)&0x0f00)+((*adc>>8)&0x00ff);
						}
					}
					det_ch=*data_bulk;
					f.read((char*)&tag,2);
					if((tag&0xFFFF)==0xFFFF)
					{
						/*for(int i=0;i<64;i++)
						{
							h1->Reset();
							for(int ii=0;ii<512;ii++)
							{
								h1->Fill(ii,adc_data[i][ii]);
							}					
							h1->Draw();
							c1->Modified();
							c1->Update();
						}*/
						t->Fill();
						count++;
					}
					else if((tag&0xFFFF)==0xEEEE)
					{
						adc_data[63][511]=adc_data[63][510];
						f.seekg(-2,ios::cur);
						//cout<<"Error!"<<endl;
						count++;
						E_count++;
					}
					else if((tag&0xFFFF)==0xFFBC)
					{
						t->Fill();
						E_count++;
					}
					else
					{
						if(!f.eof())
						{
							E_count++;
							cout<<"Read an Error tag code: "<<hex<<tag<<" at the position of "<<f.tellg()<<" Bytes."<<endl;
						}
					}				
				}
				}
				}
				}

			}
        }
        else
        {
                cout << "Error opening file" ;
        }
	time_t stop;
	time(&stop);
	double timelast=difftime(stop,start);
    cout<<"there are "<<E_count<<" Error in "<<count<<" event recorded!"<<endl;
	cout<<"cost "<<timelast<<" second."<<endl;
	f.close();
    rootf->Write();
}


