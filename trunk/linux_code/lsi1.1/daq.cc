#include "daq.h"
#include "gui.h"

daq::daq()
{   num=0;
// print header
printf( "\n");
printf( "******************\n");
printf( "*  VME DAQ linux *\n");
printf( "*                *\n");
printf( "*fanrr@ihep.ac.cn*\n");
printf( "******************\n");
printf( "\n");

//
for (int i= 0; i< MAX_HISTO_CHANNELS; i++)
{
	sprintf(Hname,"Ch%d",i); 
	h1[i] = new TH1F(Hname,"spectrum",4096,0,4095);
}

run_flag=true;
rnd=new TRandom();
}

daq::~daq()
{    
	delete rnd;
	for (int i= 0; i< MAX_HISTO_CHANNELS; i++)
	{
		delete h1[i];
	}
	delete f;
	if ( result < 0 )
	{
		printf("Error - failed to disable PCI image window (%d)\n", result);

	}




	printf("The DAQ is exited!");
}

int daq::Getdata()
{

	run_flag=true;
	pause_flag=false;
	read_events=0;
	switch(fmode)
	{
	case 0:
		{
			while(run_flag)
			{
				data=0;
				h1[rnd->Integer(16)]->Fill(rnd->Gaus(2000,100));
				read_events++;
				if (read_events==daq_counts)Stop();
				while(pause_flag&&run_flag)
				{
					gSystem->ProcessEvents();
				}
				total=h1[Hview];
				gSystem->ProcessEvents();
			}
			printf("There are %d random number read ! \n",read_events);

		}
		break;
	case 1:
		{
			memset((char *)&idata,0,sizeof(EN_PCI_IMAGE_DATA));
			devHandle = vme_openDevice("lsi0");
			if( devHandle < 0 )
			{
				printf("Error - failed to open PCI image window\n");
				getchar();
				exit(0);
			}
			else
			{
				idata.pciAddress = 0;
				idata.pciAddressUpper = 0;
				//todo
				UINT32 tmpad=0;
				tmpad=atol(address);
				idata.vmeAddress = (tmpad<<16)&0xffff0000;
				idata.vmeAddressUpper = 0;
				idata.size = 0x10000;
				idata.sizeUpper = 0;
				idata.readPrefetch =1;
				idata.prefetchSize = 3;
				idata.dataWidth = EN_VME_D32;
				idata.addrSpace = EN_VME_A32;
				idata.type = EN_LSI_DATA;
				idata.mode = EN_LSI_USER;
				idata.vmeCycle = 0;		// single cycle 

			}
			result = vme_enablePciImage( devHandle, &idata );
			if ( result < 0 )
			{
				printf("Error - failed to enable PCI image window (%d)\n", result);
			}
			else
			{
				printf("PCI image 0 enabled, reading data...\n");
				while(run_flag)
				{
					data=0;
					result = vme_read( devHandle, 0x0000, buffer,4);
					if ( result < 0 )
					{
						printf("Error - failed to read data (%d)\n", result);
					}
					else
					{
						for ( int i = 0; i < 4; i++ )
						{
							tmp_data=buffer[i];
							data+=UINT32(tmp_data)<<(24-i*8);
						}
						switch(data& 0x07000000)
						{
						case 0x02000000: 
							{
								//						printf("this is a header!");
								//						printf("\n");
							}
							break;
						case 0x04000000: 
							{
								read_events++;
								if (read_events==daq_counts)Stop();
								//						printf("this is end of data!");
								//						printf("\n");
							}
							break;
						case 0x00000000:
							{
								// DATUM
								geo= UINT32((data&0xf0000000)>>27);
								ch= UINT32((data>>17)&0x0000000f);
								adc= UINT32((data&0x00000fff));
								h1[ch]->Fill(adc);
								//			printf("the GEO is %d\n", geo );
								//			printf("the ch is %d\n", ch );
								//			printf("the adc is %d\n", adc );

							}
							break;
						case 0x06000000:
							break;

						}
						while(pause_flag&&run_flag)
						{
							gSystem->ProcessEvents();
						}
					}
					result = vme_disablePciImage( devHandle );
					total=h1[Hview];
					gSystem->ProcessEvents();
				}
			}
			printf("There are %d events read from VME! \n",read_events);
		}
		break;
	case 2:
		{
			new TBrowser();
			printf("Start Offline!\n");
		}
		break;
	}
	return read_events;
} 

char* daq::Write()
{
	sprintf(name,"Data_%d.root",num); 
	f=new TFile(name,"RECREATE");

	f->cd();  
	for (int i= 0; i< MAX_HISTO_CHANNELS; i++) 
	{
		h1[i]->Write();
	}
	f->Close();
	return name;
}

void daq::Reset()
{
	for (int i= 0; i< MAX_HISTO_CHANNELS; i++) 
	{
		h1[i]->Reset();
	}
	read_events=0;
}

void daq::Pause()
{ 
	pause_flag=!pause_flag;
	/*if(fmode==1&&pause_flag) vme_enablePciImage( devHandle, &idata );
	else if(fmode==1)vme_disablePciImage( devHandle );*/
}

void daq::Stop()
{ 
	run_flag=false;
	if(fmode==1)vme_closeDevice( devHandle );
	num++;
}

void daq::SetMode(const int mode)
{					
	fmode=mode;
}

