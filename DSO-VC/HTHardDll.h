#ifndef _HT_HARD_DLL_H
#define _HT_HARD_DLL_H

#ifndef DLL_API
#define DLL_API extern "C" __declspec(dllimport)
#endif
#define WIN_API __stdcall

typedef struct _HT_RELAY_CONTROL
{
	BOOL bCHEnable[MAX_CH_NUM];
	WORD nCHVoltDIV[MAX_CH_NUM];
	WORD nCHCoupling[MAX_CH_NUM];
	BOOL bCHBWLimit[MAX_CH_NUM];
	WORD nTrigSource;
	BOOL bTrigFilt;
	WORD nALT;
}RELAYCONTROL,*PRELAYCONTROL;

DLL_API WORD WINAPI dsoHTDeviceConnect(WORD DeviceIndex);

DLL_API WORD WINAPI dsoHMResetDevice(WORD nDeviceIndex);

DLL_API WORD WINAPI dsoGetFPGAVersion(WORD DeviceIndex);

DLL_API WORD WINAPI dsoHTReadCalibrationData(WORD DeviceIndex,WORD* pLevel,WORD nLen);

DLL_API WORD WINAPI dsoHMReadAmpCorrectData(WORD DeviceIndex,double *pAmpCoe,WORD nLen);

DLL_API BOOL WINAPI dsoSetUSBBus(WORD DeviceIndex);

DLL_API WORD WINAPI dsoHMSetFanControlState(WORD nDeviceIndex,WORD nOnOff);

DLL_API WORD WINAPI dsoHMSetADClockType(WORD nDeviceIndex,PCONTROLDATA pControl,PRELAYCONTROL pRelayControl);

DLL_API WORD WINAPI dsoHMSetSampleRate(WORD DeviceIndex,WORD nTimeDIV,PRELAYCONTROL pRelayControl);

DLL_API WORD WINAPI dsoHMSetBufferSize(WORD DeviceIndex,PCONTROLDATA pControl);

DLL_API WORD WINAPI dsoHMSetTriggerAndSyncOutput(WORD nDeviceIndex,WORD nTriggerMode,WORD nTriggerMomentSel,WORD nVedioSyncSelect,WORD nTriggerSlope,WORD nModelChoice,WORD nVideoStandard,WORD nVedioLineNum,ULONG nTrigHoldOffCounter,ULONG nPWL,ULONG nPW,ULONG nPWG);

DLL_API WORD WINAPI dsoHTForceTrigger(WORD DeviceIndex);

DLL_API WORD WINAPI dsoHMClosePeakDetect(WORD nDeviceIndex);

DLL_API WORD WINAPI dsoHMSetCHAndTrigger(WORD nDeviceIndex,BOOL *bCHEnable,WORD *nCHVoltDIV,WORD *nCHCoupling,BOOL *bCHBWLimit,WORD nTrigSource,WORD nTrigCoupling,BOOL bTrigFilt,WORD nALT,WORD *pCalibrate);

DLL_API WORD WINAPI dsoHMSetDACVoltageforTwelveRoad(WORD DeviceIndex,PCONTROLDATA pControl,WORD *pLeverPos,WORD *pBLWlevel,WORD nCalLevel,WORD nTriglevel,WORD nVedioTrigLevel,WORD nTrigDelaylevel);

DLL_API WORD WINAPI dsoHMSetChannelSwitch(WORD nDeviceIndex,PRELAYCONTROL pRelayControl);

DLL_API void WINAPI dsoHMSetAmpCorrectRatio(WORD nDeviceIndex, WORD *pLeverPos, double* dbAmp, USHORT nLength);

DLL_API WORD WINAPI  dsoHMGetNormalData(WORD DeviceIndex,WORD* pCH1Data,WORD* pCH2Data,WORD* pCH3Data,WORD* pCH4Data,PCONTROLDATA pControl,PRELAYCONTROL pRelayControl);

DLL_API WORD WINAPI dsoHMStartCollectData(WORD nDeviceIndex,WORD nMode);

DLL_API WORD WINAPI dsoHMGetYTNormalCaptureState(WORD nDeviceIndex);

















#endif

