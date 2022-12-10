#pragma once

#include "stdafx.h"
#include "RpcUser.h"

class RpcManager final
{
public:
    RpcManager();
    ~RpcManager();

    HRESULT OnInit();
    HRESULT OnSend();
    HRESULT OnDestroy();

private:
    RPC_STATUS m_status;
    handle_t m_hBinding;
};