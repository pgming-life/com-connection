#include "RpcUser.h"
#include "CClient.h"

/////////////////////////////////////////////////////
// RPC�R�[���o�b�N�C�x���g
//

// RPC�I�[�v��
CONTEXT_HANDLE_SND OpenSnd(
    /* [in] */ handle_t hBinding,
    /* [ptr][in] */ INPUT_DATA_SND* pData)
{
    CONTEXT_HANDLE_SND hContext = pData;
    clog << "-------------------------" << endl;
    clog << "Open : Binding(" << hBinding << ")" << endl;
    clog << "Open : Context(" << hContext << ")" << endl;
    return hContext;
}

// ���M������C�x���g���L���b�`
void SendSnd(
    /* [in] */ CONTEXT_HANDLE_SND hContext)
{
    clog << "Output : Context(" << hContext << ")" << endl;
    INPUT_DATA_SND* pContext = static_cast<INPUT_DATA_SND*>(hContext);
    
    // COM������
    if (FAILED(CoInitialize(NULL)))
    {
        cout << "COM�������Ɏ��s���܂����B" << endl;
        cout << "�I�����܂�..." << endl;
        Sleep(2000);
        exit(0);
    }

    // COM�N���C�A���g����
    {
        CClient client;
        client.OnInit(pContext->args1, pContext->args2);
        client.OnSend();
        client.OnDestroy();
    }

    // COM���
    CoUninitialize();
}

// RPC�N���[�Y
void CloseSnd(
    /* [out][in] */ CONTEXT_HANDLE_SND* phContext)
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
void __RPC_USER CONTEXT_HANDLE_SND_rundown(CONTEXT_HANDLE_SND hContext)
{
    clog << "CONTEXT_HANDLE_SND_rundown : Context(" << hContext << ")" << endl;
    CloseSnd(&hContext);
}