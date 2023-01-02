#include "RpcManager.h"

RpcManager::RpcManager() :
    hThread(NULL)
{
    m_status = (RPC_STATUS)nullptr;
}

RpcManager::~RpcManager()
{

}

HRESULT RpcManager::OnInitServer()
{
    // 受信用のエンドポイントと組み合わせたプロトコルを使用
    // Remote Procedure Call
    m_status = RpcServerUseProtseqEp(
        reinterpret_cast<unsigned char*>("ncacn_ip_tcp"),       // TCP/IPプロトコルを使用
        RPC_C_PROTSEQ_MAX_REQS_DEFAULT,                         // TCP/IPのバックログキューの長さ
        reinterpret_cast<unsigned char*>("4747"),               // 使用するためのTCP/IPポート
        NULL);                                                  // セキュリティなし
    if (m_status)
    {
        m_status = HandleError("RpcServerUseProtseqEp", m_status);
        return E_FAIL;
    }

    // インターフェースを登録
    m_status = RpcServerRegisterIf2(
        RpcIdlSnd_v1_0_s_ifspec,              // 登録するインターフェース
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

HRESULT RpcManager::OnInitClient()
{
    RPC_CSTR szStringBinding = NULL;

    // 文字列バインディングハンドルを作成
    // この関数は単なるprintfで、ここでは接続しない
    m_status = RpcStringBindingCompose(
        NULL,                                               // バインド先のUUID
        reinterpret_cast <unsigned char*>("ncacn_ip_tcp"),  // TCP/IPプロトコルを使用
        reinterpret_cast <unsigned char*>("localhost"),     // 使用するTCP/IPネットワークアドレス
        reinterpret_cast <unsigned char*>("4748"),          // 使用するためのTCP/IPポート
        NULL,                                               // 使用するプロトコル依存のネットワークオプション
        &szStringBinding);                                  // 文字列バインディングの出力
    if (m_status)
    {
        m_status = HandleError("RpcStringBindingCompose", m_status);
        return E_FAIL;
    }

    // 文字列バインディングハンドルの形式を検証し、バインディングハンドルに変換
    // ここでも接続は行われない
    m_status = RpcBindingFromStringBinding(
        szStringBinding,    // 検証する文字列バインディング
        &m_hBinding);       // 結果を明示的なバインディングハンドルに入れる
    if (m_status)
    {
        m_status = HandleError("RpcBindingFromStringBinding", m_status);
        return E_FAIL;
    }

    // 文字列によって割り当てられたメモリを解放
    m_status = RpcStringFree(
        &szStringBinding);    // 解放する文字列
    if (m_status)
    {
        m_status = HandleError("RpcStringFree", m_status);
        return E_FAIL;
    }

    // 部分的にバインドされたサーバーバインディングハンドルを完全にバインドされたサーバーバインディングハンドルで解決させる
    m_status = RpcEpResolveBinding(m_hBinding, RpcIdlRcv_v1_0_c_ifspec);
    if (m_status)
    {
        m_status = HandleError("RpcEpResolveBinding", m_status);
        return E_FAIL;
    }

    return S_OK;
}

HRESULT RpcManager::OnDestroyServer()
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

HRESULT RpcManager::OnDestroyClient()
{
    // バインディングハンドルリソースを解放しサーバーから切断
    m_status = RpcBindingFree(
        &m_hBinding);   // 明示的なバインディングハンドルを解放
    if (m_status)
    {
        m_status = HandleError("RpcBindingFree", m_status);
        return E_FAIL;
    }

    return S_OK;
}

HRESULT RpcManager::OnSend(INT res)
{
    RpcTryExcept
    {
        // RPCコンテキストハンドルをオープン
        CONTEXT_HANDLE_RCV hContext = OpenRcv(m_hBinding, res);

        // 送信先RPC関数をコールし送信
        // hBindingバイディングハンドルが明示的に使用される
        SendRcv(hContext);

        // RPCコンテキストハンドルをクローズ
        CloseRcv(&hContext);
    }
        RpcExcept(1)
    {
        m_status = HandleError("Remote Procedure Call", RpcExceptionCode());
        return E_FAIL;
    }
    RpcEndExcept

        return S_OK;
}