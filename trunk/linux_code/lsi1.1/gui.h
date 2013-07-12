#ifndef gui_H
#define gui_H 1
#include "Riostream.h"
#include "TGClient.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TRint.h"
#include "TROOT.h"
#include "TH1F.h"
#include <time.h>
#include "TGFrame.h"
#include "TGDockableFrame.h"
#include "TGMenu.h"
#include "TGMdiDecorFrame.h"
#include "TG3DLine.h"
#include "TGMdiFrame.h"
#include "TGMdiMainFrame.h"
#include "TGMdiMenu.h"
#include "TGListBox.h"
#include "TGNumberEntry.h"
#include "TGScrollBar.h"
#include "TGComboBox.h"
#include "TGuiBldHintsEditor.h"
#include "TGuiBldNameFrame.h"
#include "TGFrame.h"
#include "TGFileDialog.h"
#include "TGShutter.h"
#include "TGButtonGroup.h"
#include "TGCanvas.h"
#include "TGuiBldEditor.h"
#include "TGColorSelect.h"
#include "TGTextEdit.h"
#include "TGButton.h"
#include "TGFSComboBox.h"
#include "TGLabel.h"
#include "TGView.h"
#include "TGMsgBox.h"
#include "TRootGuiBuilder.h"
#include "TGTab.h"
#include "TGListView.h"
#include "TGStatusBar.h"
#include "TGuiBldGeometryFrame.h"
#include "TGToolBar.h"
#include "TGuiBldDragManager.h"
#include "TGObject.h"
#include "Riostream.h"
#include "TGButton.h"
#include "TRootEmbeddedCanvas.h"
#include "daq.h"

class gui   : public TGMainFrame
{
 private:
  daq *mydaq;
  TGTextButton *fStartButton;
  TGTextButton *fPauseButton;
  TGTextButton *fResetButton;
  TGTextButton *fStopButton;
  TGTextButton *fSetButton;

  TGHorizontalFrame *hFrame;
  TGHorizontalFrame *hFrame1;
  TGDockableFrame    *fMenuDock;
  TGMenuBar          *fMenuBar;
  TGPopupMenu        *fMenuFile, *fMenuTest, *fMenuView, *fMenuHelp;
  TGPopupMenu        *fCascadeMenu, *fCascade1Menu, *fCascade2Menu;
  TGPopupMenu        *fMenuNew1, *fMenuNew2;
  TGLayoutHints      *fMenuBarLayout, *fMenuBarItemLayout, *fMenuBarHelpLayout;

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


  time_t start,stop;
  void StartTimer();
  double StopTimer();
  void do_start();
  void do_stop();
  void do_pause();

 public:
  gui(const TGWindow *p, UInt_t w, UInt_t h);
	virtual ~gui();
	virtual void            CloseWindow();
	virtual Bool_t          ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2);
	int gui_time;
	int gui_counts;
	void set_parameters(int set_time,int set_counts)
	{
		gui_time=set_time;
		gui_counts=set_counts;
	}

};
#endif
