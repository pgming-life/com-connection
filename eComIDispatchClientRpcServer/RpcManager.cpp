#include "RpcManager.h"

RpcManager::RpcManager() :
    hThread(NULL)
{
    m_status = (RPC_STATUS)nullptr;
}

RpcManager::~RpcManager()
{

}

HRESULT RpcManager::OnInitServer()
{
    // ��M�p�̃G���h�|�C���g�Ƒg�ݍ��킹���v���g�R�����g�p
    // Remote Procedure Call
    m_status = RpcServerUseProtseqEp(
        reinterpret_cast<unsigned char*>("ncacn_ip_tcp"),       // TCP/IP�v���g�R�����g�p
        RPC_C_PROTSEQ_MAX_REQS_DEFAULT,                         // TCP/IP�̃o�b�N���O�L���[�̒���
        reinterpret_cast<unsigned char*>("4747"),               // �g�p���邽�߂�TCP/IP�|�[�g
        NULL);                                                  // �Z�L�����e�B�Ȃ�
    if (m_status)
    {
        m_status = HandleError("RpcServerUseProtseqEp", m_status);
        return E_FAIL;
    }

    // �C���^�[�t�F�[�X��o�^
    m_status = RpcServerRegisterIf2(
        RpcIdlSnd_v1_0_s_ifspec,              // �o�^����C���^�[�t�F�[�X
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

HRESULT RpcManager::OnInitClient()
{
    RPC_CSTR szStringBinding = NULL;

    // ������o�C���f�B���O�n���h�����쐬
    // ���̊֐��͒P�Ȃ�printf�ŁA�����ł͐ڑ����Ȃ�
    m_status = RpcStringBindingCompose(
        NULL,                                               // �o�C���h���UUID
        reinterpret_cast <unsigned char*>("ncacn_ip_tcp"),  // TCP/IP�v���g�R�����g�p
        reinterpret_cast <unsigned char*>("localhost"),     // �g�p����TCP/IP�l�b�g���[�N�A�h���X
        reinterpret_cast <unsigned char*>("4748"),          // �g�p���邽�߂�TCP/IP�|�[�g
        NULL,                                               // �g�p����v���g�R���ˑ��̃l�b�g���[�N�I�v�V����
        &szStringBinding);                                  // ������o�C���f�B���O�̏o��
    if (m_status)
    {
        m_status = HandleError("RpcStringBindingCompose", m_status);
        return E_FAIL;
    }

    // ������o�C���f�B���O�n���h���̌`�������؂��A�o�C���f�B���O�n���h���ɕϊ�
    // �����ł��ڑ��͍s���Ȃ�
    m_status = RpcBindingFromStringBinding(
        szStringBinding,    // ���؂��镶����o�C���f�B���O
        &m_hBinding);       // ���ʂ𖾎��I�ȃo�C���f�B���O�n���h���ɓ����
    if (m_status)
    {
        m_status = HandleError("RpcBindingFromStringBinding", m_status);
        return E_FAIL;
    }

    // ������ɂ���Ċ��蓖�Ă�ꂽ�����������
    m_status = RpcStringFree(
        &szStringBinding);    // ������镶����
    if (m_status)
    {
        m_status = HandleError("RpcStringFree", m_status);
        return E_FAIL;
    }

    // �����I�Ƀo�C���h���ꂽ�T�[�o�[�o�C���f�B���O�n���h�������S�Ƀo�C���h���ꂽ�T�[�o�[�o�C���f�B���O�n���h���ŉ���������
    m_status = RpcEpResolveBinding(m_hBinding, RpcIdlRcv_v1_0_c_ifspec);
    if (m_status)
    {
        m_status = HandleError("RpcEpResolveBinding", m_status);
        return E_FAIL;
    }

    return S_OK;
}

HRESULT RpcManager::OnDestroyServer()
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

HRESULT RpcManager::OnDestroyClient()
{
    // �o�C���f�B���O�n���h�����\�[�X��������T�[�o�[����ؒf
    m_status = RpcBindingFree(
        &m_hBinding);   // �����I�ȃo�C���f�B���O�n���h�������
    if (m_status)
    {
        m_status = HandleError("RpcBindingFree", m_status);
        return E_FAIL;
    }

    return S_OK;
}

HRESULT RpcManager::OnSend(INT res)
{
    RpcTryExcept
    {
        // RPC�R���e�L�X�g�n���h�����I�[�v��
        CONTEXT_HANDLE_RCV hContext = OpenRcv(m_hBinding, res);

        // ���M��RPC�֐����R�[�������M
        // hBinding�o�C�f�B���O�n���h���������I�Ɏg�p�����
        SendRcv(hContext);

        // RPC�R���e�L�X�g�n���h�����N���[�Y
        CloseRcv(&hContext);
    }
        RpcExcept(1)
    {
        m_status = HandleError("Remote Procedure Call", RpcExceptionCode());
        return E_FAIL;
    }
    RpcEndExcept

        return S_OK;
}