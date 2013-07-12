#ifndef msetup_H
#define msetup_H 1
#include <Riostream.h>
#include <TGClient.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TRint.h>
#include <TROOT.h>

#include <time.h>
#include "gui.h"
#include "daq.h"

class msetup   : public TGMainFrame
{
private:
	TGHorizontalFrame*hFrame1;
	TGComboBox *Rmode;
	TGFont *ufont;
	TGGC   *uGC; 
	GCValues_t Vtime;
	TGTextEntry *Ttime ;
	TGLabel *Ltime ;
	GCValues_t Vcounts;
	TGTextEntry *Tcount;
	TGLabel *Lcount;
	TGHorizontalFrame*hFrame;
	TGTextButton *Bok ;
	TGTextButton *Bcancel;
	void do_setup();
	gui*fgui;
public:
	msetup(const TGWindow *p, UInt_t w, UInt_t h);
	msetup(const TGWindow *p, UInt_t w, UInt_t h,gui* );
	virtual ~msetup();
	virtual void            CloseWindow();
	virtual Bool_t          ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2);
};
#endif
