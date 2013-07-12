#include "CalcPiThread.h"

Double_t gPi = 0.0;
Double_t gIntervals = 1.0;

void *process(void *arg)
{
  Double_t width, localsum;
  Int_t i;
  Int_t iproc = (*((char *) arg) - '0');
  
  printf("Intervals %f\n", gIntervals);
  
  // Set Width
  width = 1.0/gIntervals;
  
  // Do the local computations 
  
  localsum = 0.;
  for(i = iproc; i < gIntervals; i += 2)
    {
      Double_t x = (i + 0.5) * width;
      localsum += 4.0 / (1.0 + x * x);
    }
  
  localsum *= width;
  
  TThread::Lock();
  gPi += localsum;
  printf("Current Estimation of pi is %20.18f\n", gPi);
  TThread::UnLock();
  
  return (0);
}
