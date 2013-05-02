#include "gui.h"
#include "decode.h"
#include <iostream>
#include <fstream>
#include "TAxis.h"
using namespace std;
enum MessageTypes
{
	M_START,
	M_CALIBRATE,
	M_SAVE,
	M_STOP,
	M_EXIT
};
gui :: gui(const TGWindow *p, UInt_t w, UInt_t h)
: TGMainFrame(p, w, h)
{	
	runflag=true;
	num_unit=5;
	num_ladder=6;
	DAQ_time=30;
	flength=0;
	sprintf(dsuffix,".bin");
	sprintf(csuffix,".bin_RMSE.txt");
	sprintf(rsuffix,".root");
	sprintf(rootname,"empty file");
	//online hit map
	h2=new TH2F("the pad viewer","viewer",num_unit,0.5,num_unit+0.5,num_ladder,0.5,num_ladder+0.5);
	h2->GetZaxis()->SetRangeUser(0,100);
	//convert to histogram;
	for (int i= 0; i< 64; i++)
	{
		sprintf(Hname,"Ch%d",i); 
		h1[i] = new TH1F(Hname,"spectrum",2048,0,8192);
	}
	//make event analysis
	t=new TTree("event","data of event");
	char tmp_name[50];
	for (int i= 0; i< 64; i++)
	{
		sprintf(Hname,"d_Ch%d",i); 
		sprintf(tmp_name,"adc%d/I",i); 
		t->Branch(Hname,&t_adc[i],tmp_name);
	}	

	// main frame
	fMainFrame = new TGHorizontalFrame(this,450,300,kHorizontalFrame);
	fMainFrame->SetName("fMainFrame");
	fMainFrame->SetLayoutBroken(kTRUE);

	ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

	// graphics context changes

	valorentry.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	gClient->GetColorByName("#000000",valorentry.fForeground);
	gClient->GetColorByName("#e0e0e0",valorentry.fBackground);
	valorentry.fFillStyle = kFillSolid;
	valorentry.fFont = ufont->GetFontHandle();
	valorentry.fGraphicsExposures = kFALSE;
	uGC = gClient->GetGC(&valorentry, kTRUE);

	monitorentry = new TGTextEntry(fMainFrame, new TGTextBuffer(31),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kDoubleBorder | kOwnBackground);
	monitorentry->SetMaxLength(4096);
	monitorentry->SetAlignment(kTextLeft);
	monitorentry->SetText("");
	monitorentry->Resize(200,monitorentry->GetDefaultHeight());
	fMainFrame->AddFrame(monitorentry, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	monitorentry->MoveResize(120,96,208,22);

	ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

	// graphics context changes

	valrateentry.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	gClient->GetColorByName("#000000",valrateentry.fForeground);
	gClient->GetColorByName("#e0e0e0",valrateentry.fBackground);
	valrateentry.fFillStyle = kFillSolid;
	valrateentry.fFont = ufont->GetFontHandle();
	valrateentry.fGraphicsExposures = kFALSE;
	uGC = gClient->GetGC(&valrateentry, kTRUE);

	calibrateentry = new TGTextEntry(fMainFrame, new TGTextBuffer(31),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kDoubleBorder | kOwnBackground);
	calibrateentry->SetMaxLength(4096);
	calibrateentry->SetAlignment(kTextLeft);
	calibrateentry->SetText("");
	calibrateentry->Resize(208,calibrateentry->GetDefaultHeight());
	fMainFrame->AddFrame(calibrateentry, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	calibrateentry->MoveResize(120,48,208,22);

	calibratefile = new TGLabel(fMainFrame,"calibrate file");
	calibratefile->SetTextJustify(36);
	calibratefile->SetMargins(0,0,0,0);
	calibratefile->SetWrapLength(-1);
	fMainFrame->AddFrame(calibratefile, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	calibratefile->MoveResize(8,48,96,18);

	start= new TGTextButton(fMainFrame,"start",M_START);
	start->SetTextJustify(36);
	start->SetMargins(0,0,0,0);
	start->SetWrapLength(-1);
	start->Resize(91,24);
	start -> Associate(this);
	fMainFrame->AddFrame(start, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	start->MoveResize(40,224,91,24);

	stop = new TGTextButton(fMainFrame,"stop",M_STOP);
	stop->SetTextJustify(36);
	stop->SetMargins(0,0,0,0);
	stop->SetWrapLength(-1);
	stop->Resize(91,24);
	stop->Associate(this);
	fMainFrame->AddFrame(stop, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	stop->MoveResize(170,224,91,24);

	exit = new TGTextButton(fMainFrame,"exit",M_EXIT);
	exit->SetTextJustify(36);
	exit->SetMargins(0,0,0,0);
	exit->SetWrapLength(-1);
	exit->Resize(91,24);
	exit->Associate(this);
	fMainFrame->AddFrame(exit, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	exit->MoveResize(300,224,91,24);

	calibrate = new TGTextButton(fMainFrame,"calibrate",M_CALIBRATE);
	calibrate->SetTextJustify(36);
	calibrate->SetMargins(0,0,0,0);
	calibrate->SetWrapLength(-1);
	calibrate->Resize(91,24);
	calibrate->Associate(this);
	fMainFrame->AddFrame(calibrate, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	calibrate->MoveResize(170,175,91,24);

	save= new TGTextButton(fMainFrame,"save root file",M_SAVE);
	save->SetTextJustify(36);
	save->SetMargins(0,0,0,0);
	save->SetWrapLength(-1);
	save->Resize(91,24);
	save->Associate(this);
	fMainFrame->AddFrame(save, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	save->MoveResize(300,175,91,24);

	monitorfile = new TGLabel(fMainFrame,"monitor file");
	monitorfile->SetTextJustify(36);
	monitorfile->SetMargins(0,0,0,0);
	monitorfile->SetWrapLength(-1);
	fMainFrame->AddFrame(monitorfile, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	monitorfile->MoveResize(16,96,81,18);

	AddFrame(fMainFrame, new TGLayoutHints(kLHintsCenterX,2,2,2,2));

	// Set a name to the main frame
	SetWindowName("Hit Map");
	// Map all subwindows of main frame
	MapSubwindows();
	// Initialize the layout algorithm
	Resize(this->GetDefaultSize());
	// Map main frame
	MapWindow();
}

gui::~gui(void)
{
}
void gui ::CloseWindow()
{
	// Got close message for this MainFrame. Terminate the application
	// or returns from the TApplication event loop (depending on the
	// argument specified in TApplication::Run()).
	gApplication->Terminate(0);
}

Bool_t gui :: ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2)
{
	switch(GET_MSG(msg))
	{
	case kC_COMMAND:
		switch(GET_SUBMSG(msg))
		{
		case kCM_BUTTON: 
			switch(parm1)
			{

			case M_START:
				dostart();
				break;
			case M_CALIBRATE:
				docali();
				break;
			case M_SAVE:
				dosave();
				break;
			case M_STOP:
				dostop();
				break;
			case M_EXIT:
				CloseWindow();
				break;
			default: break;
			}
			break;	     
		default: break;
		}	    
		break;
	default: break;	
	}
	return kTRUE;
}
void gui::docali()
{
	strcpy(filename,calibrateentry->GetText());
	strcat(filename,csuffix);
	ifstream c_f(filename);
	if(c_f.is_open())
	{
		for(int i=0; i< 64; i++)
		{
			c_f>>ch;
			c_f>>mean[ch];
			c_f>>rms[ch];	
		}
	}
	else
	{
		cout << "Error opening file";
	}
	c_f.close();
	cout<<"Calibration complete!"<<endl;
}
void gui::dosave()
{
//initial root file
	strcat(rootname,rsuffix);
	TFile * rootf=new TFile(rootname,"RECREATE");
		rootf->cd();  

		for (int i= 0; i< 64; i++)
	{
		h1[i]->Write();;
	}	
		t->Write();
	rootf->Close();
}
void gui::dostart()
{	
	fviewer=new viewer(fClient->GetRoot(),1,0);
	runflag=true;
	strcpy(filename,monitorentry->GetText());
	strcpy(rootname,filename);
	strcat(filename,dsuffix);
//reset
		for (int i= 0; i< 64; i++)
	{
		h1[i]->Reset();;
	}	
		t->Reset();

//reading
	while(runflag)
	{
		int tmpl;
		ifstream f(filename,ifstream::binary);
	 	if(f.is_open())
    	{		
			f.seekg(0, ios::end);
			tmpl=f.tellg();
			if(flength!=tmpl)
			{
				
				f.seekg (flength, ios::beg);
				while (!f.eof())
				{
					h2->Reset();
					for(int i=0;i<64;i++)
					{
						f.read((char*)&data,4);
						adc=int((data&0x3fff)>>1);
						t_adc[i]=adc-mean[i];
						h1[i]->Fill(adc);
					}
					t->Fill();
					for(int i=0;i<64;i++)
					{
						int NDet=0;
						if (i<16&&i>0)NDet=i;
						else if (i>47&&i<63)NDet=i-47+15;
						if (NDet)h2->Fill(((NDet%num_unit)?NDet%num_unit:num_unit),1+int((NDet-1)/num_unit),t_adc[i]);
					}
						fviewer->draw(h2);
						Sleep(1000);
						gSystem->ProcessEvents();
    			}
				flength=tmpl;
			}
		}
  		else
    	{
			cout<<"Fail to open file!"<<endl;
      		Sleep(100);
			continue;
    	}
		f.close();
		gSystem->ProcessEvents();
	}
	delete fviewer;
}
void gui::dostop()
{
	runflag=false;
}

