#include "stdafx.h"
#include "MainApp.h"
#include "CClientDlg.h"

MainApp::MainApp()
{
	// TODO: ここに構築コードを追加し、すべての重要な初期化を InitInstance に配置する
}

// 唯一無二のオブジェクト
MainApp theApp;

BOOL MainApp::InitInstance()
{
	AfxEnableControlContainer();

	// プログラムの最初に呼び出されることを確認
	CoInitialize(NULL);

	CClientDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (IDOK == nResponse)
	{
		// TODO: OK でダイアログが閉じられたときに処理するコードをここに配置
	}
	else if (IDCANCEL == nResponse)
	{
		// TODO: ダイアログがキャンセルで閉じられたときに処理するコードをここに配置
	}

	// ダイアログが閉じられたので、アプリケーションのメッセージ ポンプを開始するのではなく、アプリケーションを終了するように FALSE を返す
	return FALSE;
}

int MainApp::ExitInstance() 
{
	// TODO: ここに特殊なコードを追加するか、基本クラスを呼び出す

	// プログラムの最後で呼び出されることを確認
	CoUninitialize();
	
	return CWinApp::ExitInstance();
}