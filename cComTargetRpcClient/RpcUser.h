#pragma once

#include "stdafx.h"
#include "../cRpcIdl/RpcIdl.h"

// RPCメモリ
void* __RPC_USER midl_user_allocate(size_t size);
void __RPC_USER midl_user_free(void* p);

// RPCオプション
DWORD HandleError(const char* szFunction, DWORD dwError);