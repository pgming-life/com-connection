#include "stdafx.h"
#include "RpcManager.h"
#include "KeyHooker.h"

unique_ptr<RpcManager> g_rpc;
unique_ptr<KeyHooker> g_kbd;

int main()
{
    // ������
    g_rpc.reset(new RpcManager());
    cout << "RPC start." << endl;
    g_rpc->OnInit();

    // �჌�x���̃L�[�{�[�h�E�}�E�X�̃t�b�N���擾
    g_kbd.reset(new KeyHooker(
        SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKbdProc, 0, 0)
    ));

    // �t�b�N�J�n
    cout << "Please press key...\n"
        << "[0-9,A-Z] Enter is end." << endl;;
    g_kbd->OnInit();

    // ���
    cout << "RPC release." << endl;
    g_rpc->OnDestroy();

    cout << "Process release..." << endl;
    Sleep(1000);
}

LRESULT CALLBACK LowLevelKbdProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    BOOL fEatKeystroke = FALSE;

    if (nCode == HC_ACTION)
    {
        PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
        BOOL bSent = FALSE;

        switch (wParam)
        {
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
            for (auto ite = kyDataList.begin(); ite != kyDataList.end(); ite++)
            {
                
                if (fEatKeystroke = (p->vkCode == ite->vkCode))
                {
                    // ���M
                    cout << ite->sendStr << endl;
                    g_rpc->OnSend(ite->sendStr);
                    bSent = TRUE;
                    break;
                }
            }
            if (p->vkCode == VK_RETURN) // Enter
            {
                // �t�b�N�I��
                g_kbd->OnDestroy();
            }
            if (!bSent)
            {
                // ��L�ȊO�̃L�[�͖���
                fEatKeystroke = FALSE;
            }
            break;
        case WM_KEYUP:
        case WM_SYSKEYUP:
            break;
        }
    }

    return(fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam));
}