#pragma once

#include "stdafx.h"
#include "RpcUser.h"

class RpcManager final
{
public:
    RpcManager();
    ~RpcManager();

    HRESULT OnInitServer();
    HRESULT OnInitClient();
    HRESULT OnDestroyServer();
    HRESULT OnDestroyClient();
    HRESULT OnSend(INT res);

private:
    RPC_STATUS m_status;
    HANDLE hThread;
    handle_t m_hBinding;
};