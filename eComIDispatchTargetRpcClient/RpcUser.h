#pragma once

#include "stdafx.h"
#include "../eRpcIdl/RpcIdlSnd.h"

// RPC������
void* __RPC_USER midl_user_allocate(size_t size);
void __RPC_USER midl_user_free(void* p);

// RPC�I�v�V����
DWORD HandleError(const char* szFunction, DWORD dwError);