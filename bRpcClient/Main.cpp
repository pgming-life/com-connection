#include "stdafx.h"
#include "RpcManager.h"

int main()
{
    unique_ptr<RpcManager> rpc;
    rpc.reset(new RpcManager());

    // ‰Šú‰»
    rpc->OnInit();

    cout << "Can I send \"Hello World!\" ? [Enter]";
    cin.get();

    // ‘—M
    rpc->OnSend();

    cout << "Process release... [Enter]" << endl;
    cin.get();

    // ‰ð•ú
    rpc->OnDestroy();
}