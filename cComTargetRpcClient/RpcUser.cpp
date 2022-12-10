#include "RpcUser.h"

/////////////////////////////////////////////////////
// RPCメモリ
// ランタイムはこれら2つの関数を使用して、文字列をサーバーに渡すのに十分なメモリを割り当て/割り当て解除する
// 

// RPCのメモリ割り当て関数
void* __RPC_USER midl_user_allocate(size_t size)
{
    return malloc(size);
}

// RPCのメモリ解放関数
void __RPC_USER midl_user_free(void* p)
{
    free(p);
}

/////////////////////////////////////////////////////
// RPCオプション
//

// ハンドルエラーメッセージ
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