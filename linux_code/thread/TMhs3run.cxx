#include <iostream>
#include <stdlib.h>
using namespace std;
#include "TROOT.h"
#include "TRint.h"
#include "TApplication.h"   



#include "TMhs3.h"


      
extern void InitGui();
VoidFuncPtr_t initfuncs[] = {InitGui, 0 };


TROOT threadtest("threadtest","Test of threads", initfuncs);    
 


int main(int argc, char **argv){
   TApplication theApp("App", &argc, argv);       
   //TThreadframe* mytestclass=new TThreadframe; // for base class test only
   TMhs3* mytestclass=new TMhs3; // test derived class running mhs3 example
 mytestclass->Threadstart();
 theApp.Run();
 return 0;
}



 
