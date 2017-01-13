// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__1C4C18A9_544C_4E6A_B0C9_C32873D0CC59__INCLUDED_)
#define AFX_STDAFX_H__1C4C18A9_544C_4E6A_B0C9_C32873D0CC59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include "Windows4Root.h"
#include "TFile.h"
#include <math.h>

//Import HeadFile
#include "DefMacro.h"
#include "HTSoftDll.h"
#include "HTDisplayDll.h"
#include "HTHardDll.h"


//Import Lib
#pragma comment(lib,"HTSoftDll.lib")
#pragma comment(lib,"HTDisplayDll.lib")
#pragma comment(lib,"HTHardDll.lib")


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__1C4C18A9_544C_4E6A_B0C9_C32873D0CC59__INCLUDED_)
