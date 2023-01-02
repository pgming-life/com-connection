#include "stdafx.h"
#include "RpcManager.h"

int main()
{
    unique_ptr<RpcManager> rpc;
    
    // ú»
    rpc.reset(new RpcManager());
    cout << "RPC start." << endl;
    rpc->OnInit();

    // RCVI¹
    cout << "Receiving... [Enter] is stop." << endl;
    cin.get();

    // ðú
    rpc->OnDestroy();

    cout << "Process release..." << endl;
    Sleep(1000);
}