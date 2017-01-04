// Hard.cpp : implementation file
//

#include "stdafx.h"
#include "Hard.h"


/////////////////////////////////////////////////////////////////////////////
// CHard

CHard::CHard()
{
	m_nDeviceIndex = 0;
	Init();
}

CHard::~CHard()
{
}

/////////////////////////////////////////////////////////////////////////////
void CHard::Init()
{
	int i = 0;
	m_nDACVoltage[0] = 0x0000;
	m_nDACVoltage[1] = 0x3a98;
	m_nDACVoltage[2] = 0x7D00;
	m_nDACVoltage[9] = 0x31ff;


	m_nDACVoltage[11]= 0xBB80;
	m_nDACVoltage[5] = 0xBB80;
	m_nDACVoltage[7] = 0xBB80;
	m_nDACVoltage[6] = 0xBB80;

	m_nDACVoltage[3] = 0xBB80;
	m_nDACVoltage[4] = 0xBB80;
	m_nDACVoltage[8] = 0xBB80;
	m_nDACVoltage[10]= 0xBB80;
	memset(m_nCalLevel,0,sizeof(m_nCalLevel));

	m_nInsertMode = 2;
	m_dbSinNum = 0.0;

	m_nCollectState = 0;
	m_nWaitTimes = 0;
	m_nReadOK = 0;
	m_nFPGAVersion = 0;
	m_nCurCH = CH1;

	for(i=0;i<MAX_CH_NUM;i++)
	{
		m_CH[i].Init();
	}

	#if(MAX_CH_NUM == 4)
	{
		m_CH[CH1].m_nLeverPos = 64;
		m_CH[CH1].m_clrRGB = RGB(255,255,0);
		m_CH[CH2].m_nLeverPos = 96;
		m_CH[CH2].m_clrRGB = RGB(0,255,255);
		m_CH[CH3].m_nLeverPos = 160;
		m_CH[CH3].m_clrRGB = RGB(255,0,255);
		m_CH[CH4].m_nLeverPos = 192;
		m_CH[CH4].m_clrRGB = RGB(0,255,0);
	}
	#else
	{
		m_CH[CH1].m_nLeverPos = 190;
		m_CH[CH1].m_clrRGB = RGB(255,255,0);
		m_CH[CH2].m_nLeverPos = 180;
		m_CH[CH2].m_clrRGB = RGB(0,255,255);
	}
	#endif
	
	m_Trigger.Init();
	for(i=0;i<MAX_CH_NUM;i++)
	{
		m_Trigger.m_nLeverPos[i] = m_CH[i].m_nLeverPos;
		m_Trigger.m_nTriggerLevel[i] = 0;
	}

	m_nTimeDIV = 12;
	m_nHTriggerPos = 50;


	m_stControl.nCHSet = 0;
	for(i=0;i<MAX_CH_NUM;i++)
	{
		USHORT n = 0;
		if(m_CH[i].m_bOnOff)
		{
			n = (USHORT)pow(2.,i);
		}
		m_stControl.nCHSet += n;
	}
	m_stControl.nTimeDIV = m_nTimeDIV;
	m_stControl.nTriggerSource = m_Trigger.m_nSource;
	m_stControl.nHTriggerPos = m_nHTriggerPos;
	m_stControl.nVTriggerPos = m_Trigger.m_nLeverPos[m_Trigger.m_nSource];
	m_stControl.nTriggerSlope = m_Trigger.m_nSlope;
	m_stControl.nBufferLen = DEF_READ_DATA_LEN;
	m_stControl.nReadDataLen = m_CH[CH1].m_nSrcDataLen;
	m_stControl.nAlreadyReadLen = 0;
	m_stControl.nALT = 0;
	m_stControl.nETSOpen = 0;

	for(i=0;i<MAX_CH_NUM;i++)
	{
		m_stRelayControl.bCHEnable[i] = m_CH[i].m_bOnOff;
		m_stRelayControl.nCHVoltDIV[i] = m_CH[i].m_nVoltDIV;
		m_stRelayControl.nCHCoupling[i] = m_CH[i].m_nCoupling;
		m_stRelayControl.bCHBWLimit[i] = m_CH[i].m_bBWLimit;
	}
	m_stRelayControl.nTrigSource = m_Trigger.m_nSource;
	m_stRelayControl.bTrigFilt = 0;
	m_stRelayControl.nALT = 0;
}

USHORT CHard::GetChannelNum(WORD nCHSet)
{
	//Get Channel Work Model
	USHORT nCHCount = 0;
	for(int i = 0;i<MAX_CH_NUM;i++)
	{
		if(((nCHSet >> i) & 0x01) == 1)
		{
			nCHCount++;
		}
	}
	if(nCHCount !=1 && nCHCount != 2) //Judge
	{
		nCHCount = 4; //When there are four channels, only Consider 1/2/4. All other Values(0/3) regards 4.
	}

	return nCHCount;
}

void CHard::SetAmpCorrectRatio()
{
	//Select needed Amplidute correction Ratio

	double dbAmpCorr[MAX_CH_NUM];
	USHORT pLeverPos[MAX_CH_NUM];
	USHORT nCHCount = GetChannelNum(m_stControl.nCHSet);	//Get Channel Work Model
	USHORT nChSwitch;
	USHORT nIndex;
	if(nCHCount == 1)
	{
		nChSwitch = 2;
	}
	else if(nCHCount == 2)
	{
		nChSwitch = 1;
	}
	else
	{
		nChSwitch = 0;
	}
	for(int i=0;i<MAX_CH_NUM;i++)
	{
		pLeverPos[i] = m_CH[i].m_nLeverPos;
		nIndex = (i*MAX_VOLTDIV_NUM+m_CH[i].m_nVoltDIV)*CAL_CHANNEL_MODEL+nChSwitch;
		dbAmpCorr[i] = m_fAmpCorrect[nIndex];
	}
	dsoHMSetAmpCorrectRatio(m_nDeviceIndex,pLeverPos,dbAmpCorr,MAX_CH_NUM);
}

void CHard::ComputerTwelveRoadVoltage()
{
	USHORT nPos;
	USHORT nCH;
	USHORT nVoltDIV;
	USHORT nIndex;
	USHORT nCHCount = GetChannelNum(m_stControl.nCHSet);
	USHORT nChSwitch;
	double fStep;	//步进
	double fMid;	//中间值
	if(nCHCount == 1)
	{
		nChSwitch = 2;
	}
	else if(nCHCount == 2)
	{
		nChSwitch = 1;
	}
	else
	{
		nChSwitch = 0;
	}
				
	//CH1 Zero Level
	nCH = CH1;
	nVoltDIV = m_CH[nCH].m_nVoltDIV;
	nPos = MAX_DATA-m_CH[nCH].m_nLeverPos;
	nIndex = nCH*CAL_VOLTDIV_NUM*CAL_CHANNEL_MODEL + 2*CAL_CHANNEL_MODEL*nVoltDIV+2*nChSwitch;
	fStep = (m_nCalLevel[nIndex+1] - m_nCalLevel[nIndex])*1.0/MAX_DATA;
	fMid =  (m_nCalLevel[nIndex+1] + m_nCalLevel[nIndex])/2.0;
				
	nPos = WORD(fStep*(nPos-MID_DATA) + fMid);
	m_nDACVoltage[11]= nPos;
				
	//CH2 Zero Level
	nCH = CH2;
	nVoltDIV = m_CH[nCH].m_nVoltDIV;
	nPos = MAX_DATA-m_CH[nCH].m_nLeverPos;
	nIndex = nCH*CAL_VOLTDIV_NUM*CAL_CHANNEL_MODEL + 2*CAL_CHANNEL_MODEL*nVoltDIV+2*nChSwitch;
	fStep = (m_nCalLevel[nIndex+1] - m_nCalLevel[nIndex])*1.0/MAX_DATA;
	fMid =  (m_nCalLevel[nIndex+1] + m_nCalLevel[nIndex])/2.0;
				
	nPos = WORD(fStep*(nPos-MID_DATA) + fMid);
	m_nDACVoltage[5] = nPos;

	//CH3 Zero Level
	nCH = CH3;
	nVoltDIV = m_CH[nCH].m_nVoltDIV;
	nPos = MAX_DATA-m_CH[nCH].m_nLeverPos;
	nIndex = nCH*CAL_VOLTDIV_NUM*CAL_CHANNEL_MODEL + 2*CAL_CHANNEL_MODEL*nVoltDIV+2*nChSwitch;
	fStep = (m_nCalLevel[nIndex+1] - m_nCalLevel[nIndex])*1.0/MAX_DATA;
	fMid =  (m_nCalLevel[nIndex+1] + m_nCalLevel[nIndex])/2.0;
				
	nPos = WORD(fStep*(nPos-MID_DATA) + fMid);
	m_nDACVoltage[7] = nPos;
				
	//CH4 Zero Level
	nCH = CH4;
	nVoltDIV = m_CH[nCH].m_nVoltDIV;
	nPos = MAX_DATA-m_CH[nCH].m_nLeverPos;
	nIndex = nCH*CAL_VOLTDIV_NUM*CAL_CHANNEL_MODEL + 2*CAL_CHANNEL_MODEL*nVoltDIV+2*nChSwitch;
	fStep = (m_nCalLevel[nIndex+1] - m_nCalLevel[nIndex])*1.0/MAX_DATA;
	fMid =  (m_nCalLevel[nIndex+1] + m_nCalLevel[nIndex])/2.0;
				
	nPos = WORD(fStep*(nPos-MID_DATA) + fMid);
	m_nDACVoltage[6] = nPos;

	//Trigger Delay Level
	nIndex = CAL_CHANNEL_LEN+CAL_TRIGGER_LEN;
	m_nDACVoltage[9] = m_nCalLevel[nIndex];
	
	//Trigger Level
	USHORT nlevel;
	USHORT nTriggerCoupling = DC;
	USHORT nDisplayPos = 0;
	USHORT nMid = 0;
	nPos = m_Trigger.m_nLeverPos[m_Trigger.m_nSource];

	nCH = m_Trigger.m_nSource;
	nTriggerCoupling = m_Trigger.m_nCoupling;

	if(nCH < MAX_CH_NUM)
	{
		nIndex = 96*CAL_CHANNEL_MODEL+2*MAX_TRIGCORR_NUM*nCH+2*nTriggerCoupling;
	
		nlevel = USHORT(1.0*(nPos-MID_DATA)*(m_nCalLevel[nIndex]-m_nCalLevel[nIndex+1])/MAX_DATA + 1.0*MID_DATA*(m_nCalLevel[nIndex]-m_nCalLevel[nIndex+1])/MAX_DATA + m_nCalLevel[nIndex+1]);	
		nPos = m_CH[nCH].m_nLeverPos;		
		nlevel = nlevel + (USHORT)(18.5*(nPos-MID_DATA));
	}
	else if(nCH == EXT || nCH == EXT10)
	{
		if(nTriggerCoupling == TRIG_DC)
		{
			nIndex = CAL_CHANNEL_LEN+CAL_TRIGGER_LEN+CAL_DELAY_LEN;
			fStep = 1.0*(m_nCalLevel[nIndex]-m_nCalLevel[nIndex+1])/64;
			nMid = m_nCalLevel[nIndex+1];
			nlevel = nMid + USHORT(fStep * (MID_DATA - nPos));
		}
		else
		{
			nIndex = CAL_CHANNEL_LEN+CAL_TRIGGER_LEN+CAL_DELAY_LEN+2;
			fStep = 1.0*(m_nCalLevel[nIndex]-m_nCalLevel[nIndex+1])/64;
			nMid = (m_nCalLevel[nIndex]+m_nCalLevel[nIndex+1])/2;
			nlevel = nMid + USHORT(fStep * (MID_DATA - nPos));
		}
	}
	m_nDACVoltage[1] = m_nDACVoltage[2] = nlevel;


}
void CHard::SetDACVoltageforTwelveRoad()
{
	//Set Twelve Road DAC Voltage

	USHORT pLeverPos[4],pBWlevel[4];
	USHORT nCalLevel,nTriglevel,nVideoTrigLevel,nTrigDelaylevel;

	nCalLevel = m_nDACVoltage[0];
	nTriglevel = m_nDACVoltage[1];
	nVideoTrigLevel = m_nDACVoltage[2];
	nTrigDelaylevel = m_nDACVoltage[9];
	pLeverPos[0] = m_nDACVoltage[11];
	pLeverPos[1] = m_nDACVoltage[5];
	pLeverPos[2] = m_nDACVoltage[7];
	pLeverPos[3] = m_nDACVoltage[6];
	pBWlevel[0] = m_nDACVoltage[3];
	pBWlevel[1] = m_nDACVoltage[4];
	pBWlevel[2] = m_nDACVoltage[8];
	pBWlevel[3] = m_nDACVoltage[10];

	dsoHMSetDACVoltageforTwelveRoad(m_nDeviceIndex,&m_stControl,pLeverPos,pBWlevel,nCalLevel,nTriglevel,nVideoTrigLevel,nTrigDelaylevel);
}

void CHard::SetCHAndTrigger(RELAYCONTROL relaycontrol)
{
	//Set CH and Trigger
	USHORT* pCaliCH = new USHORT[MAX_CH_NUM];
	memset(pCaliCH,0,MAX_CH_NUM*sizeof(USHORT));	//Must be Zero Array

	dsoHMSetCHAndTrigger(m_nDeviceIndex,
						 relaycontrol.bCHEnable,
						 relaycontrol.nCHVoltDIV,
						 relaycontrol.nCHCoupling,
						 relaycontrol.bCHBWLimit,
						 relaycontrol.nTrigSource,
						 m_Trigger.m_nCoupling,
						 relaycontrol.bTrigFilt,
						 relaycontrol.nALT,
						 pCaliCH		//must be Zero Array
						);
}
void CHard::SetTriggerAndSyncOutput()
{
	//Set Trigger Control and Sync Control

	USHORT nTriggerSlope = 0;

	nTriggerSlope = m_Trigger.m_nSlope;	

	if(m_Trigger.m_nSource == EXT || m_Trigger.m_nSource == EXT10)//Ext Trigger
	{
		if(nTriggerSlope == 0)
		{
			nTriggerSlope = 1;
		}
		else
		{
			nTriggerSlope = 0;
		}
	}

	dsoHMSetTriggerAndSyncOutput(m_nDeviceIndex, m_Trigger.m_nMode, 0, 0, nTriggerSlope, 0, 0, 0, 10, 0, 0, 0);
}

void CHard::ProcessInsertData(WORD* SourceData,WORD* BufferData,USHORT nCH)
{
	USHORT nCHCount = GetChannelNum(m_stControl.nCHSet);
	if(m_nInsertMode == 2)
	{
		double dbInsertNum = dsoHMSFGetInsertNum(m_stControl.nTimeDIV,m_stControl.nALT,nCHCount);
		if(m_dbSinNum != dbInsertNum)
		{
			m_dbSinNum = dbInsertNum;
			dsoSFCalSinSheet(dbInsertNum,m_dbSheet);
		}
	}
	dsoHMSFProcessInsertData(SourceData,BufferData,&m_stControl,m_nInsertMode,nCHCount,m_dbSheet,nCH);
}

void CHard::CollectData()
{
	USHORT nReturn;
	if(m_bStartNormalCollect == TRUE)
	{
		//Start Collecting
		nReturn = dsoHMStartCollectData(m_nDeviceIndex,0);
		//Clear Flag
		m_bStartNormalCollect = FALSE;
		//Clear
		m_nWaitTimes = 0;
	}
	//Get Collected State
	m_nCollectState = dsoHMGetYTNormalCaptureState(m_nDeviceIndex);

	if(m_nCollectState == 7)
	{
		//Read Collect Data
		int i;
		USHORT* pReadData[4];
		ULONG nDataLen = m_stControl.nReadDataLen;
		
		for(i=0;i<MAX_CH_NUM;i++)
		{
			pReadData[i] = new USHORT[nDataLen];
		}
		
		if(m_stControl.nTimeDIV > MAX_INSERT_TIMEDIV)
		{
			//Normal Collect,No Insert Data
			m_nReadOK = dsoHMGetNormalData(m_nDeviceIndex,pReadData[0],pReadData[1],pReadData[2],pReadData[3],&m_stControl,&m_stRelayControl);
		}
		else if(m_stControl.nTimeDIV > MAX_SF_T_TIMEDIV)
		{
			//Need Small Insert Data
			USHORT* nData[MAX_CH_NUM];
			for(i=0;i<MAX_CH_NUM;i++)
			{
				nData[i] = new USHORT[m_stControl.nReadDataLen];
			}
			
			m_nReadOK = dsoHMGetNormalData(m_nDeviceIndex,nData[0],nData[1],nData[2],nData[3],&m_stControl,&m_stRelayControl);
			
			for(i=0;i<MAX_CH_NUM;i++)
			{
				if(((m_stControl.nCHSet >> i) & 0x01) == 1)//CH Open
				{
					ProcessInsertData(nData[i],pReadData[i],i);
				}
			}
			for(i=0;i<MAX_CH_NUM;i++)
			{
				delete[] nData[i];
				nData[i] = NULL;
			}
		}
		else
		{
			//Need Insert Large Data
			USHORT* nData[MAX_CH_NUM];
			ULONG nState[MAX_CH_NUM];
			memset(nState,0,sizeof(nState));
			USHORT *nDataBuffer = new USHORT[(m_stControl.nReadDataLen-DEF_READ_DATA_LEN)+BUF_40K_LEN];
			for(i=0;i<MAX_CH_NUM;i++)
			{
				nData[i] = new USHORT[m_stControl.nReadDataLen];
			}
			m_nReadOK = dsoHMGetNormalData(m_nDeviceIndex,nData[0],nData[1],nData[2],nData[3],&m_stControl,&m_stRelayControl);
			
			ProcessInsertData(nData[m_stControl.nTriggerSource],nDataBuffer,m_stControl.nTriggerSource);
			nState[m_stControl.nTriggerSource] = dsoSFFindTrigger(nDataBuffer,pReadData[m_stControl.nTriggerSource],&m_stControl);
			dsoGetSoftTriggerPos(m_stControl.nTimeDIV,m_stControl.nTriggerSource,nState,m_nFPGAVersion);
			for(i=0;i<MAX_CH_NUM;i++)
			{
				if(m_stControl.nTriggerSource == i)
				{
					continue;
				}
				if(((m_stControl.nCHSet >> i) & 0x01) == 1)//如果CH可用
				{
					ProcessInsertData(nData[i],nDataBuffer,i);
					dsoSFFindTriggerCopy(nDataBuffer,pReadData[i],&m_stControl,nState[i]);
				}
			}
			
			for(i=0;i<MAX_CH_NUM;i++)
			{
				delete[] nData[i];
				nData[i] = NULL;
			}
			delete[] nDataBuffer;
			nDataBuffer = NULL;
		}
		if(m_nReadOK == 1)
		{
			//Reading Success
			for(i=0;i<MAX_CH_NUM;i++)
			{
				m_CH[i].GetSrcData(pReadData[i],nDataLen);
			}
		}
		for(i=0;i<MAX_CH_NUM;i++)
		{
			delete[] pReadData[i];
			pReadData[i] = NULL;
		}
		m_nWaitTimes = 0;
		m_bStartNormalCollect = TRUE;
	}
	else if(m_nCollectState == 1)
	{
		if(m_Trigger.m_nSweep == TRIG_AUTO)
		{
			m_nWaitTimes++;		//Wait for trigger signal
			if(m_nWaitTimes >= 3)
			{
				//Clear or Reset
				m_nWaitTimes = 0;
				//Auto Trigger needs Creating Force Trigger
				dsoHTForceTrigger(m_nDeviceIndex);
				//Clear Force Signal
				SetTriggerAndSyncOutput();
			}
		}
	}
	else
	{
		//Others
	}
}