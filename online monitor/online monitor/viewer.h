#pragma once
#include <Windows4Root.h>
#include <Riostream.h>
#include <TGClient.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TRint.h>
#include <TROOT.h>
#include "TH2F.h"
#include <time.h>
#ifndef ROOT_TGFrame
#include "TGFrame.h"
#endif



#ifndef ROOT_TGButton
#include "TGButton.h"
#endif

#include "TRootEmbeddedCanvas.h"

class viewer   : public TGMainFrame
{
 private:
  TRootEmbeddedCanvas*fEcanvas;
  TCanvas *fCanvas;
 public:
  viewer(const TGWindow *p, UInt_t w, UInt_t h);
	virtual ~viewer();
	virtual void draw( TH2F*);
};
