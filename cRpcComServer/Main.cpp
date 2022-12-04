#include "RpcServer.h"

int main()
{
    RPC_STATUS status;

    clog << "Calling RpcServerUseProtseqEp" << endl;

    // ��M�p�̃G���h�|�C���g�Ƒg�ݍ��킹���v���g�R�����g�p
    // Remote Procedure Call
    status = RpcServerUseProtseqEp(
        reinterpret_cast<unsigned char*>("ncacn_ip_tcp"), // TCP/IP�v���g�R�����g�p
        RPC_C_PROTSEQ_MAX_REQS_DEFAULT,                   // TCP/IP�̃o�b�N���O�L���[�̒���
        reinterpret_cast<unsigned char*>("1688"),         // �g�p���邽�߂�TCP/IP�|�[�g
        NULL);                                            // �Z�L�����e�B�Ȃ�
    if (status)
        return HandleError("RpcServerUseProtseqEp", status);

    clog << "Calling RpcServerRegisterIf" << endl;

    // �C���^�[�t�F�[�X��o�^
    status = RpcServerRegisterIf2(
        RpcIdl_v1_0_s_ifspec,                 // �o�^����C���^�[�t�F�[�X
        NULL,                                 // MIDL�Ő������ꂽ�G���g���|�C���g�x�N�g�����g�p
        NULL,                                 // MIDL�Ő������ꂽ�G���g���|�C���g�x�N�g�����g�p
        RPC_IF_ALLOW_CALLBACKS_WITH_NO_AUTH,  // �Z�L�����e�B�R�[���o�b�N�̎g�p������
        RPC_C_LISTEN_MAX_CALLS_DEFAULT,       // �f�t�H���g�̓����Ăяo�������g�p
        (unsigned)-1,                         // ���M�f�[�^�u���b�N�̍ő�T�C�Y�͖���
        SecurityCallback);                    // �P���ȃZ�L�����e�B�R�[���o�b�N
    if (status)
        return HandleError("RpcServerRegisterIf", status);

    clog << "Creating listen thread" << endl;
    const HANDLE hThread = CreateThread(
        NULL,
        0,
        RpcServerListenThreadProc,
        NULL,
        0,
        NULL);
    if (!hThread)
        return HandleError("CreateThread", GetLastError());

    cout << "Press enter to stop listening" << endl;
    cin.get();

    clog << "Calling RpcMgmtStopServerListening" << endl;
    status = RpcMgmtStopServerListening(NULL);
    if (status)
        return HandleError("RpcMgmtStopServerListening", status);

    clog << "Waiting for listen thread to finish";
    while (WaitForSingleObject(hThread, 1000) == WAIT_TIMEOUT)
        clog << '.';
    clog << endl << "Listen thread finished" << std::endl;

    DWORD dwExitCodeThread = 0;
    GetExitCodeThread(hThread, &dwExitCodeThread);
    CloseHandle(hThread);
    if (dwExitCodeThread)
        return HandleError("RpcServerListen", dwExitCodeThread);

    cout << "Press enter to exit" << endl;
    cin.get();
}