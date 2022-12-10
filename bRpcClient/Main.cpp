#include "stdafx.h"
#include "RpcManager.h"

int main()
{
    unique_ptr<RpcManager> rpc;
    rpc.reset(new RpcManager());

    // 初期化
    rpc->OnInit();

    cout << "Can I send \"Hello World!\" ? [Enter]";
    cin.get();

    // 送信
    rpc->OnSend();

    cout << "Process release... [Enter]" << endl;
    cin.get();

    // 解放
    rpc->OnDestroy();
}