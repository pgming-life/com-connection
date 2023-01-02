#include "stdafx.h"
#include "RpcManager.h"

int main()
{
    unique_ptr<RpcManager> rpc;
    
    // ������
    rpc.reset(new RpcManager());
    cout << "RPC start." << endl;
    rpc->OnInit();

    // RCV�I��
    cout << "Receiving... [Enter] is stop." << endl;
    cin.get();

    // ���
    rpc->OnDestroy();

    cout << "Process release..." << endl;
    Sleep(1000);
}