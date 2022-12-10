#include "stdafx.h"
#include "RpcManager.h"

int main()
{
    unique_ptr<RpcManager> rpc;
    rpc.reset(new RpcManager());

    // ������
    rpc->OnInit();

    cout << "Can I send \"Hello World!\" ? [Enter]";
    cin.get();

    // ���M
    rpc->OnSend();

    cout << "Process release... [Enter]" << endl;
    cin.get();

    // ���
    rpc->OnDestroy();
}