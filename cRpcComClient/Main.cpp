#include "RpcClient.h"

int main()
{
    RPC_STATUS status;
    unsigned char* szStringBinding = NULL;

    clog << "Calling RpcStringBindingCompose" << endl;

    // 文字列バインディングハンドルを作成
    // この関数は単なるprintfで、ここでは接続しない
    status = RpcStringBindingCompose(
        NULL,                                             // バインド先のUUID
        reinterpret_cast<unsigned char*>("ncacn_ip_tcp"), // TCP/IPプロトコルを使用
        reinterpret_cast<unsigned char*>("localhost"),    // 使用するTCP/IPネットワークアドレス
        reinterpret_cast<unsigned char*>("1688"),         // 使用するためのTCP/IPポート
        NULL,                                             // 使用するプロトコル依存のネットワークオプション
        &szStringBinding);                                // 文字列バインディングの出力
    if (status)
        return HandleError("RpcStringBindingCompose", status);

    handle_t hBinding = NULL;

    clog << "Calling RpcBindingFromStringBinding" << endl;

    // 文字列バインディングハンドルの形式を検証し、バインディングハンドルに変換
    // ここでも接続は行われない
    status = RpcBindingFromStringBinding(
        szStringBinding,  // 検証する文字列バインディング
        &hBinding);       // 結果を明示的なバインディングハンドルに入れる
    if (status)
        return HandleError("RpcBindingFromStringBinding", status);

    clog << "Calling RpcStringFree" << endl;

    // 文字列によって割り当てられたメモリを解放
    status = RpcStringFree(
        &szStringBinding);    // 解放する文字列
    if (status)
        return HandleError("RpcStringFree", status);

    clog << "Calling RpcEpResolveBinding" << endl;

    // 部分的にバインドされたサーバーバインディングハンドルを完全にバインドされたサーバーバインディングハンドルで解決させる
    status = RpcEpResolveBinding(hBinding, RpcIdl_v1_0_c_ifspec);
    if (status)
        return HandleError("RpcEpResolveBinding", status);

    RpcTryExcept
    {
        clog << "Calling Open" << endl;

        CONTEXT_HANDLE hContext = Open(hBinding, "Hello Context World!");

        cout << "Press enter to call Output" << endl;
        cin.get();

        clog << "Calling Output" << endl;

        // RPC関数をコール
        // hBindingバイディングハンドルが明示的に使用される
        Output(hContext);

        cout << "Press enter to call Close" << endl;
        cin.get();

        clog << "Calling Close" << endl;

        // コンテキストハンドルをクローズ
        Close(&hContext);
    }
        RpcExcept(1)
    {
        HandleError("Remote Procedure Call", RpcExceptionCode());
    }
    RpcEndExcept

    clog << "Calling RpcBindingFree" << endl;

    // バインディングハンドルリソースを解放しサーバーから切断
    status = RpcBindingFree(
        &hBinding);   // 明示的なバインディングハンドルを解放
    if (status)
        return HandleError("RpcBindingFree", status);

    cout << "Press enter to exit" << endl;
    cin.get();
}