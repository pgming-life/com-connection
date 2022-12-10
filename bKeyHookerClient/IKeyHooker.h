#pragma once

#include "stdafx.h"

LRESULT CALLBACK LowLevelKbdProc(int nCode, WPARAM wParam, LPARAM lParam);

class IKeyHooker
{
public:
    typedef HHOOK Hhkbd_t;

    virtual ~IKeyHooker() {}
    virtual HRESULT OnInit() = 0;
    virtual HRESULT OnDestroy() = 0;
};