#include "menu_setup.h"
enum MessageTypes
{
	M_OK,
	M_CANCEL
};

msetup :: msetup(const TGWindow *p, UInt_t w, UInt_t h,gui*pgui)
: TGMainFrame(p, w, h)
{
	fgui=pgui;


	SetCleanup(kDeepCleanup);

	hFrame1 = new TGHorizontalFrame(this,300,150,kHorizontalFrame);
	hFrame1->SetName("hFrame1");
	hFrame1->SetLayoutBroken(kTRUE);

	// MainFrame Contructor Function
	// Create Main Frame
	// Create canvas widget   
	Rmode = new TGComboBox(hFrame1,-1,kHorizontalFrame | kSunkenFrame | kDoubleBorder | kOwnBackground);
	Rmode->SetName("limited");
	Rmode->AddEntry("no limited ",0);
	Rmode->AddEntry("time limited ",1);
	Rmode->AddEntry("counts limited ",2);
	Rmode->Resize(102,22);
	Rmode->Select(0);
	hFrame1->AddFrame(Rmode, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	Rmode->MoveResize(80,32,105,19);

	// will reflect user font changes
	ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

	// will reflect user GC changes
	// graphics context changes
/*	Vtime.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	gClient->GetColorByName("#000000",Vtime.fForeground);
	gClient->GetColorByName("#c0c0c0",Vtime.fBackground);
	Vtime.fFillStyle = kFillSolid;
	Vtime.fFont = ufont->GetFontHandle();
	Vtime.fGraphicsExposures = kFALSE;
	uGC = gClient->GetGC(&Vtime, kTRUE);
*/
	Ttime = new TGTextEntry(hFrame1, new TGTextBuffer(15),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kDoubleBorder | kOwnBackground);
	Ttime->SetMaxLength(4096);
	Ttime->SetAlignment(kTextLeft);
	Ttime->Resize(83,Ttime->GetDefaultHeight());
	hFrame1->AddFrame(Ttime, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	Ttime->MoveResize(80,60,83,22);


	Ltime = new TGLabel(hFrame1,"time");
	Ltime->SetTextJustify(36);
	Ltime->SetMargins(0,0,0,0);
	Ltime->SetWrapLength(-1);
	hFrame1->AddFrame(Ltime, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	Ltime->MoveResize(184,60,57,18);

	ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

	// graphics context changes
/*	Vcounts.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
	gClient->GetColorByName("#000000",Vcounts.fForeground);
	gClient->GetColorByName("#c0c0c0",Vcounts.fBackground);
	Vcounts.fFillStyle = kFillSolid;
	Vcounts.fFont = ufont->GetFontHandle();
	Vcounts.fGraphicsExposures = kFALSE;
	uGC = gClient->GetGC(&Vcounts, kTRUE);
*/
	Tcount = new TGTextEntry(hFrame1, new TGTextBuffer(15),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kDoubleBorder | kOwnBackground);
	Tcount->SetMaxLength(4096);
	Tcount->SetAlignment(kTextLeft);
	Tcount->Resize(83,Tcount->GetDefaultHeight());
	hFrame1->AddFrame(Tcount, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	Tcount->MoveResize(80,90,83,22);

	Lcount = new TGLabel(hFrame1,"counts");
	Lcount->SetTextJustify(36);
	Lcount->SetMargins(0,0,0,0);
	Lcount->SetWrapLength(-1);
	hFrame1->AddFrame(Lcount, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
	Lcount->MoveResize(184,90,57,18);

	AddFrame(hFrame1, new TGLayoutHints(kLHintsCenterX,2,2,2,2));

	hFrame = new TGHorizontalFrame(this,200,40);

	Bok = new TGTextButton(hFrame,"OK",M_OK);
	Bok -> Associate(this);
	hFrame->AddFrame(Bok, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));

	Bcancel = new TGTextButton(hFrame,"Cancel",M_CANCEL);
	Bcancel-> Associate(this);
	hFrame->AddFrame(Bcancel, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));


	AddFrame(hFrame, new TGLayoutHints(kLHintsCenterX,2,2,2,2));

	SetWindowName("SETUP");
	// Map all subwindows of main frame
	MapSubwindows();
	// Initialize the layout algorithm
	Resize(this->GetDefaultSize());
	// Map main frame
	MapWindow();
}

msetup::~msetup()
{
}

void msetup ::CloseWindow()
{
	// Got close message for this MainFrame. Terminate the application
	// or returns from the TApplication event loop (depending on the
	// argument specified in TApplication::Run()).
	gROOT->SetInterrupt();
		delete hFrame1;
	delete Rmode;
	delete ufont;
	delete uGC; 
	delete Ttime ;
	delete Ltime ;
	delete Tcount;
	delete Lcount;
	delete hFrame;
	delete Bok ;
	delete Bcancel;
	DeleteWindow();
}

Bool_t msetup :: ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2)
{
	switch(GET_MSG(msg))
	{
	case kC_COMMAND:
		switch(GET_SUBMSG(msg))
		{
		case kCM_BUTTON: 
			switch(parm1)
			{

			case M_OK:
				do_setup();
				CloseWindow();
				break;
			case M_CANCEL:
				DeleteWindow();
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

void msetup::do_setup()
{
	switch(Rmode->GetSelected())
	{
	case 0:
		break;
	case 1:
		{
			fgui->set_parameters(atol(Ttime->GetText()),-1);//time
		}
		break;
	case 2:
		{
			fgui->set_parameters(-1,atol(Tcount->GetText()));//counts
		}
		break;
	default: break;
	}
}
