// Trigger.cpp : implementation file
//

#include "stdafx.h"
#include "Trigger.h"

/////////////////////////////////////////////////////////////////////////////
// CTrigger

CTrigger::CTrigger()
{
	int i;
	m_nSource = 0;					//Trigger Source
	for(i=0;i<MAX_CH_NUM;i++)
	{
		m_nLeverPos[i] = MID_DATA;		//Trigger Level in Device
	}
	m_nSlope = 0;						//Trigger Slope
}

CTrigger::~CTrigger()
{
}

/////////////////////////////////////////////////////////////////////////////
void CTrigger::Init()
{
	int i;
	m_nSource = 0;					//Trigger Source
	for(i=0;i<MAX_CH_NUM;i++)
	{
		m_nLeverPos[i] = MID_DATA;		//Trigger Level in Device
		m_nTriggerLevel[i] = MID_DATA;
	}
	m_nMode = EDGE;						//Trigger Mode:Edge
	m_nSlope = 0;						//Trigger Slope
	m_nCoupling = 0;					//Trigger Couple
	m_nSweep = 0;						//Trigger Sweep
}