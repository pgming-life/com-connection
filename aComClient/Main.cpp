#include "stdafx.h"
#include "CClient.h"

int main()
{
    cout << "▼▼▼▼▼▼  Test Start ▼▼▼▼▼▼" << endl;

    CClient client;
    if (FAILED(client.OnInit(2, 3)))
    {
        cout << "COM初期化に失敗しました。" << endl;
        cout << "終了します..." << endl;
        Sleep(2000);
        return 0;
    }
    if (FAILED(client.OnSendToServer()))
    {
        cout << "ターゲットCOMサーバーが存在しません。" << endl;
        cout << "終了します..." << endl;
        Sleep(2000);
        return 0;
    }

    cout << "▲▲▲▲▲▲ Test Finish ▲▲▲▲▲▲" << endl;
    system("PAUSE");
}