#include "stdafx.h"
#include "RpcManager.h"

int main()
{
    unique_ptr<RpcManager> rpc;
    rpc.reset(new RpcManager());

    // ‰Šú‰»
    cout << "RPC start." << endl;
    rpc->OnInit();

    cout << "Can I send \"2 and 3\" / \"5 and 6\"? [Enter]";
    cin.get();

    // ‘—M
    cout << "Sending..." << endl;
    INPUT_DATA data;
    data.szStr1 = "Sum Args1«";
    data.args1[0] = 2;
    data.args1[1] = 3;
    data.szStr2 = "Sum Args2«";
    data.args2[0] = 5;
    data.args2[1] = 6;
    rpc->OnSend(&data);

    // ‰ğ•ú
    cout << "RPC release? [Enter]";
    cin.get();
    rpc->OnDestroy();

    cout << "Process release..." << endl;
    Sleep(1000);
}