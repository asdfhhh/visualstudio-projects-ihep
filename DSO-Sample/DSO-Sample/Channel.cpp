// Channel.cpp : implementation file
//

#include "stdafx.h"
#include "Channel.h"



/////////////////////////////////////////////////////////////////////////////
// CChannel

CChannel::CChannel()
{
	Init();
}

CChannel::~CChannel()
{
	if(m_pSrcData != NULL)
	{
		delete[] m_pSrcData;
		m_pSrcData = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////
void CChannel::Init()
{
	m_nSrcDataLen = DEF_READ_DATA_LEN;
	m_nDrawDataLen = DEF_DRAW_DATA_LEN;
	m_pSrcData = new short[m_nSrcDataLen];
	memset(m_pSrcData,0,m_nSrcDataLen*sizeof(short));
	m_bOnOff = TRUE;
	m_nVoltDIV = 9;
	m_nCoupling = AC;
	m_clrRGB = RGB(0,0,0);
	m_nLeverPos = MID_DATA;
	m_bBWLimit = FALSE;
	m_bInvert = FALSE;
}

void CChannel::GetSrcData(USHORT *pData, ULONG nDataLen)
{
	ULONG i;
	for(i=0;i<nDataLen;i++)
	{
		*(m_pSrcData+i) = (short)(pData[i] - (MAX_DATA - m_nLeverPos));
	}
}