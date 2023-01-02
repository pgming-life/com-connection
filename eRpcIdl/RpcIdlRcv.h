

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 12:14:07 2038
 */
/* Compiler settings for RpcIdlRcv.idl:
    Oicf, W4, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
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


#ifndef __RpcIdlRcv_h__
#define __RpcIdlRcv_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __RpcIdlRcv_INTERFACE_DEFINED__
#define __RpcIdlRcv_INTERFACE_DEFINED__

/* interface RpcIdlRcv */
/* [explicit_handle][version][uuid] */ 

typedef /* [context_handle] */ void *CONTEXT_HANDLE_RCV;

CONTEXT_HANDLE_RCV OpenRcv( 
    /* [in] */ handle_t hBinding,
    /* [in] */ int result);

void SendRcv( 
    /* [in] */ CONTEXT_HANDLE_RCV hContext);

void CloseRcv( 
    /* [out][in] */ CONTEXT_HANDLE_RCV *phContext);



extern RPC_IF_HANDLE RpcIdlRcv_v1_0_c_ifspec;
extern RPC_IF_HANDLE RpcIdlRcv_v1_0_s_ifspec;
#endif /* __RpcIdlRcv_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

void __RPC_USER CONTEXT_HANDLE_RCV_rundown( CONTEXT_HANDLE_RCV );

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


