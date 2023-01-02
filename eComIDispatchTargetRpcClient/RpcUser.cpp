#include "RpcUser.h"

/////////////////////////////////////////////////////
// RPCコールバックイベント
//

// RPCオープン
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

// 送信元からイベントをキャッチ
void SendRcv(
    /* [in] */ CONTEXT_HANDLE_RCV hContext)
{
    clog << "SendRcv : Context(" << hContext << ")" << endl;
    int* pContext = static_cast<int*>(hContext);
    cout << "((( Receive ))) " << "Sum up result : " <<  *pContext << endl;    // 出力
}

// RPCクローズ
void CloseRcv(
    /* [out][in] */ CONTEXT_HANDLE_RCV* phContext)
{
    clog << "CloseRcv : Context(" << *phContext << ")" << endl;
    int* pContext = static_cast<int*>(*phContext);
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
        LPSTR(&pBuffer),
        0,
        NULL);

    cerr << szFunction << " failed. "
        << (pBuffer ? LPCSTR(pBuffer) : "Unknown error. ")
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
void __RPC_USER CONTEXT_HANDLE_RCV_rundown(CONTEXT_HANDLE_RCV hContext)
{
    clog << "CONTEXT_HANDLE_RCV_rundown : Context(" << hContext << ")" << endl;
    CloseRcv(&hContext);
}