#include "RpcClient.h"

int main()
{
    RPC_STATUS status;
    unsigned char* szStringBinding = NULL;

    clog << "Calling RpcStringBindingCompose" << endl;

    // ������o�C���f�B���O�n���h�����쐬
    // ���̊֐��͒P�Ȃ�printf�ŁA�����ł͐ڑ����Ȃ�
    status = RpcStringBindingCompose(
        NULL,                                             // �o�C���h���UUID
        reinterpret_cast<unsigned char*>("ncacn_ip_tcp"), // TCP/IP�v���g�R�����g�p
        reinterpret_cast<unsigned char*>("localhost"),    // �g�p����TCP/IP�l�b�g���[�N�A�h���X
        reinterpret_cast<unsigned char*>("1688"),         // �g�p���邽�߂�TCP/IP�|�[�g
        NULL,                                             // �g�p����v���g�R���ˑ��̃l�b�g���[�N�I�v�V����
        &szStringBinding);                                // ������o�C���f�B���O�̏o��
    if (status)
        return HandleError("RpcStringBindingCompose", status);

    handle_t hBinding = NULL;

    clog << "Calling RpcBindingFromStringBinding" << endl;

    // ������o�C���f�B���O�n���h���̌`�������؂��A�o�C���f�B���O�n���h���ɕϊ�
    // �����ł��ڑ��͍s���Ȃ�
    status = RpcBindingFromStringBinding(
        szStringBinding,  // ���؂��镶����o�C���f�B���O
        &hBinding);       // ���ʂ𖾎��I�ȃo�C���f�B���O�n���h���ɓ����
    if (status)
        return HandleError("RpcBindingFromStringBinding", status);

    clog << "Calling RpcStringFree" << endl;

    // ������ɂ���Ċ��蓖�Ă�ꂽ�����������
    status = RpcStringFree(
        &szStringBinding);    // ������镶����
    if (status)
        return HandleError("RpcStringFree", status);

    clog << "Calling RpcEpResolveBinding" << endl;

    // �����I�Ƀo�C���h���ꂽ�T�[�o�[�o�C���f�B���O�n���h�������S�Ƀo�C���h���ꂽ�T�[�o�[�o�C���f�B���O�n���h���ŉ���������
    status = RpcEpResolveBinding(hBinding, RpcIdl_v1_0_c_ifspec);
    if (status)
        return HandleError("RpcEpResolveBinding", status);

    RpcTryExcept
    {
        clog << "Calling Open" << endl;

        CONTEXT_HANDLE hContext = Open(hBinding, "Hello Context World!");

        cout << "Press enter to call Output" << endl;
        cin.get();

        clog << "Calling Output" << endl;

        // RPC�֐����R�[��
        // hBinding�o�C�f�B���O�n���h���������I�Ɏg�p�����
        Output(hContext);

        cout << "Press enter to call Close" << endl;
        cin.get();

        clog << "Calling Close" << endl;

        // �R���e�L�X�g�n���h�����N���[�Y
        Close(&hContext);
    }
        RpcExcept(1)
    {
        HandleError("Remote Procedure Call", RpcExceptionCode());
    }
    RpcEndExcept

    clog << "Calling RpcBindingFree" << endl;

    // �o�C���f�B���O�n���h�����\�[�X��������T�[�o�[����ؒf
    status = RpcBindingFree(
        &hBinding);   // �����I�ȃo�C���f�B���O�n���h�������
    if (status)
        return HandleError("RpcBindingFree", status);

    cout << "Press enter to exit" << endl;
    cin.get();
}