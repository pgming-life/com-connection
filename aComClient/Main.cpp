﻿#include "stdafx.h"
#include "CClient.h"

int main()
{
    cout << "▼▼▼▼▼▼  Test Start ▼▼▼▼▼▼" << endl;

    CClient client;

    client.OnInit(2, 3);
    if (FAILED(client.OnSendToServer()))
    {
        cout << "Failure..." << endl;
    }

    cout << "▲▲▲▲▲▲ Test Finish ▲▲▲▲▲▲" << endl;
    system("PAUSE");
}