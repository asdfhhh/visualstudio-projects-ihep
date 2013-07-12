#ifndef __THREADFRAME__
#define __THREADFRAME__ 1 

// TThreadframe: tutorial base class running member functions as root TThreads

//********************************************************************
// date:	23.02.2000
// library:	libTThreadframe.so
// version:	1.0
// authors:	Joern Adamczewski
// libraries:	libThread.so libpthread.so            
// makefile:	Makefile.TMhs3
//		generates libraries libTThreadframe.so and libTMhs3.so
//		and test execuable TMhs3run
// description:	ctor argument indicates number of threads to start (1...4)
//		method Threadstart() launches thread instances
//		methods Thread0...Thread3 are the functions that run
//		as thread; virtual methods Func0...Func3 are called from
//		these and can be overwritten in derived class (e.g. TMhs3) 
//		method Threadstop() deletes threads
//              
// usage:	after making the shared library, execute 
//		macro TMhs3demo.C from root interpreter, or use 
//		test executable TMhs3run   
//***********************************************************************


#include <iostream>
#include <stdio.h>
using namespace std;
#include "TThread.h" 
#include "TApplication.h"
#include "TROOT.h"
#include "TRint.h"
#include "TObject.h"
#include "TTimer.h"



class TThreadframe{
 private:
  
  UInt_t mThreadnum; 			//number of threads in object
  TThread* mThread0;		// thread pointer
  TThread* mThread1;		// thread pointer
  TThread* mThread2;		// thread pointer
  TThread* mThread3;		// thread pointer
  // better: keep thread pointers within array; is omitted here
  // for tutorial reasons

 protected:
  Bool_t mThreadrun; // flags for quick abort of loops within threads
                    // may also use different flags for each thread	
 public:
  
  TThreadframe(UInt_t threadnum=4);
  virtual ~TThreadframe();
 
  static void Thread0(void* arg); // functions running as threads
  static void Thread1(void* arg);  
  static void Thread2(void* arg); 
  static void Thread3(void* arg);

  virtual void Func0();	// user functions called from Thread0
  virtual void Func1(); 	
  virtual void Func2();	
  virtual void Func3();	

  virtual Int_t Threadstart();  // launch all threads 
  virtual Int_t Threadstop();   // stop all threads
 
  Bool_t GetThreadRun() 
    {return mThreadrun;}


//ClassDef(TThreadframe,0)
};





#endif
