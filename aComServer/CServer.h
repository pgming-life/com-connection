

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 12:14:07 2038
 */
/* Compiler settings for CServer.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __CServer_h__
#define __CServer_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISumUp_FWD_DEFINED__
#define __ISumUp_FWD_DEFINED__
typedef interface ISumUp ISumUp;

#endif 	/* __ISumUp_FWD_DEFINED__ */


#ifndef ___ISumUpEvents_FWD_DEFINED__
#define ___ISumUpEvents_FWD_DEFINED__
typedef interface _ISumUpEvents _ISumUpEvents;

#endif 	/* ___ISumUpEvents_FWD_DEFINED__ */


#ifndef __SumUp_FWD_DEFINED__
#define __SumUp_FWD_DEFINED__

#ifdef __cplusplus
typedef class SumUp SumUp;
#else
typedef struct SumUp SumUp;
#endif /* __cplusplus */

#endif 	/* __SumUp_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ISumUp_INTERFACE_DEFINED__
#define __ISumUp_INTERFACE_DEFINED__

/* interface ISumUp */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISumUp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("295D9570-C579-4696-8BE2-C069DEC06F36")
    ISumUp : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SumUp( 
            int a,
            int b) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISumUpVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISumUp * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISumUp * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISumUp * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISumUp * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISumUp * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISumUp * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISumUp * This,
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
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SumUp )( 
            ISumUp * This,
            int a,
            int b);
        
        END_INTERFACE
    } ISumUpVtbl;

    interface ISumUp
    {
        CONST_VTBL struct ISumUpVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISumUp_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISumUp_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISumUp_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISumUp_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISumUp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISumUp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISumUp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ISumUp_SumUp(This,a,b)	\
    ( (This)->lpVtbl -> SumUp(This,a,b) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISumUp_INTERFACE_DEFINED__ */



#ifndef __CONNECTIONCOMLib_LIBRARY_DEFINED__
#define __CONNECTIONCOMLib_LIBRARY_DEFINED__

/* library CONNECTIONCOMLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CONNECTIONCOMLib;

#ifndef ___ISumUpEvents_INTERFACE_DEFINED__
#define ___ISumUpEvents_INTERFACE_DEFINED__

/* interface _ISumUpEvents */
/* [object][helpstring][uuid] */ 


EXTERN_C const IID IID__ISumUpEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AFE854B0-246F-4B66-B26F-A1060225C71C")
    _ISumUpEvents : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExecutionOver( 
            int Result) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct _ISumUpEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ISumUpEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ISumUpEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ISumUpEvents * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ExecutionOver )( 
            _ISumUpEvents * This,
            int Result);
        
        END_INTERFACE
    } _ISumUpEventsVtbl;

    interface _ISumUpEvents
    {
        CONST_VTBL struct _ISumUpEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ISumUpEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _ISumUpEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _ISumUpEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _ISumUpEvents_ExecutionOver(This,Result)	\
    ( (This)->lpVtbl -> ExecutionOver(This,Result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ___ISumUpEvents_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_SumUp;

#ifdef __cplusplus

class DECLSPEC_UUID("630B3CD3-DDB1-43CE-AD2F-4F57DC54D5D0")
SumUp;
#endif
#endif /* __CONNECTIONCOMLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


