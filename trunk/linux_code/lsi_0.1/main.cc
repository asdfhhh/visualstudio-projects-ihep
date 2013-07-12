#include<iostream>
#include<fstream>
#include "TApplication.h"
#include "TCanvas.h"
#include "daq.h"
#include "gui.h"
#include "viewer.h"
#include "TThread.h"
#include<time.h>
#include<signal.h>
TH1F*total=0;
viewer*fviewer;
void *top(void *)
{

	while(1)
	{
		fviewer->draw(total);
		sleep(1);
	}
	return 0;
}

int main(int argc, char **argv)
{

	TApplication theApp("App", &argc, argv);   


	// top thread
	TThread *thp = new TThread("top",top);
	gui* mainframe = new gui(gClient->GetRoot(),0,0);
	fviewer=new viewer(gClient->GetRoot(),1,0);
	thp->Run();
	sleep(1);
	theApp.Run();
	sleep(1);
	thp->SetCancelAsynchronous();
	thp->Kill();
	printf("The END...\n");
	return 0;
}
