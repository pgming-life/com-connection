#include "RpcServer.h"

/////////////////////////////////////////////////////
// RPC制御
//

// RPCオープン
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

// クライアントへ返信
void Output(
    /* [in] */ CONTEXT_HANDLE hContext)
{
    clog << "Output: Context = " << hContext << endl;
    string* pContext = static_cast<string*>(hContext);
    cout << *pContext << endl;
}

// RPCクローズ
void Close(
    /* [out][in] */ CONTEXT_HANDLE* phContext)
{
    clog << "Close: Context = " << *phContext << endl;
    string* pContext = static_cast<string*>(*phContext);
    delete pContext;

    // コンテキストハンドルをNULLに設定
    *phContext = NULL;
}

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
        LPTSTR(&pBuffer),
        0,
        NULL);

    cerr << szFunction << " failed. "
        << (pBuffer ? LPCTSTR(pBuffer) : "Unknown error. ")
        << "(" << dwError << ")" << endl;
    LocalFree(pBuffer);
    return dwError;
}

// 単純なセキュリティコールバック
RPC_STATUS CALLBACK SecurityCallback(RPC_IF_HANDLE /*hInterface*/, void* /*pBindingHandle*/)
{
    return RPC_S_OK;    // 常に誰でも許可
}

// 着信RPCコールに応答するスレッド
DWORD WINAPI RpcServerListenThreadProc(LPVOID /*pParam*/)
{
    // 登録されている全てのインターフェースのRPCの応答を開始
    // この呼出は、RpcMgmtStopServerListeningが呼び出されるまで戻らない
    return RpcServerListen(
        1,                                // スレッドの推奨最小数
        RPC_C_LISTEN_MAX_CALLS_DEFAULT,   // スレッドの推奨最大数
        FALSE);                           // 今すぐ応答を開始
}

// クライアントへの接続が失われた場合、RPCランタイムはこの関数をコール
void __RPC_USER CONTEXT_HANDLE_rundown(CONTEXT_HANDLE hContext)
{
    clog << "CONTEXT_HANDLE_rundown: Context = " << hContext << endl;
    Close(&hContext);
}