#ifndef rnd_H
#define rnd_H 1
#include "TRandom.h"

class rnd
{
 public:
     rnd();
	~rnd();
	int GetRnd();
private:
	TRandom*suiji;


};
#endif