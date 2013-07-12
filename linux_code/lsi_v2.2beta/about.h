#ifndef about_H
#define about_H 1
#include <Riostream.h>
#include <TGClient.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TRint.h>
#include <TROOT.h>
#include "daq.h"
#include "TH1F.h"
#include "TGIcon.h"
#include <time.h>
#ifndef ROOT_TGFrame
#include "TGFrame.h"
#endif
#ifndef ROOT_TGLabel
#include "TGLabel.h"
#endif

class about   : public TGMainFrame
{
 private:

public:
  about(const TGWindow *p, UInt_t w, UInt_t h);
TGIcon *logo;
	virtual ~about();
};
#endif
