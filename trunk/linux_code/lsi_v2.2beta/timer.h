#ifndef TIMER_H
#define TIMER_H 1
#include "TThread.h"
class timer
{
	private:
		int timer_time;
		TThread* mTimer;
		static void ThreadTimer(void*arg);
	public:
		timer();
		~timer();
		virtual void Timer();	
		int StartTimer();
		void SetTimer(int d_time){timer_time=d_time;};
		int StopTimer();
}
#endif
