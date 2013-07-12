#include "gui.h"
#include "about.h"
#include "TCanvas.h"
enum MessageTypes
{
	M_START,
	M_PAUSE,
	M_RESET,
	M_STOP,
	M_SET,
	M_HELP_ABOUT,
	M_OK,
	M_CLEAR

};
gui :: gui(const TGWindow *p, UInt_t w, UInt_t h)
: TGMainFrame(p, w, h)
{
	gui_time=-1;
	gui_counts=-1;
	myviewer=new viewer(fClient->GetRoot(),1,1);
	mydaq = new daq();
	//***********************************************************************************//
	//set menu
	fMenuDock = new TGDockableFrame(this);
	AddFrame(fMenuDock, new TGLayoutHints(kLHintsExpandX, 0, 0, 1,0));
	fMenuDock->SetWindowName("DAQ Set Menu");

	fMenuBarLayout = new TGLayoutHints(kLHintsTop | kLHintsExpandX);
	fMenuBarHelpLayout = new TGLayoutHints(kLHintsTop | kLHintsRight);

	fMenuHelp = new TGPopupMenu(fClient->GetRoot());
	fMenuHelp->AddEntry("&About", M_HELP_ABOUT);
	// Menu button messages are handled by the main frame (i.e. "this")
	// ProcessMessage() method.
	fMenuHelp->Associate(this);

	fMenuBar = new TGMenuBar(fMenuDock, 1, 1, kHorizontalFrame);
	fMenuBar->AddPopup("&Help", fMenuHelp, fMenuBarHelpLayout);
	fMenuDock->AddFrame(fMenuBar, fMenuBarLayout);

	//***********************************************************************************//
	//set tab
	fTab = new TGTab(this, 500, 300);
	//tab 1
	tf = fTab->AddTab("Control");
	hFrame1 = new TGCompositeFrame(tf,500,300,kVerticalFrame);
	hFrame1->SetName("hFrame1");
	hFrame1->SetLayoutBroken(kTRUE);


	//the output editor
	foutput = new TGTextEdit(hFrame1,288,216);
	foutput->SetName("OutPut");
	// foutput->LoadFile("VME.ini");
	hFrame1->AddFrame(foutput, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	foutput->MoveResize(190,30,300,250);

	// will reflect user font changes
	ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

	// will reflect user GC changes
	// graphics context changes

	address.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	gClient->GetColorByName("#000000",address.fForeground);
	gClient->GetColorByName("#c0c0c0",address.fBackground);
	address.fFillStyle = kFillSolid;
	address.fFont = ufont->GetFontHandle();
	address.fGraphicsExposures = kFALSE;
	uGC = gClient->GetGC(&address, kTRUE);

	faddress = new TGTextEntry(hFrame1, new TGTextBuffer(15),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kDoubleBorder | kOwnBackground);
	faddress->SetMaxLength(4096);
	faddress->SetAlignment(kTextLeft);
	faddress->Resize(83,faddress->GetDefaultHeight());
	hFrame1->AddFrame(faddress, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	faddress->MoveResize(40,160,83,22);

	Daddress = new TGLabel(hFrame1,"address");
	Daddress->SetTextJustify(36);
	Daddress->SetMargins(0,0,0,0);
	Daddress->SetWrapLength(-1);
	hFrame1->AddFrame(Daddress, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	Daddress->MoveResize(40,136,57,18);

	// combo box
	methods = new TGComboBox(hFrame1,-1,kHorizontalFrame | kSunkenFrame | kDoubleBorder | kOwnBackground);
	methods->SetName("methods");
	methods->AddEntry("random test",0);
	methods->AddEntry("DAQ Online",1);
	methods->AddEntry("DAQ Offline",2);
	methods->Resize(102,22);
	methods->Select(-1);
	hFrame1->AddFrame(methods, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	methods->MoveResize(40,104,83,22);

	lmethods = new TGLabel(hFrame1,"DAQ mode");
	lmethods->SetTextJustify(36);
	lmethods->SetMargins(0,0,0,0);
	lmethods->SetWrapLength(-1);
	hFrame1->AddFrame(lmethods, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	lmethods->MoveResize(40,80,57,18);


	fchannel =  new TGNumberEntry(hFrame1,1,6,-1, TGNumberFormat::kNESInteger,
		TGNumberFormat::kNEANonNegative, 
		TGNumberFormat::kNELLimitMinMax,
		1, 16);
	fchannel->SetName("fchannel");
	hFrame1->AddFrame(fchannel, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fchannel->MoveResize(40,216,59,22);

	Channel = new TGLabel(hFrame1,"Channel");
	Channel->SetTextJustify(36);
	Channel->SetMargins(0,0,0,0);
	Channel->SetWrapLength(-1);
	hFrame1->AddFrame(Channel, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	Channel->MoveResize(40,192,57,18);

	logo = new TGIcon(hFrame1,"VMElogo.png");
	logo->SetName("logo");
	hFrame1->AddFrame(logo, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	logo->MoveResize(8,24,168,40);

	fSetButton = new TGTextButton(hFrame1,"set", M_SET);
	fSetButton -> SetTextJustify(36);
	fSetButton->SetMargins(0,0,0,0);
	fSetButton->SetWrapLength(-1);
	fSetButton->Resize(32,16);
	fSetButton -> Associate(this);
	fSetButton->SetState(kButtonDisabled);
	hFrame1->AddFrame(fSetButton,new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	fSetButton->MoveResize(120,220,32,16);

	tf->AddFrame(hFrame1, new TGLayoutHints(kLHintsCenterX,2,2,2,2));

	//tab 2

	tf = fTab->AddTab("Option");
	hFrame2 = new TGCompositeFrame(tf,500,300,kVerticalFrame);
	hFrame2->SetName("hFrame2");
	hFrame2->SetLayoutBroken(kTRUE);
	// MainFrame Contructor Function
	// Create Main Frame
	// Create canvas widget   
	Rmode = new TGComboBox(hFrame2,-1,kHorizontalFrame | kSunkenFrame | kDoubleBorder | kOwnBackground);
	Rmode->SetName("limited");
	Rmode->AddEntry("no limited ",0);
	Rmode->AddEntry("time limited ",1);
	Rmode->AddEntry("counts limited ",2);
	Rmode->Resize(102,22);
	Rmode->Select(0);
	hFrame2->AddFrame(Rmode, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	Rmode->MoveResize(80,32,105,19);



	// will reflect user font changes
	ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

	// will reflect user GC changes
	// graphics context changes
	Vtime.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	gClient->GetColorByName("#000000",Vtime.fForeground);
	gClient->GetColorByName("#c0c0c0",Vtime.fBackground);
	Vtime.fFillStyle = kFillSolid;
	Vtime.fFont = ufont->GetFontHandle();
	Vtime.fGraphicsExposures = kFALSE;
	uGC = gClient->GetGC(&Vtime, kTRUE);

	Ttime = new TGTextEntry(hFrame2, new TGTextBuffer(15),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kDoubleBorder | kOwnBackground);
	Ttime->SetMaxLength(4096);
	Ttime->SetAlignment(kTextLeft);
	Ttime->Resize(83,Ttime->GetDefaultHeight());
	hFrame2->AddFrame(Ttime, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	Ttime->MoveResize(80,60,83,22);


	Ltime = new TGLabel(hFrame2,"time");
	Ltime->SetTextJustify(36);
	Ltime->SetMargins(0,0,0,0);
	Ltime->SetWrapLength(-1);
	hFrame2->AddFrame(Ltime, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	Ltime->MoveResize(184,60,57,18);

	ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

	// graphics context changes
	Vcounts.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	gClient->GetColorByName("#000000",Vcounts.fForeground);
	gClient->GetColorByName("#c0c0c0",Vcounts.fBackground);
	Vcounts.fFillStyle = kFillSolid;
	Vcounts.fFont = ufont->GetFontHandle();
	Vcounts.fGraphicsExposures = kFALSE;
	uGC = gClient->GetGC(&Vcounts, kTRUE);

	Tcount = new TGTextEntry(hFrame2, new TGTextBuffer(15),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kDoubleBorder | kOwnBackground);
	Tcount->SetMaxLength(4096);
	Tcount->SetAlignment(kTextLeft);
	Tcount->Resize(83,Tcount->GetDefaultHeight());
	hFrame2->AddFrame(Tcount, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	Tcount->MoveResize(80,90,83,22);

	Lcount = new TGLabel(hFrame2,"counts");
	Lcount->SetTextJustify(36);
	Lcount->SetMargins(0,0,0,0);
	Lcount->SetWrapLength(-1);
	hFrame2->AddFrame(Lcount, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	Lcount->MoveResize(184,90,57,18);

	Vname.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	gClient->GetColorByName("#000000",Vname.fForeground);
	gClient->GetColorByName("#c0c0c0",Vname.fBackground);
	Vname.fFillStyle = kFillSolid;
	Vname.fFont = ufont->GetFontHandle();
	Vname.fGraphicsExposures = kFALSE;
	uGC = gClient->GetGC(&Vname, kTRUE);

	Tname = new TGTextEntry(hFrame2, new TGTextBuffer(15),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kDoubleBorder | kOwnBackground);
	Tname->SetMaxLength(4096);
	Tname->SetAlignment(kTextLeft);
	Tname->Resize(83,Tname->GetDefaultHeight());
	Tname->SetText("Data");
	hFrame2->AddFrame(Tname, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	Tname->MoveResize(80,150,83,22);

	Lname = new TGLabel(hFrame2,"file name");
	Lname->SetTextJustify(36);
	Lname->SetMargins(0,0,0,0);
	Lname->SetWrapLength(-1);
	hFrame2->AddFrame(Lname, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	Lname->MoveResize(184,150,57,18);

	Bok = new TGTextButton(hFrame2,"OK",M_OK);
	Bok -> Associate(this);
	hFrame2->AddFrame(Bok, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	Bok->MoveResize(300,60,50,20);
	Bclear = new TGTextButton(hFrame2,"Clear",M_CLEAR);
	Bclear-> Associate(this);
	hFrame2->AddFrame(Bclear, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	Bclear->MoveResize(300,90,50,20);

	tf->AddFrame(hFrame2, new TGLayoutHints(kLHintsCenterX,2,2,2,2));

	//***********************************************************************************//
	//set button
	AddFrame(fTab,  new TGLayoutHints(kLHintsCenterX,2,2,2,2));

	// Create a horizontal frame widget with buttons
	hFrame = new TGHorizontalFrame(this,200,40);
	fStartButton = new TGTextButton(hFrame,"Start", M_START);
	fStartButton -> Associate(this);
	hFrame->AddFrame(fStartButton,new TGLayoutHints(kLHintsCenterX,5,5,3,4));

	fPauseButton = new TGTextButton(hFrame,"Pause", M_PAUSE);
	fPauseButton -> Associate(this);
	fPauseButton->SetState(kButtonDisabled);
	hFrame->AddFrame(fPauseButton,new TGLayoutHints(kLHintsCenterX,5,5,3,4));

	fResetButton = new TGTextButton(hFrame,"Reset", M_RESET);
	fResetButton -> Associate(this);
	fResetButton->SetState(kButtonDisabled);
	hFrame->AddFrame(fResetButton,new TGLayoutHints(kLHintsCenterX,5,5,3,4)); 

	fStopButton = new TGTextButton(hFrame,"Stop", M_STOP);
	fStopButton -> Associate(this);
	fStopButton->SetState(kButtonDisabled);
	hFrame->AddFrame(fStopButton,new TGLayoutHints(kLHintsCenterX,5,5,3,4));

	AddFrame(hFrame, new TGLayoutHints(kLHintsCenterX,2,2,2,2));

	// Set a name to the main frame
	SetWindowName("VME DAQ");
	// Map all subwindows of main frame
	MapSubwindows();
	// Initialize the layout algorithm
	Resize(this->GetDefaultSize());
	// Map main frame
	MapWindow();
	do_setup();

}

gui::~gui()
{ 

	delete mydaq;
	delete myviewer;
	delete fStartButton;
	delete fResetButton;
	delete hFrame;
}

void gui ::CloseWindow()
{
	// Got close message for this MainFrame. Terminate the application
	// or returns from the TApplication event loop (depending on the
	// argument specified in TApplication::Run()).
	foutput->SaveFile("record.txt");
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
				do_start();
				break;
			case M_PAUSE:
				do_pause();
				break;
			case M_RESET: 
				foutput->AddLine("The data is reset!");
				StartTimer();
				mydaq->Reset();
				break;
			case M_STOP:
				do_stop();
				break;
			case M_SET:
				mydaq->SetHit(fchannel->GetNumber());
				break;
			case M_OK:
				do_setup();
				break;
			case M_CLEAR:
				Tcount->Clear();
				Ttime->Clear();
				break;
			default: break;
			}
			break;
		case kCM_MENU:
			switch (parm1) 
			{

			case M_HELP_ABOUT:
				{
					new about(fClient->GetRoot(),200,200);
				}
				break;
			default: break; 
			}
		default: break;
		}	    
		break;
	default: break;	
	}
	return kTRUE;
}
void gui::StartTimer()
{
	struct tm * timeinfo;
	time (&start);
	timeinfo = localtime ( &start );
	foutput->AddLine("DAQ starts at : ");
	foutput->AddLine(asctime (timeinfo));

}

double gui::StopTimer()
{
	struct tm * timeinfo;
	time (&stop);
	double dif = difftime (stop,start);
	timeinfo = localtime ( &stop );
	foutput->AddLine("DAQ stops at : ");
	foutput->AddLine(asctime (timeinfo));
	return dif;
}

void gui::do_start()
{	
	char *out_buffer;
	fStartButton->SetState(kButtonDisabled);
	fResetButton->SetState(kButtonUp);
	fPauseButton->SetState(kButtonUp);
	fSetButton->SetState(kButtonUp);
	fStopButton->SetState(kButtonUp);
	StartTimer();
	methods->SetEnabled(false);
	mydaq->SetMode(methods->GetSelected());
	mydaq->SetAdd(faddress->GetText());
	mydaq->SetHit(fchannel->GetNumber());
	mydaq->Reset();
	myviewer->Start();
	mydaq ->Start();
};

void gui::do_stop()
{
	StopTimer();
	foutput->AddLine("The data is recorded in file:");
	foutput->AddLine(mydaq->Write());
	mydaq ->Stop();
	myviewer->Stop();
	fResetButton->SetState(kButtonDisabled);
	fPauseButton->SetText("Pause");
	fPauseButton->SetState(kButtonDisabled);
	fSetButton->SetState(kButtonDisabled);
	fStopButton->SetState(kButtonDisabled);
	fStartButton->SetState(kButtonUp);
	methods->SetEnabled(true);
};

void gui::do_pause()
{
	mydaq ->Pause();
	if(!strcmp((fPauseButton->GetText())->GetString(),"Pause"))
	{
		foutput->AddLine("The DAQ is paused!");
		fPauseButton->SetText("Resume");
	}
	else 
	{
		foutput->AddLine("The DAQ is resumed!");
		fPauseButton->SetText("Pause");
	}
};

void gui::do_setup()
{
	switch(Rmode->GetSelected())
	{
	case 0:
		{
			foutput->AddLine("The DAQ is no limited!");
			mydaq->SetParamters(-1,-1,Tname->GetText());//no limitied
		}
		break;
	case 1:
		{
			mydaq->SetParamters(-1,atol(Tcount->GetText()),Tname->GetText());//time
			foutput->AddLine("The DAQ is time limited! the limit(sec) is:");
			foutput->AddLine(Ttime->GetText());
		}
		break;
	case 2:
		{
			mydaq->SetParamters(atol(Tcount->GetText()),-1,Tname->GetText());//counts
			foutput->AddLine("The DAQ is counts limited! the limit is:");
			foutput->AddLine(Tcount->GetText());
		}
		break;
	default: break;
	}
}
