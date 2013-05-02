#pragma once
// Mainframe macro generated from application: root
// By ROOT version 5.34/00 on 2012-09-05 20:45:43
#include <Windows4Root.h>
#include <Riostream.h>
#include <TGClient.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TRint.h>
#include <TROOT.h>

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
#ifndef ROOT_TGButton
#include "TGButton.h"
#endif
#ifndef ROOT_TGFSComboBox
#include "TGFSComboBox.h"
#endif
#ifndef ROOT_TGLabel
#include "TGLabel.h"
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
#ifndef ROOT_TGListTree
#include "TGListTree.h"
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
#include "TTree.h"
#include "TH2F.h"
#include "TF1.h"
#include "TFile.h"
#include "TH1F.h"
#include "viewer.h"
#include "TThread.h"

class gui: public TGMainFrame
{
public:
	gui(const TGWindow *p, UInt_t w, UInt_t h);
	virtual ~gui();
	virtual void            CloseWindow();
	virtual Bool_t          ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2);
	TH2F *h2;

private:
	TGHorizontalFrame *fMainFrame;
	TGFont *ufont;         // will reflect user font changes
	TGGC   *uGC;           // will reflect user GC changes
	TGTextEntry *monitorentry;
	GCValues_t valorentry;
	TGTextEntry *calibrateentry;
	GCValues_t valrateentry;
	TGLabel *calibratefile;
	TGTextButton *start ;
	TGTextButton *stop;
	TGTextButton *exit;
	TGTextButton *calibrate;
	TGTextButton *save ;
	TGLabel *monitorfile;
	viewer*fviewer;
	void docali();
	void dosave();
	void dostart();
	void dostop();
	unsigned int data;
	int adc;
	int t_adc[64];
	int ch;
	int num_unit;
	int num_ladder;
	int DAQ_time;
	int flength;
	float mean[64],rms[64];
	char filename[100];
	char rootname[100];
	char Hname[10];
	char dsuffix[10];
	char csuffix[20];
	char rsuffix[10];
	TF1*consf;
	TH1F *h1[64];
	TTree*t;
	bool runflag;

};
