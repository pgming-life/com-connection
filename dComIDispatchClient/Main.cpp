#include "stdafx.h"
#include "CClient.h"

int main()
{
	cout << "▼▼▼▼▼▼  Test Start ▼▼▼▼▼▼" << endl;

	// COM初期化
	if (FAILED(CoInitialize(NULL)))
	{
		cout << "COM初期化に失敗しました。" << endl;
		cout << "終了します..." << endl;
		Sleep(2000);
		return 0;
	}

	// スマートポインタインスタンスであるm_spISumUpは自動変数であり、ReleaseされるのはCoUninitializeを実行した後のmainスコープを出たときであるためアクセス違反が生じる。
	// そのため、CoInitializeとCoUninitializeの間のブロック内にm_spISumUpを管理するクラスインスタンスであるclientがある必要がある。
	{
		CClient client;
		client.OnInit(2, 3);
		client.OnSendToServer();
		client.OnDestroy();
	}
	// デストラクタ呼出し（m_spISumUp解放）

	// COM解放
	CoUninitialize();

	cout << "▲▲▲▲▲▲ Test Finish ▲▲▲▲▲▲" << endl;
	system("PAUSE");
}