#if !defined(AFX_HARD_H__CCB5BE4E_47EB_4F46_9076_253DA4A92C4D__INCLUDED_)
#define AFX_HARD_H__CCB5BE4E_47EB_4F46_9076_253DA4A92C4D__INCLUDED_

// Hard.h : header file
//
#include "Channel.h"
#include "Trigger.h"

/////////////////////////////////////////////////////////////////////////////

class CHard
{
// Construction
public:
	CHard();
	~CHard();

// Attributes
public:
	USHORT m_nDeviceIndex;				//Device Serial ID(0/1/2....)
	USHORT m_nFPGAVersion;				//FPGA Versorn

	USHORT m_nInsertMode;
	double m_dbSinNum;
	double m_dbSheet[105000];//[5000][21];

	USHORT m_nCurCH;					//Current Selected Channel
	USHORT m_nTimeDIV;					//TimeBase Index Value
	USHORT m_nHTriggerPos;				//Horizonal Trigger Position(Range from 0 to 100)

	USHORT m_nCalLevel[CAL_LEVEL_LEN];	//Self Calibration Result
	USHORT m_nDACVoltage[12];			//Twelve Road DAC Volatage

	CChannel m_CH[MAX_CH_NUM];			//Channel
	CTrigger m_Trigger;					//Trigger
	RELAYCONTROL m_stRelayControl;		//Relay Control Struct
	CONTROLDATA m_stControl;			//Control State

	BOOL  m_bStartNormalCollect;		//Is Starting new Collecting
	USHORT m_nCollectState;				//Collected State
	USHORT m_nWaitTimes;				//wait for Trigger signal
	USHORT m_nReadOK;					//Read Collect Data State

	//Correction Value
	double m_fAmpCorrect[MAX_CH_NUM*MAX_VOLTDIV_NUM*CAL_CHANNEL_MODEL];	//Amplitude Ratio Correction

// Operations
public:
	void Init();
	USHORT GetChannelNum(WORD nCHSet);
	void SetAmpCorrectRatio();
	void ComputerTwelveRoadVoltage();
	void SetDACVoltageforTwelveRoad();
	void SetCHAndTrigger(RELAYCONTROL relaycontrol);
	void SetTriggerAndSyncOutput();
	void ProcessInsertData(WORD* SourceData,WORD* BufferData,USHORT nCH);
	void CollectData();

};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_HARD_H__CCB5BE4E_47EB_4F46_9076_253DA4A92C4D__INCLUDED_)
