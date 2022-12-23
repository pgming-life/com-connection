#include "stdafx.h"
#include "CClient.h"

int main()
{
	cout << "¥¥¥¥¥¥  Test Start ¥¥¥¥¥¥" << endl;

	CClient client;
	client.OnInit(2, 3);
	client.OnSendToServer();
	client.OnDestroy();

	cout << "££££££ Test Finish ££££££" << endl;
	system("PAUSE");
}