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
    RPC_CSTR szStringBinding = NULL;

    // ������o�C���f�B���O�n���h�����쐬
    // ���̊֐��͒P�Ȃ�printf�ŁA�����ł͐ڑ����Ȃ�
    m_status = RpcStringBindingCompose(
        NULL,                                               // �o�C���h���UUID
        reinterpret_cast <unsigned char*>("ncacn_ip_tcp"),  // TCP/IP�v���g�R�����g�p
        reinterpret_cast <unsigned char*>("localhost"),     // �g�p����TCP/IP�l�b�g���[�N�A�h���X
        reinterpret_cast <unsigned char*>("4747"),          // �g�p���邽�߂�TCP/IP�|�[�g
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
    m_status = RpcEpResolveBinding(m_hBinding, RpcIdlSnd_v1_0_c_ifspec);
    if (m_status)
    {
        m_status = HandleError("RpcEpResolveBinding", m_status);
        return E_FAIL;
    }

    return S_OK;
}

HRESULT RpcManager::OnSend(INPUT_DATA_SND* pData)
{
    RpcTryExcept
    {
        // RPC�R���e�L�X�g�n���h�����I�[�v��
        CONTEXT_HANDLE_SND hContext = OpenSnd(m_hBinding, pData);

        // ���M��RPC�֐����R�[�������M
        // hBinding�o�C�f�B���O�n���h���������I�Ɏg�p�����
        SendSnd(hContext);

        // RPC�R���e�L�X�g�n���h�����N���[�Y
        CloseSnd(&hContext);
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
        m_status = HandleError("RpcBindingFree", m_status);
        return E_FAIL;
    }

    return S_OK;
}