#pragma once

#include "stdafx.h"
#include "../cRpcIdl/RpcIdl.h"

// RPC�R�[���o�b�N�C�x���g
CONTEXT_HANDLE Open(
    /* [in] */ handle_t hBinding,
    /* [string][in] */ const char* szString);
void Output(
    /* [in] */ CONTEXT_HANDLE hContext);
void Close(
    /* [out][in] */ CONTEXT_HANDLE* phContext);

// RPC������
void* __RPC_USER midl_user_allocate(size_t size);
void __RPC_USER midl_user_free(void* p);

// RPC�I�v�V����
DWORD HandleError(const char* szFunction, DWORD dwError);
RPC_STATUS CALLBACK SecurityCallback(RPC_IF_HANDLE /*hInterface*/, void* /*pBindingHandle*/);
DWORD WINAPI RpcServerListenThreadProc(LPVOID /*pParam*/);
void __RPC_USER CONTEXT_HANDLE_rundown(CONTEXT_HANDLE hContext);