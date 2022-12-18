#include "stdafx.h"
#include "CClient.h"

int main()
{
    cout << "▼▼▼▼▼▼  Test Start ▼▼▼▼▼▼" << endl;

    CClient client;
    client.OnInit();
    client.Execute();

    cout << "▲▲▲▲▲▲ Test Finish ▲▲▲▲▲▲" << endl;
    system("PAUSE");
}