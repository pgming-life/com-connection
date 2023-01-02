#include "RpcUser.h"

/////////////////////////////////////////////////////
// RPC�R�[���o�b�N�C�x���g
//

// RPC�I�[�v��
CONTEXT_HANDLE_RCV OpenRcv(
    /* [in] */ handle_t hBinding,
    /* [in] */ int res)
{
    int* pContext = new int(res);
    CONTEXT_HANDLE_RCV hContext = pContext;
    clog << "OpenRcv : Binding(" << hBinding << ")" << endl;
    clog << "OpenRcv : Context(" << hContext << ")" << endl;
    return hContext;
}

// ���M������C�x���g���L���b�`
void SendRcv(
    /* [in] */ CONTEXT_HANDLE_RCV hContext)
{
    clog << "SendRcv : Context(" << hContext << ")" << endl;
    int* pContext = static_cast<int*>(hContext);
    cout << "((( Receive ))) " << "Sum up result : " <<  *pContext << endl;    // �o��
}

// RPC�N���[�Y
void CloseRcv(
    /* [out][in] */ CONTEXT_HANDLE_RCV* phContext)
{
    clog << "CloseRcv : Context(" << *phContext << ")" << endl;
    int* pContext = static_cast<int*>(*phContext);
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
        LPSTR(&pBuffer),
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
void __RPC_USER CONTEXT_HANDLE_RCV_rundown(CONTEXT_HANDLE_RCV hContext)
{
    clog << "CONTEXT_HANDLE_RCV_rundown : Context(" << hContext << ")" << endl;
    CloseRcv(&hContext);
}