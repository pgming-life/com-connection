#pragma once

#include "stdafx.h"
#include "../eRpcIdl/RpcIdlSnd.h"

// RPC�R�[���o�b�N�C�x���g
CONTEXT_HANDLE_SND OpenSnd(
    /* [in] */ handle_t hBinding,
    /* [ptr][in] */ INPUT_DATA_SND* pData);
void SendSnd(
    /* [in] */ CONTEXT_HANDLE_SND hContext);
void CloseSnd(
    /* [out][in] */ CONTEXT_HANDLE_SND* phContext);

// RPC������
void* __RPC_USER midl_user_allocate(size_t size);
void __RPC_USER midl_user_free(void* p);

// RPC�I�v�V����
DWORD HandleError(const char* szFunction, DWORD dwError);
RPC_STATUS CALLBACK SecurityCallback(RPC_IF_HANDLE /*hInterface*/, void* /*pBindingHandle*/);
DWORD WINAPI RpcServerListenThreadProc(LPVOID /*pParam*/);
void __RPC_USER CONTEXT_HANDLE_SND_rundown(CONTEXT_HANDLE_SND hContext);