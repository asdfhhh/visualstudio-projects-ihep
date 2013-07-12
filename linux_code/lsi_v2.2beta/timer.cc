#include "timer.h"

timer::timer()
{
	mTimer=0;
}
timer::~timer()
{
}
int timer::StartTimer()
{
	if(!mTimer){
		mTimer= new TThread("Timer",(void(*) (void *))&ThreadTimer,(void*) this);
		mTimer->Run();
		return 0;
	}
	return 1;
}
int timer::StopTimer()
{
	if(mTimer)
		{
			TThread::Delete(mTimer);
			delete mTimer;
			mTimer=0;
			return 0;
		}
	return 1;
}
void daq::Timer()
{
	sleep(timer_time);
	cout<<"Time up!"<<endl;
}
void daq::ThreadTimer(void* arg){
	// thread function which calls user specified action Func0
	TThread::SetCancelOn();
	TThread::SetCancelDeferred();
	daq* inst = (daq*) arg;
	Int_t meid=TThread::SelfId(); // get pthread id
	TThread::CancelPoint();
	inst->Timer(); // call the user defined threaded function
}
