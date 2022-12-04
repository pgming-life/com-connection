#include "RpcServer.h"

/////////////////////////////////////////////////////
// RPC����
//

// RPC�I�[�v��
CONTEXT_HANDLE Open(
    /* [in] */ handle_t hBinding,
    /* [string][in] */ const char* szString)
{
    string* pContext = new string(szString);
    CONTEXT_HANDLE hContext = pContext;
    clog << "Open: Binding = " << hBinding
        << "; Context = " << hContext << endl;
    return hContext;
}

// �N���C�A���g�֕ԐM
void Output(
    /* [in] */ CONTEXT_HANDLE hContext)
{
    clog << "Output: Context = " << hContext << endl;
    string* pContext = static_cast<string*>(hContext);
    cout << *pContext << endl;
}

// RPC�N���[�Y
void Close(
    /* [out][in] */ CONTEXT_HANDLE* phContext)
{
    clog << "Close: Context = " << *phContext << endl;
    string* pContext = static_cast<string*>(*phContext);
    delete pContext;

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
        << (pBuffer ? LPCTSTR(pBuffer) : "Unknown error. ")
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
    clog << "CONTEXT_HANDLE_rundown: Context = " << hContext << endl;
    Close(&hContext);
}