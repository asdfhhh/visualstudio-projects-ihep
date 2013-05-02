#include<iostream>
#include<fstream>
#include "TApplication.h"
#include "gui.h"
#include "viewer.h"

int main(int argc, char **argv)
{
    TApplication theApp("App", &argc, argv);   
    gui* mainframe = new gui(gClient->GetRoot(),0,0);
    theApp.Run();
   return 0;
}
