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
    // ��~�w��(Ctrl + C)������܂Ńt�b�N�����s���A���[�v���̓t�b�N��ێ�
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(m_hhKbd);   // �t�b�N����

    return S_OK;
}

HRESULT KeyHooker::OnDestroy()
{
    PostQuitMessage(0);     // GetMessage�֏I������

    return S_OK;
}