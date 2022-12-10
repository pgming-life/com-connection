#include "KeyHooker.h"

KeyHooker::KeyHooker(Hhkbd_t hhKbd) :
    m_hhKbd(hhKbd)
{

}

KeyHooker::~KeyHooker()
{

}

HRESULT KeyHooker::OnInit()
{
    // 停止指示(Ctrl + C)があるまでフックを実行し、ループ中はフックを保持
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(m_hhKbd);   // フック解除

    return S_OK;
}

HRESULT KeyHooker::OnDestroy()
{
    PostQuitMessage(0);     // GetMessageへ終了命令

    return S_OK;
}