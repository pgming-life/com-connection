#include "stdafx.h"
#include "RpcManager.h"

int main()
{
    unique_ptr<RpcManager> rpc;
    rpc.reset(new RpcManager());

    // ‰Šú‰»
    cout << "RPC start." << endl;
    rpc->OnInit();

    cout << "Can I send \"2 and 3\"? [Enter]";
    cin.get();

    // ‘—M
    INPUT_DATA_SND data;
    data.args1 = 2;
    data.args2 = 3;
    rpc->OnSend(&data);

    // ‰ğ•ú
    cout << "RPC release? [Enter]";
    cin.get();
    rpc->OnDestroy();

    cout << "Process release..." << endl;
    Sleep(1000);
}