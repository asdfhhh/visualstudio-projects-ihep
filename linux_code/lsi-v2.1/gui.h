#ifndef gui_H
#define gui_H 1
#include <Riostream.h>
#include <TGClient.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TRint.h>
#include <TROOT.h>
#include "daq.h"
#include "viewer.h"
#include "TH1F.h"
#include <time.h>
#ifndef ROOT_TGFrame
#include "TGFrame.h"
#endif

#ifndef ROOT_TGDockableFrame
#include "TGDockableFrame.h"
#endif
#ifndef ROOT_TGMenu
#include "TGMenu.h"
#endif
#ifndef ROOT_TGMdiDecorFrame
#include "TGMdiDecorFrame.h"
#endif
#ifndef ROOT_TG3DLine
#include "TG3DLine.h"
#endif
#ifndef ROOT_TGMdiFrame
#include "TGMdiFrame.h"
#endif
#ifndef ROOT_TGMdiMainFrame
#include "TGMdiMainFrame.h"
#endif
#ifndef ROOT_TGMdiMenu
#include "TGMdiMenu.h"
#endif
#ifndef ROOT_TGListBox
#include "TGListBox.h"
#endif
#ifndef ROOT_TGNumberEntry
#include "TGNumberEntry.h"
#endif
#ifndef ROOT_TGScrollBar
#include "TGScrollBar.h"
#endif
#ifndef ROOT_TGComboBox
#include "TGComboBox.h"
#endif
#ifndef ROOT_TGuiBldHintsEditor
#include "TGuiBldHintsEditor.h"
#endif
#ifndef ROOT_TGuiBldNameFrame
#include "TGuiBldNameFrame.h"
#endif
#ifndef ROOT_TGFrame
#include "TGFrame.h"
#endif
#ifndef ROOT_TGFileDialog
#include "TGFileDialog.h"
#endif
#ifndef ROOT_TGShutter
#include "TGShutter.h"
#endif
#ifndef ROOT_TGButtonGroup
#include "TGButtonGroup.h"
#endif
#ifndef ROOT_TGCanvas
#include "TGCanvas.h"
#endif
#ifndef ROOT_TGuiBldEditor
#include "TGuiBldEditor.h"
#endif
#ifndef ROOT_TGColorSelect
#include "TGColorSelect.h"
#endif
#ifndef ROOT_TGTextEdit
#include "TGTextEdit.h"
#endif
#ifndef ROOT_TGButton
#include "TGButton.h"
#endif
#ifndef ROOT_TGFSComboBox
#include "TGFSComboBox.h"
#endif
#ifndef ROOT_TGLabel
#include "TGLabel.h"
#endif
#ifndef ROOT_TGView
#include "TGView.h"
#endif
#ifndef ROOT_TGMsgBox
#include "TGMsgBox.h"
#endif
#ifndef ROOT_TRootGuiBuilder
#include "TRootGuiBuilder.h"
#endif
#ifndef ROOT_TGTab
#include "TGTab.h"
#endif
#ifndef ROOT_TGListView
#include "TGListView.h"
#endif
#ifndef ROOT_TGStatusBar
#include "TGStatusBar.h"
#endif
#ifndef ROOT_TGuiBldGeometryFrame
#include "TGuiBldGeometryFrame.h"
#endif
#ifndef ROOT_TGToolBar
#include "TGToolBar.h"
#endif
#ifndef ROOT_TGuiBldDragManager
#include "TGuiBldDragManager.h"
#endif
#ifndef ROOT_TGObject
#include "TGObject.h"
#endif

#include "Riostream.h"


#ifndef ROOT_TGButton
#include "TGButton.h"
#endif

#include "TRootEmbeddedCanvas.h"

class gui   : public TGMainFrame
{
 private:
	viewer*myviewer;
  daq *mydaq;
  TGTextButton *fStartButton;
  TGTextButton *fPauseButton;
  TGTextButton *fResetButton;
  TGTextButton *fStopButton;
  TGTextButton *fSetButton;

  TGHorizontalFrame *hFrame;
  TGCompositeFrame *hFrame1;
  TGCompositeFrame *hFrame2;

  TGDockableFrame    *fMenuDock;
  TGMenuBar          *fMenuBar;
  TGPopupMenu        *fMenuHelp;
  TGLayoutHints      *fMenuBarLayout, *fMenuBarHelpLayout;

  TGTextEdit *foutput;
  TGFont *ufont; 
  TGGC   *uGC;  
  GCValues_t address;
  TGTextEntry *faddress;
  TGNumberEntry *fchannel;
  TGLabel *Daddress;
 /* TGLabel *Module;
  GCValues_t DModule;
  TGTextEntry *fModule;
  */
  TGLabel *Channel;
  TGIcon *logo;
  TGLabel*lmethods;
  TGComboBox *methods;

  //tab
  TGTab  *fTab;
  TGCompositeFrame *tf;
  TGTextButton* Bok;
  TGTextButton*Bclear;
  //set_up
  	TGComboBox *Rmode;
	GCValues_t Vtime;
	TGTextEntry *Ttime ;
	TGLabel *Ltime ;
	GCValues_t Vcounts;
	TGTextEntry *Tcount;
	TGLabel *Lcount;
	GCValues_t Vname;
	TGTextEntry *Tname;
	TGLabel *Lname;


  time_t start,stop;
  void StartTimer();
  double StopTimer();
  void do_start();
  void do_stop();
  void do_pause();
  void do_setup();

 public:
  gui(const TGWindow *p, UInt_t w, UInt_t h);
	virtual ~gui();
	virtual void            CloseWindow();
	virtual Bool_t          ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2);
	int gui_time;
	int gui_counts;
	const char* gui_name;
};
#endif
