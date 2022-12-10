#include "stdafx.h"
#include "RpcManager.h"

int main()
{
    unique_ptr<RpcManager> rpc;
    rpc.reset(new RpcManager());

    // ������
    cout << "RPC start." << endl;
    rpc->OnInit();

    cout << "Can I send \"Hello World!\"? [Enter]";
    cin.get();

    // ���M
    rpc->OnSend();

    // ���
    cout << "RPC release? [Enter]";
    cin.get();
    rpc->OnDestroy();

    cout << "Process release..." << endl;
    Sleep(1000);
}