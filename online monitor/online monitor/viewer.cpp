#include "viewer.h"
#include "TCanvas.h"
#include "TThread.h"

viewer :: viewer(const TGWindow *p, UInt_t w, UInt_t h)
		   : TGMainFrame(p, w, h)
{
	
	
	SetCleanup(kDeepCleanup);

   // MainFrame Contructor Function
// Create Main Frame
// Create canvas widget   
fEcanvas = new TRootEmbeddedCanvas("Ecanvas",this,600,400);
AddFrame(fEcanvas, new TGLayoutHints(kLHintsExpandX| kLHintsExpandY,
                                            10,10,10,1));

// Set a name to the main frame
SetWindowName("The hit map");
// Map all subwindows of main frame
MapSubwindows();
// Initialize the layout algorithm
Resize(this->GetDefaultSize());
// Map main frame
MapWindow();
fCanvas = fEcanvas->GetCanvas();
}

void viewer::draw(TH2F*h1)
{
fCanvas->cd();
if(h1!=0)h1->Draw("LEGO2");
fCanvas->Update();
}

viewer::~viewer()
{
}

