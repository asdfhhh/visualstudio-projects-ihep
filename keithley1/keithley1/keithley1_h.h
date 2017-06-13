

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Tue Jun 13 11:32:48 2017
 */
/* Compiler settings for keithley1.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __keithley1_h_h__
#define __keithley1_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __Ikeithley1_FWD_DEFINED__
#define __Ikeithley1_FWD_DEFINED__
typedef interface Ikeithley1 Ikeithley1;

#endif 	/* __Ikeithley1_FWD_DEFINED__ */


#ifndef __keithley1_FWD_DEFINED__
#define __keithley1_FWD_DEFINED__

#ifdef __cplusplus
typedef class keithley1 keithley1;
#else
typedef struct keithley1 keithley1;
#endif /* __cplusplus */

#endif 	/* __keithley1_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __keithley1_LIBRARY_DEFINED__
#define __keithley1_LIBRARY_DEFINED__

/* library keithley1 */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_keithley1;

#ifndef __Ikeithley1_DISPINTERFACE_DEFINED__
#define __Ikeithley1_DISPINTERFACE_DEFINED__

/* dispinterface Ikeithley1 */
/* [uuid] */ 


EXTERN_C const IID DIID_Ikeithley1;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B036E18F-59E5-466A-B6CF-D357C36BCAF7")
    Ikeithley1 : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct Ikeithley1Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            Ikeithley1 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            Ikeithley1 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            Ikeithley1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            Ikeithley1 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            Ikeithley1 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            Ikeithley1 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            Ikeithley1 * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } Ikeithley1Vtbl;

    interface Ikeithley1
    {
        CONST_VTBL struct Ikeithley1Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Ikeithley1_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define Ikeithley1_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define Ikeithley1_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define Ikeithley1_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define Ikeithley1_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define Ikeithley1_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define Ikeithley1_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __Ikeithley1_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_keithley1;

#ifdef __cplusplus

class DECLSPEC_UUID("0D9B53D0-03E1-45E9-B372-7128E96857F6")
keithley1;
#endif
#endif /* __keithley1_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


