#include "stdafx.h"
#include "RpcManager.h"

int main()
{
    unique_ptr<RpcManager> rpc;
    
    // 初期化
    rpc.reset(new RpcManager());
    cout << "RPC start." << endl;
    rpc->OnInit();

    // サーバー終了
    cout << "Listening... [Enter] is stop." << endl;
    cin.get();

    // 解放
    rpc->OnDestroy();

    cout << "Process release..." << endl;
    Sleep(1000);
}