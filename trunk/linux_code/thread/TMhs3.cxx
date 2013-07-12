#include "TMhs3.h"

ClassImp(TMhs3)      



TMhs3::TMhs3(): TThreadframe(3)
{
   mTotal0=0;
  mPad2=0;
  mPad1=0;
  mC1=0;
  CreateGraphics();
}

TMhs3::~TMhs3()
{
  DeleteGraphics();
}


Int_t TMhs3::Threadstart()
{
  cout <<"TMhs3 threadstart"<<endl;
  Int_t val=0;
  val+=CreateGraphics();
  val+=TThreadframe::Threadstart();
  return val;
}

Int_t TMhs3::Threadstop()
{
  cout <<"TMhs3 threadstop"<<endl;
  Int_t val=0;
  val+=TThreadframe::Threadstop();
  val+=DeleteGraphics();
  return val;
}

Int_t TMhs3::CreateGraphics()
{
  // create all "global" graphical objects
  cout <<"creating graphics.."<<endl;
  if(!mC1){
    mC1 = new TCanvas("c1","The HSUM example",1200,400);   
    cout <<"canvas"<<endl;
  }
  if(!mPad1){
    mC1->cd();
    mPad1 = new TPad("pad1","This is pad1",0.02,0.02,0.48,0.83,33);
    cout <<"pad1"<<endl;
  }
  if(!mPad2){
    mC1->cd();
    mPad2 = new TPad("pad2","This is pad2",0.52,0.02,0.98,0.83,33);
    cout <<"pad2"<<endl;
  }
  if(!mTotal0){  
     mTotal0  = new TH1F("total","This is the total distribution",100,-4,4);
     cout <<"total"<<endl;
   }
  mC1->Modified();
  mC1->Update();
return 0;
}

Int_t TMhs3::DeleteGraphics()
{
  // delete all "global" graphical objects
   cout <<"deleting graphics.."<<endl;
  if(mTotal0){  
    delete mTotal0;
    mTotal0=0;
  }
  if(mPad2){
    delete mPad2;
    mPad2=0;
  }
  if(mPad1){
    delete mPad1;
    mPad1=0;
  }
  if(mC1){
    delete mC1;
    mC1=0;
  }
  return 0;
}




void TMhs3::Func0(){
  // first threaded function (mhs in other example)
  TThread::Printf("Start of mhs0 \n");
  mC1->cd();
  mC1->SetGrid();
  mPad1->Draw();
  
  TThread::Lock();
  TH1F *main   = new TH1F("main","Main contributor",100,-4,4);
  TThread::UnLock();
  
  mTotal0->Sumw2();  
  mTotal0->SetMarkerStyle(21);
  mTotal0->SetMarkerSize(0.7);
  main->SetFillColor(16);

// Fill histograms randomly
  gRandom->SetSeed();
  const Int_t kUPDATE = 100;
  Float_t xmain;
  for ( Int_t i=0; i<=100000; i++) {
    //for ( Int_t i=0;; i++) {

    if(!mThreadrun)
      TThread::Exit(); 
     xmain = gRandom->Gaus(-1,1.5);
     TThread::Lock();
     main->Fill(xmain);
     mTotal0->Fill(xmain);
     TThread::UnLock();
     if (!(i%kUPDATE)) {
        if (i == kUPDATE) {
	   mPad1->cd();
           mTotal0->Draw("e1p");
        }
	mPad1->cd();
	mTotal0->DrawCopy("e1p");
	mC1->Modified();
	mC1->Update();
     }
     gSystem->Sleep(1);
  }
  TThread::Printf("End of mhs\n");

  mC1->Modified();
  mC1->Update();

}

void TMhs3::Func1(){
  // second threaded function (mhs1 in other example)
  TThread::Printf("Start of mhs1 \n");
 
  TThread::Lock();
  TH1F *s1     = new TH1F("s1","This is the first signal",100,-4,4);
  TH1F *s2     = new TH1F("s2","This is the second signal",100,-4,4);
  TThread::UnLock();
  
  s1->SetFillColor(42);
  s2->SetFillColor(46);

// Fill histograms randomly
  gRandom->SetSeed();
  Float_t xs1, xs2;
  for ( Int_t i=0; i<=100000; i++) {
  //for ( Int_t i=0;; i++) {
    if(!mThreadrun)
      TThread::Exit();
       xs1   = gRandom->Gaus(-0.5,0.5);
     xs2   = gRandom->Gaus(1,0.3);
     TThread::Lock();
     s1->Fill(xs1,0.3);
     s2->Fill(xs2,0.2);
     mTotal0->Fill(xs1,0.3);
     mTotal0->Fill(xs2,0.2);
     TThread::UnLock();
     gSystem->Sleep(6);
  }
  TThread::Printf("End of mhs1\n");

  mPad1->cd();
  mTotal0->DrawCopy("e1p");
  mC1->Modified();
  mC1->Update();

}

void TMhs3::Func2(){
  // third threaded function (mhs2 in other example)
  TThread::Printf("Start of mhs2\n");
  mC1->cd();
  mPad2->Draw();

  // Create some histograms.
  TThread::Lock();
  TH1F *total  = new TH1F("total2","This is the total distribution",100,-4,4);
  TH1F *main   = new TH1F("main2","Main contributor",100,-4,4);
  TH1F *s1     = new TH1F("s12","This is the first signal",100,-4,4);
  TH1F *s2     = new TH1F("s22","This is the second signal",100,-4,4);
  TThread::UnLock();

  total->Sumw2();  
  total->SetMarkerStyle(21);
  total->SetMarkerSize(0.7);
  main->SetFillColor(16);
  s1->SetFillColor(42);
  s2->SetFillColor(46);

// Fill histograms randomly
  gRandom->SetSeed();
  const Int_t kUPDATE = 100;
  Float_t xs1, xs2, xmain;
  for ( Int_t i=0; i<=100000; i++) {
    //for ( Int_t i=0; ; i++) {
    if(!mThreadrun)
      TThread::Exit();
       xmain = gRandom->Gaus(-1,1.5);
     xs1   = gRandom->Gaus(-0.5,0.5);
     xs2   = gRandom->Gaus(1,0.3);
     main->Fill(xmain);
     s1->Fill(xs1,0.3);
     s2->Fill(xs2,0.2);
     total->Fill(xmain);
     total->Fill(xs1,0.3);
     total->Fill(xs2,0.2);
     if (!(i%kUPDATE)) {
        if (i == kUPDATE) {
	   mPad2->cd();
           total->Draw("e1p");
	   }
	
	mPad2->cd();
	total->DrawCopy("e1p");
	mC1->Modified();
	mC1->Update();
  
     }
     gSystem->Sleep(1);
  }
  TThread::Printf("End of mhs2\n");
  mC1->Modified();
  mC1->Update();




}
