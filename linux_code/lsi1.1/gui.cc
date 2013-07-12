#include "about.h"
#include "TCanvas.h"
#include "menu_setup.h"
#include "gui.h"

enum MessageTypes
{
	M_START,
	M_PAUSE,
	M_RESET,
	M_STOP,
	M_SET,
	M_FILE_OPEN,
	M_FILE_SAVE,
	M_FILE_SAVEAS,
	M_FILE_PRINT,
	M_FILE_PRINTSETUP,
	M_FILE_EXIT,

	M_TEST_SETUP,
	M_TEST_MSGBOX,
	M_TEST_SLIDER,
	M_TEST_SHUTTER,
	M_TEST_DIRLIST,
	M_TEST_FILELIST,
	M_TEST_PROGRESS,
	M_TEST_NUMBERENTRY,
	M_TEST_FONTDIALOG,
	M_TEST_NEWMENU,

	M_VIEW_ENBL_DOCK,
	M_VIEW_ENBL_HIDE,
	M_VIEW_DOCK,
	M_VIEW_UNDOCK,

	M_HELP_CONTENTS,
	M_HELP_SEARCH,
	M_HELP_ABOUT,

	M_CASCADE_1,
	M_CASCADE_2,
	M_CASCADE_3,

	M_NEW_REMOVEMENU

};
gui :: gui(const TGWindow *p, UInt_t w, UInt_t h)
: TGMainFrame(p, w, h)
{
	gui_time=-1;
	gui_counts=-1;

	mydaq = new daq();
	hFrame1 = new TGHorizontalFrame(this,500,300,kHorizontalFrame);
	hFrame1->SetName("hFrame1");
	hFrame1->SetLayoutBroken(kTRUE);

	fMenuDock = new TGDockableFrame(this);
	AddFrame(fMenuDock, new TGLayoutHints(kLHintsExpandX, 0, 0, 1,0));
	fMenuDock->SetWindowName("DAQ Set Menu");

	fMenuBarLayout = new TGLayoutHints(kLHintsTop | kLHintsExpandX);
	fMenuBarItemLayout = new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 4, 0, 0);
	fMenuBarHelpLayout = new TGLayoutHints(kLHintsTop | kLHintsRight);

	fMenuFile = new TGPopupMenu(fClient->GetRoot());
	fMenuFile->AddEntry("&Open...", M_FILE_OPEN);
	fMenuFile->AddEntry("&Save", M_FILE_SAVE);
	fMenuFile->AddEntry("S&ave as...", M_FILE_SAVEAS);
	fMenuFile->AddEntry("&Close", -1);
	fMenuFile->AddSeparator();
	fMenuFile->AddEntry("&Print", M_FILE_PRINT);
	fMenuFile->AddEntry("P&rint setup...", M_FILE_PRINTSETUP);
	fMenuFile->AddSeparator();
	fMenuFile->AddEntry("E&xit", M_FILE_EXIT);

	fMenuFile->DisableEntry(M_FILE_SAVEAS);
	fMenuFile->HideEntry(M_FILE_PRINT);


	fCascade2Menu = new TGPopupMenu(fClient->GetRoot());
	fCascade2Menu->AddEntry("ID = 2&3", M_CASCADE_1);
	fCascade2Menu->AddEntry("ID = 2&4", M_CASCADE_2);
	fCascade2Menu->AddEntry("ID = 2&5", M_CASCADE_3);

	fCascade1Menu = new TGPopupMenu(fClient->GetRoot());
	fCascade1Menu->AddEntry("ID = 4&1", 41);
	fCascade1Menu->AddEntry("ID = 4&2", 42);
	fCascade1Menu->AddEntry("ID = 4&3", 43);
	fCascade1Menu->AddSeparator();
	fCascade1Menu->AddPopup("Cascade&d 2", fCascade2Menu);

	fCascadeMenu = new TGPopupMenu(fClient->GetRoot());
	fCascadeMenu->AddEntry("ID = 5&1", 51);
	fCascadeMenu->AddEntry("ID = 5&2", 52);
	fCascadeMenu->AddEntry("ID = 5&3", 53);
	fCascadeMenu->AddSeparator();
	fCascadeMenu->AddPopup("&Cascaded 1", fCascade1Menu);

	fMenuTest = new TGPopupMenu(fClient->GetRoot());
	fMenuTest->AddLabel("Test different features...");
	fMenuTest->AddSeparator();
	fMenuTest->AddEntry("&Options", M_TEST_SETUP);
	fMenuTest->AddEntry("&Message Box...", M_TEST_MSGBOX);
	fMenuTest->AddEntry("&Sliders...", M_TEST_SLIDER);
	fMenuTest->AddEntry("Sh&utter...", M_TEST_SHUTTER);
	fMenuTest->AddEntry("&List Directory...", M_TEST_DIRLIST);
	fMenuTest->AddEntry("&File List...", M_TEST_FILELIST);
	fMenuTest->AddEntry("&Progress...", M_TEST_PROGRESS);
	fMenuTest->AddEntry("&Number Entry...", M_TEST_NUMBERENTRY);
	fMenuTest->AddEntry("F&ont Dialog...", M_TEST_FONTDIALOG);
	fMenuTest->AddSeparator();
	fMenuTest->AddEntry("Add New Menus", M_TEST_NEWMENU);
	fMenuTest->AddSeparator();
	fMenuTest->AddPopup("&Cascaded menus", fCascadeMenu);

	fMenuView = new TGPopupMenu(gClient->GetRoot());
	fMenuView->AddEntry("&Dock", M_VIEW_DOCK);
	fMenuView->AddEntry("&Undock", M_VIEW_UNDOCK);
	fMenuView->AddSeparator();
	fMenuView->AddEntry("Enable U&ndock", M_VIEW_ENBL_DOCK);
	fMenuView->AddEntry("Enable &Hide", M_VIEW_ENBL_HIDE);
	fMenuView->DisableEntry(M_VIEW_DOCK);

	fMenuDock->EnableUndock(kTRUE);
	fMenuDock->EnableHide(kTRUE);
	fMenuView->CheckEntry(M_VIEW_ENBL_DOCK);
	fMenuView->CheckEntry(M_VIEW_ENBL_HIDE);

	fMenuHelp = new TGPopupMenu(fClient->GetRoot());
	fMenuHelp->AddEntry("&Contents", M_HELP_CONTENTS);
	fMenuHelp->AddEntry("&Search...", M_HELP_SEARCH);
	fMenuHelp->AddSeparator();
	fMenuHelp->AddEntry("&About", M_HELP_ABOUT);

	fMenuNew1 = new TGPopupMenu();
	fMenuNew1->AddEntry("Remove New Menus", M_NEW_REMOVEMENU);

	fMenuNew2 = new TGPopupMenu();
	fMenuNew2->AddEntry("Remove New Menus", M_NEW_REMOVEMENU);

	// Menu button messages are handled by the main frame (i.e. "this")
	// ProcessMessage() method.
	fMenuFile->Associate(this);
	fMenuTest->Associate(this);
	fMenuView->Associate(this);
	fMenuHelp->Associate(this);
	fCascadeMenu->Associate(this);
	fCascade1Menu->Associate(this);
	fCascade2Menu->Associate(this);
	fMenuNew1->Associate(this);
	fMenuNew2->Associate(this);

	fMenuBar = new TGMenuBar(fMenuDock, 1, 1, kHorizontalFrame);
	fMenuBar->AddPopup("&File", fMenuFile, fMenuBarItemLayout);
	fMenuBar->AddPopup("&Tools", fMenuTest, fMenuBarItemLayout);
	fMenuBar->AddPopup("&View", fMenuView, fMenuBarItemLayout);
	fMenuBar->AddPopup("&Help", fMenuHelp, fMenuBarHelpLayout);

	fMenuDock->AddFrame(fMenuBar, fMenuBarLayout);

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

	AddFrame(hFrame1, new TGLayoutHints(kLHintsCenterX,2,2,2,2));

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

}

gui::~gui()
{ 

}

void gui ::CloseWindow()
{
	// Got close message for this MainFrame. Terminate the application
	// or returns from the TApplication event loop (depending on the
	// argument specified in TApplication::Run()).
	foutput->SaveFile("record.txt");
	delete mydaq;
	delete fStartButton;
	delete fResetButton;
	delete hFrame;
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
			case M_TEST_SETUP:
				{
					new msetup(fClient->GetRoot(),400,200,this);
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
	mydaq->SetParamters(gui_time,gui_counts);
	mydaq->SetAdd(faddress->GetText());
	mydaq->SetHit(fchannel->GetNumber());
	mydaq ->Getdata();
};

void gui::do_stop()
{
	StopTimer();
	mydaq ->Stop();
	foutput->AddLine("The data is recorded in file:");
	foutput->AddLine(mydaq->Write());
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

