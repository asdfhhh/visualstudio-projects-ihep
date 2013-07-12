void RunPi(Double_t intervals=10)
{
  gSystem->Load("CalcPiThread.so");

  // create the TThread instances
  
  gIntervals = intervals;
  printf("Intervals %f\n", gIntervals);
  
  TThread *th1 = new TThread("pi1",process,(void*)"0");
  TThread *th2 = new TThread("pi2",process,(void*)"1");

  th1->Run();
  th2->Run();
}   
