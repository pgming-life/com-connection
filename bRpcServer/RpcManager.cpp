#include "RpcManager.h"

RpcManager::RpcManager() :
    hThread(NULL)
{
    m_status = (RPC_STATUS)nullptr;
}

RpcManager::~RpcManager()
{

}

HRESULT RpcManager::OnInit()
{
    // 受信用のエンドポイントと組み合わせたプロトコルを使用
    // Remote Procedure Call
    m_status = RpcServerUseProtseqEp(
        reinterpret_cast<unsigned char*>("ncacn_ip_tcp"), // TCP/IPプロトコルを使用
        RPC_C_PROTSEQ_MAX_REQS_DEFAULT,                   // TCP/IPのバックログキューの長さ
        reinterpret_cast<unsigned char*>("4747"),         // 使用するためのTCP/IPポート
        NULL);                                            // セキュリティなし
    if (m_status)
    {
        m_status = HandleError("RpcServerUseProtseqEp", m_status);
        return E_FAIL;
    }

    // インターフェースを登録
    m_status = RpcServerRegisterIf2(
        RpcIdl_v1_0_s_ifspec,                 // 登録するインターフェース
        NULL,                                 // MIDLで生成されたエントリポイントベクトルを使用
        NULL,                                 // MIDLで生成されたエントリポイントベクトルを使用
        RPC_IF_ALLOW_CALLBACKS_WITH_NO_AUTH,  // セキュリティコールバックの使用を強制
        RPC_C_LISTEN_MAX_CALLS_DEFAULT,       // デフォルトの同時呼び出し数を使用
        (unsigned)-1,                         // 着信データブロックの最大サイズは無限
        SecurityCallback);                    // 単純なセキュリティコールバック
    if (m_status)
    {
        m_status = HandleError("RpcServerRegisterIf", m_status);
        return E_FAIL;
    }

    // スレッドハンドルを作成
    hThread = CreateThread(
        NULL,
        0,
        RpcServerListenThreadProc,
        NULL,
        0,
        NULL);
    if (!hThread)
    {
        m_status = HandleError("CreateThread", GetLastError());
        return E_FAIL;
    }

    return S_OK;
}

HRESULT RpcManager::OnDestroy()
{
    // RPC受信サービスを停止
    m_status = RpcMgmtStopServerListening(NULL);
    if (m_status)
    {
        m_status = HandleError("RpcMgmtStopServerListening", m_status);
        return E_FAIL;
    }

    // スレッドが終了するまで待機
    while (WaitForSingleObject(hThread, 1000) == WAIT_TIMEOUT)
        clog << '.';
    clog << endl << "Listen thread finished." << endl;

    // スレッドハンドルをクローズ
    DWORD dwExitCodeThread = 0;
    GetExitCodeThread(hThread, &dwExitCodeThread);
    CloseHandle(hThread);
    if (dwExitCodeThread)
    {
        m_status = HandleError("RpcServerListen", dwExitCodeThread);
        return E_FAIL;
    }

    return S_OK;
}