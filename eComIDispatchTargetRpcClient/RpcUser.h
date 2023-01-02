#pragma once

#include "stdafx.h"
#include "../eRpcIdl/RpcIdlSnd.h"
#include "../eRpcIdl/RpcIdlRcv.h"

// RPC�R�[���o�b�N�C�x���g
CONTEXT_HANDLE_RCV OpenRcv(
    /* [in] */ handle_t hBinding,
    /* [in] */ int res);
void SendRcv(
    /* [in] */ CONTEXT_HANDLE_RCV hContext);
void CloseRcv(
    /* [out][in] */ CONTEXT_HANDLE_RCV* phContext);

// RPC������
void* __RPC_USER midl_user_allocate(size_t size);
void __RPC_USER midl_user_free(void* p);

// RPC�I�v�V����
DWORD HandleError(const char* szFunction, DWORD dwError);
RPC_STATUS CALLBACK SecurityCallback(RPC_IF_HANDLE /*hInterface*/, void* /*pBindingHandle*/);
DWORD WINAPI RpcServerListenThreadProc(LPVOID /*pParam*/);
void __RPC_USER CONTEXT_HANDLE_RCV_rundown(CONTEXT_HANDLE_RCV hContext);