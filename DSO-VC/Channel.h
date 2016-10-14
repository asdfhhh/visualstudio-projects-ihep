#if !defined(AFX_CHANNEL_H__FDA2DA8C_B756_42D7_BF0B_7157BB085959__INCLUDED_)
#define AFX_CHANNEL_H__FDA2DA8C_B756_42D7_BF0B_7157BB085959__INCLUDED_

// Channel.h : header file
//

/////////////////////////////////////////////////////////////////////////////

class CChannel
{
// Construction
public:
	CChannel();
	~CChannel();

// Attributes
public:
	short* m_pSrcData;			//Valule of Dots Read from Device
	ULONG m_nSrcDataLen;		//Number of Dots Read from Device
	ULONG m_nDrawDataLen;		//Number of Dots Drew in Screen
	BOOL m_bOnOff;				//TRUE:ON  FALSE:OFF
	USHORT m_nVoltDIV;			//Voltage Shift Index Value
	USHORT m_nCoupling;			//Couple Index Value
	USHORT m_nLeverPos;			//position of Zero Level in Device 
	BOOL m_bBWLimit;			//Bandwidth Limitations TRUE:ON  FALSE:OFF
	BOOL m_bInvert;				//Is Invert		TRUE:Invert
	COLORREF m_clrRGB;			//Show Color

// Operations
public:
	void Init();
	void GetSrcData(USHORT *pData, ULONG nDataLen);

};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_CHANNEL_H__FDA2DA8C_B756_42D7_BF0B_7157BB085959__INCLUDED_)
