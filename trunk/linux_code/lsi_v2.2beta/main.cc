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
int main(int argc, char **argv)
{

	TApplication theApp("App", &argc, argv);   
	gui* mainframe = new gui(gClient->GetRoot(),0,0);
	theApp.Run();
	printf("The END...\n");
	return 0;
}
