#if !defined(AFX_TRIGGER_H__CA7D9B92_D4EB_48D5_B251_BEB7A486E34B__INCLUDED_)
#define AFX_TRIGGER_H__CA7D9B92_D4EB_48D5_B251_BEB7A486E34B__INCLUDED_

// Trigger.h : header file
//

/////////////////////////////////////////////////////////////////////////////

class CTrigger
{
// Construction
public:
	CTrigger();
	~CTrigger();

// Attributes
public:
	USHORT m_nSource;					//Trigger Source
	USHORT m_nLeverPos[MAX_CH_NUM];		//Trigger Level in Device
	USHORT m_nTriggerLevel[MAX_CH_NUM];	//Trigger Level
	USHORT m_nMode;						//Trigger Mode
	USHORT m_nSlope;					//Trigger Slope
	USHORT m_nCoupling;					//Trigger Couple
	USHORT m_nSweep;					//Trigger Sweep

// Operations
public:
	void Init();

};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_TRIGGER_H__CA7D9B92_D4EB_48D5_B251_BEB7A486E34B__INCLUDED_)
