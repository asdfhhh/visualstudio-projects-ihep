#ifndef viewer_H
#define viewer_H 1
#include <Riostream.h>
#include <TGClient.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TRint.h>
#include <TROOT.h>
#include "TH1F.h"
#include <time.h>
#include "TGFrame.h"
#include "TGButton.h"
#include "TRootEmbeddedCanvas.h"

class viewer   : public TGMainFrame
{
 private:
  TRootEmbeddedCanvas*fEcanvas;
  TCanvas *fCanvas;
 public:
  viewer(const TGWindow *p, UInt_t w, UInt_t h);
	virtual ~viewer();
	virtual void draw( TH1F*);
};
#endif
