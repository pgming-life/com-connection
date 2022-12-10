#include "RpcUser.h"

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
        LPWSTR(&pBuffer),
        0,
        NULL);

    cerr << szFunction << " failed. "
        << (pBuffer ? LPCSTR(pBuffer) : "Unknown error. ")
        << "(" << dwError << ")" << endl;
    
    LocalFree(pBuffer);

    return dwError;
}