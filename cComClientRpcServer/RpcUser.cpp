#include "RpcUser.h"
#include "CClient.h"

/////////////////////////////////////////////////////
// RPCコールバックイベント
//

// RPCオープン
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

// 送信元からイベントをキャッチ
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

// RPCクローズ
void Close(
    /* [out][in] */ CONTEXT_HANDLE* phContext)
{
    clog << "Close : Context(" << *phContext << ")" << endl;

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
void __RPC_USER CONTEXT_HANDLE_rundown(CONTEXT_HANDLE hContext)
{
    clog << "CONTEXT_HANDLE_rundown : Context(" << hContext << ")" << endl;
    Close(&hContext);
}