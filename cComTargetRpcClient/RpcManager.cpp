#include "RpcManager.h"

RpcManager::RpcManager() :
    m_hBinding(NULL)
{
    m_status = (RPC_STATUS)nullptr;
}

RpcManager::~RpcManager()
{

}

HRESULT RpcManager::OnInit()
{
    unsigned char* szStringBinding = NULL;

    // ������o�C���f�B���O�n���h�����쐬
    // ���̊֐��͒P�Ȃ�printf�ŁA�����ł͐ڑ����Ȃ�
    m_status = RpcStringBindingCompose(
        NULL,                                             // �o�C���h���UUID
        reinterpret_cast<unsigned char*>("ncacn_ip_tcp"), // TCP/IP�v���g�R�����g�p
        reinterpret_cast<unsigned char*>("localhost"),    // �g�p����TCP/IP�l�b�g���[�N�A�h���X
        reinterpret_cast<unsigned char*>("4747"),         // �g�p���邽�߂�TCP/IP�|�[�g
        NULL,                                             // �g�p����v���g�R���ˑ��̃l�b�g���[�N�I�v�V����
        &szStringBinding);                                // ������o�C���f�B���O�̏o��
    if (m_status)
    {
        m_status = HandleError("Rpc string binding compose", m_status);
        return E_FAIL;
    }

    // ������o�C���f�B���O�n���h���̌`�������؂��A�o�C���f�B���O�n���h���ɕϊ�
    // �����ł��ڑ��͍s���Ȃ�
    m_status = RpcBindingFromStringBinding(
        szStringBinding,  // ���؂��镶����o�C���f�B���O
        &m_hBinding);       // ���ʂ𖾎��I�ȃo�C���f�B���O�n���h���ɓ����
    if (m_status)
    {
        m_status = HandleError("Rpc binding from string binding", m_status);
        return E_FAIL;
    }

    // ������ɂ���Ċ��蓖�Ă�ꂽ�����������
    m_status = RpcStringFree(
        &szStringBinding);    // ������镶����
    if (m_status)
    {
        m_status = HandleError("Rpc string free", m_status);
        return E_FAIL;
    }

    // �����I�Ƀo�C���h���ꂽ�T�[�o�[�o�C���f�B���O�n���h�������S�Ƀo�C���h���ꂽ�T�[�o�[�o�C���f�B���O�n���h���ŉ���������
    m_status = RpcEpResolveBinding(m_hBinding, RpcIdl_v1_0_c_ifspec);
    if (m_status)
    {
        m_status = HandleError("Rpc EP resolve binding", m_status);
        return E_FAIL;
    }

    return S_OK;
}

HRESULT RpcManager::OnSend()
{
    RpcTryExcept
    {
        // RPC�R���e�L�X�g�n���h�����I�[�v��
        CONTEXT_HANDLE hContext = Open(m_hBinding, "Hello World!");

        // ���M��RPC�֐����R�[�������M
        // hBinding�o�C�f�B���O�n���h���������I�Ɏg�p�����
        Output(hContext);

        // RPC�R���e�L�X�g�n���h�����N���[�Y
        Close(&hContext);
    }
        RpcExcept(1)
    {
        m_status = HandleError("Remote Procedure Call", RpcExceptionCode());
        return E_FAIL;
    }
    RpcEndExcept

        return S_OK;
}

HRESULT RpcManager::OnDestroy()
{
    // �o�C���f�B���O�n���h�����\�[�X��������T�[�o�[����ؒf
    m_status = RpcBindingFree(
        &m_hBinding);   // �����I�ȃo�C���f�B���O�n���h�������
    if (m_status)
    {
        m_status = HandleError("Rpc binding free", m_status);
        return E_FAIL;
    }

    return S_OK;
}