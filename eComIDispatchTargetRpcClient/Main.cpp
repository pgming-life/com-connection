#include "stdafx.h"
#include "RpcManager.h"

int main()
{
    unique_ptr<RpcManager> rpc;
    rpc.reset(new RpcManager());

    // ‰Šú‰»
    cout << "RPC start." << endl;
    rpc->OnInitServer();
    rpc->OnInitClient();

    cout << "Can I send it 5 times? [Enter]";
    cin.get();

    // 5‰ñ‘—M
    for (UINT i = 1; i <= 5; i++)
    {
        cout << "-------------------------" << endl;
        cout << ">>> input : " << i << endl;
        cout << ">>> output : " << i << " + " << i << endl;
        cout << "Sending..." << endl;
        INPUT_DATA_SND data;
        data.args1 = i;
        data.args2 = i;
        rpc->OnSend(&data);
    }

    // ‰ğ•ú
    cout << "RPC release? [Enter]";
    cin.get();
    rpc->OnDestroyClient();
    rpc->OnDestroyServer();

    cout << "Process release..." << endl;
    Sleep(1000);
}