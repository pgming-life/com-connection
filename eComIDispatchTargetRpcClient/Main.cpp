#include "stdafx.h"
#include "RpcManager.h"

int main()
{
    unique_ptr<RpcManager> rpc;
    rpc.reset(new RpcManager());

    // 初期化
    cout << "RPC start." << endl;
    rpc->OnInit();

    cout << "Can I send \"2 and 3\"? [Enter]";
    cin.get();

    // 送信
    INPUT_DATA_SND data;
    data.args1 = 2;
    data.args2 = 3;
    rpc->OnSend(&data);

    // 解放
    cout << "RPC release? [Enter]";
    cin.get();
    rpc->OnDestroy();

    cout << "Process release..." << endl;
    Sleep(1000);
}