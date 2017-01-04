#ifndef _HT_SOFT_DLL_H
#define _HT_SOFT_DLL_H

#ifndef DLL_API
#define DLL_API extern "C" _declspec(dllimport)
#endif
#define WINAPI __stdcall

typedef struct _HT_CONTROL_DATA
{
	WORD nCHSet;
        WORD nTimeDIV;
        WORD nTriggerSource;
        WORD nHTriggerPos;
	WORD nVTriggerPos;
	WORD nTriggerSlope;
	ULONG nBufferLen;
	ULONG nReadDataLen;
	ULONG nAlreadyReadLen;
    	WORD nALT;
	WORD nETSOpen;
		
}CONTROLDATA,*PCONTROLDATA;


DLL_API ULONG WINAPI dsoSFFindTrigger(WORD* SourceData,WORD* BufferData,PCONTROLDATA pControl);

DLL_API WORD WINAPI dsoSFFindTriggerCopy(WORD* SourceData,WORD* BufferData,PCONTROLDATA Control,ULONG TriggerPoint);

DLL_API WORD WINAPI dsoSFCalSinSheet(double div_data,double* dbSinSheet);

DLL_API void WINAPI dsoGetSoftTriggerPos(WORD nTimeDIV,WORD nTriggerSource,ULONG* pState,WORD nFPGAVersion);

DLL_API double WINAPI dsoHMSFGetInsertNum(WORD nTimeDIV, WORD nALT, WORD nCHCount);

DLL_API void WINAPI dsoHMSFProcessInsertData(WORD* SourceData,WORD* BufferData,PCONTROLDATA pControl,WORD nInsertMode,WORD nCHCount,double* dbSinSheet,WORD nCH);

#endif
