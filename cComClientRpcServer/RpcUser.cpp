#include "RpcUser.h"
#include "CClient.h"

/////////////////////////////////////////////////////
// RPC�R�[���o�b�N�C�x���g
//

// RPC�I�[�v��
CONTEXT_HANDLE Open(
    /* [in] */ handle_t hBinding,
    /* [ptr][in] */ INPUT_DATA* pData)
{
    CONTEXT_HANDLE hContext = pData;
    clog << "-------------------------" << endl;
    clog << "Open : Binding(" << hBinding << ")" << endl;
    clog << "Open : Context(" << hContext << ")" << endl;
    return hContext;
}

// ���M������C�x���g���L���b�`
void Output(
    /* [in] */ CONTEXT_HANDLE hContext)
{
    clog << "Output : Context(" << hContext << ")" << endl;
    INPUT_DATA* pContext = static_cast<INPUT_DATA*>(hContext);
    string* pStr1 = new string(pContext->szStr1);
    string* pStr2 = new string(pContext->szStr2);

    CClient client;
    client.OnInit();
    cout << ">>> " << *pStr1 << endl;
    cout << ">>> " << pContext->args1[0] << " + " << pContext->args1[1] << endl;
    if (FAILED(client.OnSendToServer(pContext->args1[0], pContext->args1[1])))
    {
        cout << "Failure..." << endl;
    }
    cout << ">>> " << *pStr2 << endl;
    cout << ">>> " << pContext->args2[0] << " + " << pContext->args2[1] << endl;
    if (FAILED(client.OnSendToServer(pContext->args2[0], pContext->args2[1])))
    {
        cout << "Failure..." << endl;
    }
}

// RPC�N���[�Y
void Close(
    /* [out][in] */ CONTEXT_HANDLE* phContext)
{
    clog << "Close : Context(" << *phContext << ")" << endl;

    // �R���e�L�X�g�n���h����NULL�ɐݒ�
    *phContext = NULL;
}

/////////////////////////////////////////////////////
// RPC������
// �����^�C���͂����2�̊֐����g�p���āA��������T�[�o�[�ɓn���̂ɏ\���ȃ����������蓖��/���蓖�ĉ�������
//

// RPC�̃��������蓖�Ċ֐�
void* __RPC_USER midl_user_allocate(size_t size)
{
    return malloc(size);
}

// RPC�̃���������֐�
void __RPC_USER midl_user_free(void* p)
{
    free(p);
}

/////////////////////////////////////////////////////
// RPC�I�v�V����
//

// �n���h���G���[���b�Z�[�W
DWORD HandleError(const char* szFunction, DWORD dwError)
{
    void* pBuffer = NULL;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK,
        NULL,
        dwError,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        LPTSTR(&pBuffer),
        0,
        NULL);

    cerr << szFunction << " failed. "
        << (pBuffer ? LPCSTR(pBuffer) : "Unknown error. ")
        << "(" << dwError << ")" << endl;
    
    LocalFree(pBuffer);
    
    return dwError;
}

// �P���ȃZ�L�����e�B�R�[���o�b�N
RPC_STATUS CALLBACK SecurityCallback(RPC_IF_HANDLE /*hInterface*/, void* /*pBindingHandle*/)
{
    return RPC_S_OK;    // ��ɒN�ł�����
}

// ���MRPC�R�[���ɉ�������X���b�h
DWORD WINAPI RpcServerListenThreadProc(LPVOID /*pParam*/)
{
    // �o�^����Ă���S�ẴC���^�[�t�F�[�X��RPC�̉������J�n
    // ���̌ďo�́ARpcMgmtStopServerListening���Ăяo�����܂Ŗ߂�Ȃ�
    return RpcServerListen(
        1,                                // �X���b�h�̐����ŏ���
        RPC_C_LISTEN_MAX_CALLS_DEFAULT,   // �X���b�h�̐����ő吔
        FALSE);                           // �������������J�n
}

// �N���C�A���g�ւ̐ڑ�������ꂽ�ꍇ�ARPC�����^�C���͂��̊֐����R�[��
void __RPC_USER CONTEXT_HANDLE_rundown(CONTEXT_HANDLE hContext)
{
    clog << "CONTEXT_HANDLE_rundown : Context(" << hContext << ")" << endl;
    Close(&hContext);
}