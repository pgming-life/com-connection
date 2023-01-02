

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 12:14:07 2038
 */
/* Compiler settings for RpcIdlSnd.idl:
    Oicf, W4, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
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


#ifndef __RpcIdlSnd_h__
#define __RpcIdlSnd_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __RpcIdlSnd_INTERFACE_DEFINED__
#define __RpcIdlSnd_INTERFACE_DEFINED__

/* interface RpcIdlSnd */
/* [explicit_handle][version][uuid] */ 

typedef /* [context_handle] */ void *CONTEXT_HANDLE_SND;

typedef struct INPUT_DATA_SND
    {
    int args1;
    int args2;
    } 	INPUT_DATA_SND;

CONTEXT_HANDLE_SND OpenSnd( 
    /* [in] */ handle_t hBinding,
    /* [full][in] */ INPUT_DATA_SND *pData);

void SendSnd( 
    /* [in] */ CONTEXT_HANDLE_SND hContext);

void CloseSnd( 
    /* [out][in] */ CONTEXT_HANDLE_SND *phContext);



extern RPC_IF_HANDLE RpcIdlSnd_v1_0_c_ifspec;
extern RPC_IF_HANDLE RpcIdlSnd_v1_0_s_ifspec;
#endif /* __RpcIdlSnd_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

void __RPC_USER CONTEXT_HANDLE_SND_rundown( CONTEXT_HANDLE_SND );

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


