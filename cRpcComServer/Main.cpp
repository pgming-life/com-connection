#include "RpcServer.h"

int main()
{
    RPC_STATUS status;

    clog << "Calling RpcServerUseProtseqEp" << endl;

    // 受信用のエンドポイントと組み合わせたプロトコルを使用
    // Remote Procedure Call
    status = RpcServerUseProtseqEp(
        reinterpret_cast<unsigned char*>("ncacn_ip_tcp"), // TCP/IPプロトコルを使用
        RPC_C_PROTSEQ_MAX_REQS_DEFAULT,                   // TCP/IPのバックログキューの長さ
        reinterpret_cast<unsigned char*>("1688"),         // 使用するためのTCP/IPポート
        NULL);                                            // セキュリティなし
    if (status)
        return HandleError("RpcServerUseProtseqEp", status);

    clog << "Calling RpcServerRegisterIf" << endl;

    // インターフェースを登録
    status = RpcServerRegisterIf2(
        RpcIdl_v1_0_s_ifspec,                 // 登録するインターフェース
        NULL,                                 // MIDLで生成されたエントリポイントベクトルを使用
        NULL,                                 // MIDLで生成されたエントリポイントベクトルを使用
        RPC_IF_ALLOW_CALLBACKS_WITH_NO_AUTH,  // セキュリティコールバックの使用を強制
        RPC_C_LISTEN_MAX_CALLS_DEFAULT,       // デフォルトの同時呼び出し数を使用
        (unsigned)-1,                         // 着信データブロックの最大サイズは無限
        SecurityCallback);                    // 単純なセキュリティコールバック
    if (status)
        return HandleError("RpcServerRegisterIf", status);

    clog << "Creating listen thread" << endl;
    const HANDLE hThread = CreateThread(
        NULL,
        0,
        RpcServerListenThreadProc,
        NULL,
        0,
        NULL);
    if (!hThread)
        return HandleError("CreateThread", GetLastError());

    cout << "Press enter to stop listening" << endl;
    cin.get();

    clog << "Calling RpcMgmtStopServerListening" << endl;
    status = RpcMgmtStopServerListening(NULL);
    if (status)
        return HandleError("RpcMgmtStopServerListening", status);

    clog << "Waiting for listen thread to finish";
    while (WaitForSingleObject(hThread, 1000) == WAIT_TIMEOUT)
        clog << '.';
    clog << endl << "Listen thread finished" << std::endl;

    DWORD dwExitCodeThread = 0;
    GetExitCodeThread(hThread, &dwExitCodeThread);
    CloseHandle(hThread);
    if (dwExitCodeThread)
        return HandleError("RpcServerListen", dwExitCodeThread);

    cout << "Press enter to exit" << endl;
    cin.get();
}