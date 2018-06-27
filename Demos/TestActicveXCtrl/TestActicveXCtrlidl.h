

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Wed Jun 27 09:04:30 2018
 */
/* Compiler settings for TestActicveXCtrl.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __TestActicveXCtrlidl_h__
#define __TestActicveXCtrlidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DTestActicveXCtrl_FWD_DEFINED__
#define ___DTestActicveXCtrl_FWD_DEFINED__
typedef interface _DTestActicveXCtrl _DTestActicveXCtrl;

#endif 	/* ___DTestActicveXCtrl_FWD_DEFINED__ */


#ifndef ___DTestActicveXCtrlEvents_FWD_DEFINED__
#define ___DTestActicveXCtrlEvents_FWD_DEFINED__
typedef interface _DTestActicveXCtrlEvents _DTestActicveXCtrlEvents;

#endif 	/* ___DTestActicveXCtrlEvents_FWD_DEFINED__ */


#ifndef __TestActicveXCtrl_FWD_DEFINED__
#define __TestActicveXCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class TestActicveXCtrl TestActicveXCtrl;
#else
typedef struct TestActicveXCtrl TestActicveXCtrl;
#endif /* __cplusplus */

#endif 	/* __TestActicveXCtrl_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_TestActicveXCtrl_0000_0000 */
/* [local] */ 

#pragma once
#pragma region Desktop Family
#pragma endregion


extern RPC_IF_HANDLE __MIDL_itf_TestActicveXCtrl_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_TestActicveXCtrl_0000_0000_v0_0_s_ifspec;


#ifndef __TestActicveXCtrlLib_LIBRARY_DEFINED__
#define __TestActicveXCtrlLib_LIBRARY_DEFINED__

/* library TestActicveXCtrlLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_TestActicveXCtrlLib;

#ifndef ___DTestActicveXCtrl_DISPINTERFACE_DEFINED__
#define ___DTestActicveXCtrl_DISPINTERFACE_DEFINED__

/* dispinterface _DTestActicveXCtrl */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DTestActicveXCtrl;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B38B780A-1291-400C-88B2-0048AB629F77")
    _DTestActicveXCtrl : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DTestActicveXCtrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DTestActicveXCtrl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DTestActicveXCtrl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DTestActicveXCtrl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DTestActicveXCtrl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DTestActicveXCtrl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DTestActicveXCtrl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DTestActicveXCtrl * This,
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
    } _DTestActicveXCtrlVtbl;

    interface _DTestActicveXCtrl
    {
        CONST_VTBL struct _DTestActicveXCtrlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DTestActicveXCtrl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DTestActicveXCtrl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DTestActicveXCtrl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DTestActicveXCtrl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DTestActicveXCtrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DTestActicveXCtrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DTestActicveXCtrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DTestActicveXCtrl_DISPINTERFACE_DEFINED__ */


#ifndef ___DTestActicveXCtrlEvents_DISPINTERFACE_DEFINED__
#define ___DTestActicveXCtrlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DTestActicveXCtrlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DTestActicveXCtrlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("A4633AC6-1B7D-4B63-B8ED-1C6FB264BB74")
    _DTestActicveXCtrlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DTestActicveXCtrlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DTestActicveXCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DTestActicveXCtrlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DTestActicveXCtrlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DTestActicveXCtrlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DTestActicveXCtrlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DTestActicveXCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DTestActicveXCtrlEvents * This,
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
    } _DTestActicveXCtrlEventsVtbl;

    interface _DTestActicveXCtrlEvents
    {
        CONST_VTBL struct _DTestActicveXCtrlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DTestActicveXCtrlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DTestActicveXCtrlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DTestActicveXCtrlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DTestActicveXCtrlEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DTestActicveXCtrlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DTestActicveXCtrlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DTestActicveXCtrlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DTestActicveXCtrlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TestActicveXCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("648573AD-951F-415F-8FBD-F41F7300CB99")
TestActicveXCtrl;
#endif
#endif /* __TestActicveXCtrlLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


