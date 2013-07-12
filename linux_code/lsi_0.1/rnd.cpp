#include "rnd.h"


rnd::rnd()
{  

    suiji=new TRandom(851126);
    
  }

rnd::~rnd()
{   delete suiji; 
	printf("The random test is exited!");
}

int rnd::GetRnd()
{
return suiji->Uniform(4096);

  }
