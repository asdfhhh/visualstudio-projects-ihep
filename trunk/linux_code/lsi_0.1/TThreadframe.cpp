#include "TThreadframe.h"



//ClassImp(TThreadframe)



TThreadframe::TThreadframe(UInt_t threadnum){
  if(threadnum>4) threadnum=4; 
  mThreadnum=threadnum;
  mThread0=0;
  mThread1=0;
  mThread2=0;
  mThread3=0;
  mThreadrun=kFALSE;
} 





TThreadframe::~TThreadframe(){
  Threadstop();  
}




/////////////////////////////////////////////////////////////
// threaded methods calling user functions: 


void TThreadframe::Thread0(void* arg){
  // thread function which calls user specified action Func0
  TThread::SetCancelOn();
  TThread::SetCancelDeferred();
  TThreadframe* inst = (TThreadframe*) arg;
  Int_t meid=TThread::SelfId(); // get pthread id
  cout << "\nThread 0, id:" <<meid<< " is running..\n"<<endl;
  while(inst->GetThreadRun()){
	// loop keeps thread alive...
	TThread::CancelPoint();
	inst->Func0(); // call the user defined threaded function
  }

}

void TThreadframe::Thread1(void* arg){
  // thread function which calls user specified action Func0
  TThread::SetCancelOn();
  TThread::SetCancelDeferred();
  TThreadframe* inst = (TThreadframe*) arg;
  Int_t meid=TThread::SelfId(); // get pthread id
  cout << "\nThread 1, id:" <<meid<< " is running..\n"<<endl;
  while(inst->GetThreadRun()){
	// loop keeps thread alive...
	TThread::CancelPoint();
	inst->Func1(); // call the user defined threaded function
  }

}

void TThreadframe::Thread2(void* arg){
  // thread function which calls user specified action Func0
  TThread::SetCancelOn();
  TThread::SetCancelDeferred();
  TThreadframe* inst = (TThreadframe*) arg;
  Int_t meid=TThread::SelfId(); // get pthread id
  cout << "\nThread 2, id: " <<meid<< " is running..\n"<<endl;
  while(inst->GetThreadRun()){
	// loop keeps thread alive...
	TThread::CancelPoint();
	inst->Func2(); // call the user defined threaded function
  }

}

void TThreadframe::Thread3(void* arg){
  // thread function which calls user specified action Func0
  TThread::SetCancelOn();
  TThread::SetCancelDeferred();
  TThreadframe* inst = (TThreadframe*) arg;
  Int_t meid=TThread::SelfId(); // get pthread id
  cout << "\nThread 3, id:"<<meid<< " is running..\n"<<endl;
  while(inst->GetThreadRun()){
	// loop keeps thread alive...
	TThread::CancelPoint();
	inst->Func3(); // call the user defined threaded function
  }

}



///////////////////////////////////////////////////////////////////
// default user functions running within threaded methods, overwrite these:

void TThreadframe::Func0(){ 
  cout << "Default Threadfunc 0 running, please overwrite in derived class"<<endl;
  gSystem->Sleep(1000);
}



void TThreadframe::Func1(){ 
  cout << "Default Threadfunc 1 running, please overwrite in derived class"<<endl;
  gSystem->Sleep(2000);


}


void TThreadframe::Func2(){ 
  cout << "Default Threadfunc 2 running, please overwrite in derived class"<<endl;
  gSystem->Sleep(3000);
}

void TThreadframe::Func3(){
  cout << "Default Threadfunc 3 running, please overwrite in derived class"<<endl;
  gSystem->Sleep(4000);
 
}

/////////////////////////////

Int_t TThreadframe::Threadstart(){
  // start all threads
  mThreadrun=kTRUE;
  UInt_t number=1;
  if(!mThread0){
	mThread0= new TThread("mythread 0",
						  (void(*) (void *))&Thread0,
						  (void*) this);
	mThread0->Run();
		
  }
  if (++number>mThreadnum) return 0;
  // check number of active threads; better: keep TThread pointers  in array
  // to have more flexibility, we omitted this for tutorial reasons... 

  if(!mThread1){
	mThread1= new TThread("mythread 1",
						  (void(*) (void *))&Thread1,
						  (void*) this);
	mThread1->Run();
	
  }
  if (++number>mThreadnum) return 0;
  if(!mThread2){
	mThread2= new TThread("mythread 2",
						  (void(*) (void *))&Thread2,
						  (void*) this);
	mThread2->Run();
		
  }
  if (++number>mThreadnum) return 0;
  if(!mThread3){
	mThread3= new TThread("mythread 3",
						  (void(*) (void *))&Thread3,
						  (void*) this);
	mThread3->Run();
  }
  return 0;
}

 


Int_t TThreadframe::Threadstop(){
  // stop all active threads 
  mThreadrun=kFALSE;	// aborting flag
  gSystem->Sleep(1000); // wait a while for threads to halt
  UInt_t number=1;
  if(mThread0){ 
	TThread::Delete(mThread0);
	delete mThread0;
	mThread0=0;
  }
  if (++number>mThreadnum) return 0;
  // check number of active threads; better: keep TThread pointers  in array
  // to have more flexibility, we omitted this for tutorial reasons..
  if(mThread1){ 
	TThread::Delete(mThread1);
	delete mThread1;
	mThread1=0;
  }
  if (++number>mThreadnum) return 0;
  if(mThread2){ 
	TThread::Delete(mThread2);
	delete mThread2;
	mThread2=0;
  }
  if (++number>mThreadnum) return 0;
  if(mThread3){ 
	TThread::Delete(mThread3);
	delete mThread3;
	mThread3=0;
  }
  return 0;

} 

