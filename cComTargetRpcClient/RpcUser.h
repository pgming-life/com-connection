#pragma once

#include "stdafx.h"
#include "../cRpcIdl/RpcIdl.h"

// RPC������
void* __RPC_USER midl_user_allocate(size_t size);
void __RPC_USER midl_user_free(void* p);

// RPC�I�v�V����
DWORD HandleError(const char* szFunction, DWORD dwError);