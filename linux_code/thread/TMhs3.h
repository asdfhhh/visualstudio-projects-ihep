#include "TThreadframe.h"

#include "TH1.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TRandom.h"
#include "TBenchmark.h"

class TMhs3: public TThreadframe{
 private:
   TCanvas *mC1;
  TPad *mPad2;
  TPad *mPad1;
  TH1F *mTotal0;

  Int_t CreateGraphics();
  Int_t DeleteGraphics();
 public:
  TMhs3();
  virtual ~TMhs3();
  void Func0();	// functions running within thread
  void Func1(); // dito; 	
  void Func2();
  Int_t Threadstart();
  Int_t Threadstop();

ClassDef(TMhs3,0)
};
