#include "RpcManager.h"

RpcManager::RpcManager() :
    m_hBinding(NULL)
{
    m_status = (RPC_STATUS)nullptr;
}

RpcManager::~RpcManager()
{

}

HRESULT RpcManager::OnInit()
{
    unsigned char* szStringBinding = NULL;

    // 文字列バインディングハンドルを作成
    // この関数は単なるprintfで、ここでは接続しない
    m_status = RpcStringBindingCompose(
        NULL,                                             // バインド先のUUID
        reinterpret_cast<unsigned char*>("ncacn_ip_tcp"), // TCP/IPプロトコルを使用
        reinterpret_cast<unsigned char*>("localhost"),    // 使用するTCP/IPネットワークアドレス
        reinterpret_cast<unsigned char*>("4747"),         // 使用するためのTCP/IPポート
        NULL,                                             // 使用するプロトコル依存のネットワークオプション
        &szStringBinding);                                // 文字列バインディングの出力
    if (m_status)
    {
        m_status = HandleError("Rpc string binding compose", m_status);
        return E_FAIL;
    }

    // 文字列バインディングハンドルの形式を検証し、バインディングハンドルに変換
    // ここでも接続は行われない
    m_status = RpcBindingFromStringBinding(
        szStringBinding,  // 検証する文字列バインディング
        &m_hBinding);       // 結果を明示的なバインディングハンドルに入れる
    if (m_status)
    {
        m_status = HandleError("Rpc binding from string binding", m_status);
        return E_FAIL;
    }

    // 文字列によって割り当てられたメモリを解放
    m_status = RpcStringFree(
        &szStringBinding);    // 解放する文字列
    if (m_status)
    {
        m_status = HandleError("Rpc string free", m_status);
        return E_FAIL;
    }

    // 部分的にバインドされたサーバーバインディングハンドルを完全にバインドされたサーバーバインディングハンドルで解決させる
    m_status = RpcEpResolveBinding(m_hBinding, RpcIdl_v1_0_c_ifspec);
    if (m_status)
    {
        m_status = HandleError("Rpc EP resolve binding", m_status);
        return E_FAIL;
    }

    return S_OK;
}

HRESULT RpcManager::OnSend()
{
    RpcTryExcept
    {
        // RPCコンテキストハンドルをオープン
        CONTEXT_HANDLE hContext = Open(m_hBinding, "Hello World!");

        // 送信先RPC関数をコールし送信
        // hBindingバイディングハンドルが明示的に使用される
        Output(hContext);

        // RPCコンテキストハンドルをクローズ
        Close(&hContext);
    }
        RpcExcept(1)
    {
        m_status = HandleError("Remote Procedure Call", RpcExceptionCode());
        return E_FAIL;
    }
    RpcEndExcept

        return S_OK;
}

HRESULT RpcManager::OnDestroy()
{
    // バインディングハンドルリソースを解放しサーバーから切断
    m_status = RpcBindingFree(
        &m_hBinding);   // 明示的なバインディングハンドルを解放
    if (m_status)
    {
        m_status = HandleError("Rpc binding free", m_status);
        return E_FAIL;
    }

    return S_OK;
}