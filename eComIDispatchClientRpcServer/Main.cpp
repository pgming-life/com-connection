#include "stdafx.h"
#include "Singleton.h"
#include "RpcManager.h"

static RpcManager& g_rpc = Singleton<RpcManager>::GetInstance();

int main()
{
    // ‰Šú‰»
    cout << "RPC start." << endl;
    g_rpc.OnInitServer();
    g_rpc.OnInitClient();

    // RCVI—¹
    cout << "Receiving... [Enter] is stop." << endl;
    cin.get();

    // ‰ğ•ú
    g_rpc.OnDestroyClient();
    g_rpc.OnDestroyServer();
    SingletonFinalizer::Finalize();

    cout << "Process release..." << endl;
    Sleep(1000);
}