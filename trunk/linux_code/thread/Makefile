ObjSuf        = o
SrcSuf        = cxx
ExeSuf        =
DllSuf        = so  
OutPutOpt     = -o

ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)





THREADTST     = -D_THREADLIB_ 

# Linux with egcs
CXX           = g++




CXXFLAGS     = -g -Wall -DR__THREAD -fPIC -D_REENTRANT 
CXXFLAGS     += $(ROOTCFLAGS) -I.

LD            = g++
LDFLAGS       = -g
SOFLAGS       = -shared
LIBS          = $(ROOTLIBS) -lm -ldl -rdynamic
GLIBS         = $(ROOTLIBS) $(ROOTGLIBS) -L/usr/X11R6/lib \
                -lXpm -lX11 -lm -ldl -rdynamic


THREADLIBS =  -lpthread -lThread
MYLIBS  =     $(THREADLIBS) 


#----------------------------------------------------------
# test executable, to be used instead of macro


TESTO      = TMhs3run.$(ObjSuf)
TESTS      = TMhs3run.$(SrcSuf)
TESTE      = TMhs3run$(ExeSuf)   

$(TESTE):     $(TESTO)
	$(LD) $(LDFLAGS) $(TESTO) $(GLIBS) $(MYLIBS) $(OutPutOpt) $(TESTE)
	@echo "$(TESTE) done"      


#------------------------------------------------------------------------------
# shared library containing the TThreadframe base class

BASEO        = TThreadframe.$(ObjSuf) \
                TThreadframeDict.$(ObjSuf) 

BASES        = TThreadframe.$(SrcSuf) \
                TThreadframeDict.$(SrcSuf)
BASESO	= libTThreadframe.$(DllSuf)

$(BASESO):       $(BASEO)
		$(LD) $(SOFLAGS) $(LDFLAGS) $(BASEO) $(OutPutOpt) $(BASESO)
		@echo "$(BASESO) done"


#------------------------------------------------------------------------------
# shared library containing the TMhs3 example class derived from TThreadframe

MHSO        = TMhs3.$(ObjSuf) \
                TMhs3Dict.$(ObjSuf) 

MHSS        = TMhs3.$(SrcSuf) \
                TMhs3Dict.$(SrcSuf)
MHSSO	= libTMhs3.$(DllSuf)

$(MHSSO):       $(MHSO)
		$(LD) $(SOFLAGS) $(LDFLAGS) $(MHSO) $(OutPutOpt) $(MHSSO)
		@echo "$(MHSSO) done"





#--------------------------------------------------------------------------------
PROGRAMS =  $(BASESO) $(MHSSO) $(TESTE)



all:			$(PROGRAMS) 


clean:
		@rm -f $(BASEO)$(MHSO) $(TESTO) *Dict.* core

clean_targets:

		@rm -f $(PROGRAMS) *Dict.* core


.SUFFIXES: .$(SrcSuf)

##############################################################

TThreadframe.$(ObjSuf): TThreadframe.h

TThreadframeDict.$(SrcSuf): TThreadframe.h TThreadframeLinkDef.h
	@echo "Generating dictionary TThreadframeDict..."
	@$(ROOTSYS)/bin/rootcint -f TThreadframeDict.$(SrcSuf) -c -I. TThreadframe.h TThreadframeLinkDef.h





##############################################################

TMhs3.$(ObjSuf): TMhs3.h TThreadframe.h TThreadframe.cxx

TMhs3Dict.$(SrcSuf): TMhs3.h TMhs3LinkDef.h
	@echo "Generating dictionary TMhs3Dict..."
	@$(ROOTSYS)/bin/rootcint -f TMhs3Dict.$(SrcSuf) -c  -I. TMhs3.h TMhs3LinkDef.h


##############################################
TMhs3run.$(ObjSuf): TMhs3run.cxx libTMhs3.so

.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -c $<


