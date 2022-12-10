#pragma once

#include "stdafx.h"
#include "../cRpcIdl/RpcIdl.h"

// RPCƒƒ‚ƒŠ
void* __RPC_USER midl_user_allocate(size_t size);
void __RPC_USER midl_user_free(void* p);

// RPCƒIƒvƒVƒ‡ƒ“
DWORD HandleError(const char* szFunction, DWORD dwError);