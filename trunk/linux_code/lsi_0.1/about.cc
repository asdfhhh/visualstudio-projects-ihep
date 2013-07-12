#include "about.h"

about :: about(const TGWindow *p, UInt_t w, UInt_t h)
: TGMainFrame(p, w, h)
{


	SetCleanup(kDeepCleanup);

	// MainFrame Contructor Function
	// Create Main Frame
	// Create canvas widget   
	TGLabel *fLabel = new TGLabel(this,"VME DAQ\nfanrr@ihep.ac.cn");
	fLabel->SetTextJustify(36);
	fLabel->SetMargins(0,0,0,0);
	fLabel->SetWrapLength(-1);
	fLabel->MoveResize(16,16,224,144);

	AddFrame(fLabel, new TGLayoutHints(kLHintsExpandX| kLHintsExpandY,
		10,10,10,1));

	// Set a name to the main frame
	SetWindowName("about VME DAQ");
	// Map all subwindows of main frame
	MapSubwindows();
	// Initialize the layout algorithm
	Resize(this->GetDefaultSize());
	// Map main frame
	MapWindow();

}
about::~about()
{
};
