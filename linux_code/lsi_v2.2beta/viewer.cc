#include "viewer.h"
#include "TCanvas.h"
extern TH1F*total;
viewer :: viewer(const TGWindow *p, UInt_t w, UInt_t h)
		   : TGMainFrame(p, w, h),runflag(0)
{
vmTh=0;	
	
	SetCleanup(kDeepCleanup);

   // MainFrame Contructor Function
// Create Main Frame
// Create canvas widget   
fEcanvas = new TRootEmbeddedCanvas("Ecanvas",this,600,400);
AddFrame(fEcanvas, new TGLayoutHints(kLHintsExpandX| kLHintsExpandY,
                                            10,10,10,1));

// Set a name to the main frame
SetWindowName("the data viewer of VME DAQ");
// Map all subwindows of main frame
MapSubwindows();
// Initialize the layout algorithm
Resize(this->GetDefaultSize());
// Map main frame
MapWindow();
fCanvas = fEcanvas->GetCanvas();

}

void viewer::draw(TH1F*h1)
{
fCanvas->cd();
while(runflag)
{
h1=total;
if(h1!=0)
	{
	h1->Draw();
	fCanvas->Update();
	sleep(0.1);
	}
}
}

viewer::~viewer()
{

}

void viewer::Thread(void* arg)
{
        // thread function which calls user specified action Func0
         TThread::SetCancelOn();
         TThread::SetCancelDeferred();
         viewer* inst = (viewer*) arg;
         Int_t meid=TThread::SelfId(); // get pthread id
         TThread::CancelPoint();
	 inst->draw(total); // call the user defined threaded function
}

int viewer::Start(){
        if(!vmTh){
				runflag=true;
                vmTh= new TThread("draw",(void(*) (void *))&Thread,(void*) this);
                vmTh->Run();
                return 0;
        }
        return 1;
}

int viewer::Stop()
{
	if(vmTh)
	{
		//TThread::Delete(vmTh);
		//delete vmTh;
		vmTh=0;
		return 0;
	}
	return 1;
}
