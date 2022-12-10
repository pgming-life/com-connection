#pragma once

#include "stdafx.h"
#include "RpcUser.h"

class RpcManager final
{
public:
    RpcManager();
    ~RpcManager();

    HRESULT OnInit();
    HRESULT OnDestroy();

private:
    RPC_STATUS m_status;
    HANDLE hThread;
};