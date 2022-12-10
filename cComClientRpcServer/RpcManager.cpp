#include "RpcManager.h"

RpcManager::RpcManager() :
    hThread(NULL)
{
    m_status = (RPC_STATUS)nullptr;
}

RpcManager::~RpcManager()
{

}

HRESULT RpcManager::OnInit()
{
    // ��M�p�̃G���h�|�C���g�Ƒg�ݍ��킹���v���g�R�����g�p
    // Remote Procedure Call
    m_status = RpcServerUseProtseqEp(
        reinterpret_cast<unsigned char*>("ncacn_ip_tcp"), // TCP/IP�v���g�R�����g�p
        RPC_C_PROTSEQ_MAX_REQS_DEFAULT,                   // TCP/IP�̃o�b�N���O�L���[�̒���
        reinterpret_cast<unsigned char*>("4747"),         // �g�p���邽�߂�TCP/IP�|�[�g
        NULL);                                            // �Z�L�����e�B�Ȃ�
    if (m_status)
    {
        m_status = HandleError("RpcServerUseProtseqEp", m_status);
        return E_FAIL;
    }

    // �C���^�[�t�F�[�X��o�^
    m_status = RpcServerRegisterIf2(
        RpcIdl_v1_0_s_ifspec,                 // �o�^����C���^�[�t�F�[�X
        NULL,                                 // MIDL�Ő������ꂽ�G���g���|�C���g�x�N�g�����g�p
        NULL,                                 // MIDL�Ő������ꂽ�G���g���|�C���g�x�N�g�����g�p
        RPC_IF_ALLOW_CALLBACKS_WITH_NO_AUTH,  // �Z�L�����e�B�R�[���o�b�N�̎g�p������
        RPC_C_LISTEN_MAX_CALLS_DEFAULT,       // �f�t�H���g�̓����Ăяo�������g�p
        (unsigned)-1,                         // ���M�f�[�^�u���b�N�̍ő�T�C�Y�͖���
        SecurityCallback);                    // �P���ȃZ�L�����e�B�R�[���o�b�N
    if (m_status)
    {
        m_status = HandleError("RpcServerRegisterIf", m_status);
        return E_FAIL;
    }

    // �X���b�h�n���h�����쐬
    hThread = CreateThread(
        NULL,
        0,
        RpcServerListenThreadProc,
        NULL,
        0,
        NULL);
    if (!hThread)
    {
        m_status = HandleError("CreateThread", GetLastError());
        return E_FAIL;
    }

    return S_OK;
}

HRESULT RpcManager::OnDestroy()
{
    // RPC��M�T�[�r�X���~
    m_status = RpcMgmtStopServerListening(NULL);
    if (m_status)
    {
        m_status = HandleError("RpcMgmtStopServerListening", m_status);
        return E_FAIL;
    }

    // �X���b�h���I������܂őҋ@
    while (WaitForSingleObject(hThread, 1000) == WAIT_TIMEOUT)
        clog << '.';
    clog << endl << "Listen thread finished." << endl;

    // �X���b�h�n���h�����N���[�Y
    DWORD dwExitCodeThread = 0;
    GetExitCodeThread(hThread, &dwExitCodeThread);
    CloseHandle(hThread);
    if (dwExitCodeThread)
    {
        m_status = HandleError("RpcServerListen", dwExitCodeThread);
        return E_FAIL;
    }

    return S_OK;
}