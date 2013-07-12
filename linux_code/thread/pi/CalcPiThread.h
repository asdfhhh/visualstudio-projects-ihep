#include <iostream>
using namespace std;
#include "TThread.h"

extern Double_t gPi;
extern Double_t gIntervals;

void *process(void *arg);
