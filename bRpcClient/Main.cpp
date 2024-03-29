#include "stdafx.h"
#include "RpcManager.h"

int main()
{
    unique_ptr<RpcManager> rpc;
    rpc.reset(new RpcManager());

    // 初期化
    cout << "RPC start." << endl;
    rpc->OnInit();

    cout << "Can I send \"Hello World!\"? [Enter]";
    cin.get();

    // 送信
    cout << "Sending..." << endl;
    rpc->OnSend();

    // 解放
    cout << "RPC release? [Enter]";
    cin.get();
    rpc->OnDestroy();

    cout << "Process release..." << endl;
    Sleep(1000);
}