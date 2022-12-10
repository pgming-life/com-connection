#pragma once

#include "IKeyHooker.h"

// ex) PKBDLLHOOKSTRUCT
struct KeyData
{
    DWORD   vkCode;
    //DWORD   scanCode;
    //DWORD   flags;
    LPCSTR sendStr;
};

const vector<KeyData> kyDataList =
{
    // WinUser.h
    {0x30, "0"}, // 0
    {0x31, "1"}, // 1
    {0x32, "2"}, // 2
    {0x33, "3"}, // 3
    {0x34, "4"}, // 4
    {0x35, "5"}, // 5
    {0x36, "6"}, // 6
    {0x37, "7"}, // 7
    {0x38, "8"}, // 8
    {0x39, "9"}, // 9
    {0x41, "A"}, // A
    {0x42, "B"}, // B
    {0x43, "C"}, // C
    {0x44, "D"}, // D
    {0x45, "E"}, // E
    {0x46, "F"}, // F
    {0x47, "G"}, // G
    {0x48, "H"}, // H
    {0x49, "I"}, // I
    {0x4A, "J"}, // J
    {0x4B, "K"}, // K
    {0x4C, "L"}, // L
    {0x4D, "M"}, // M
    {0x4E, "N"}, // N
    {0x4F, "O"}, // O
    {0x50, "P"}, // P
    {0x51, "Q"}, // Q
    {0x52, "R"}, // R
    {0x53, "S"}, // S
    {0x54, "T"}, // T
    {0x55, "U"}, // U
    {0x56, "V"}, // V
    {0x57, "W"}, // W
    {0x58, "X"}, // X
    {0x59, "Y"}, // Y
    {0x5A, "Z"}, // Z
};

class KeyHooker : public IKeyHooker
{
public:
    struct KeyInfo
    {
        DWORD m_vkCode;
        DWORD m_scanCode;
        DWORD m_flags;
        DWORD m_time;
        ULONG_PTR m_dwExtraInfo;
    };

    explicit KeyHooker(Hhkbd_t hhKbd);
    virtual ~KeyHooker();
    
    virtual HRESULT OnInit();
    virtual HRESULT OnDestroy();

private:
    Hhkbd_t m_hhKbd;
};