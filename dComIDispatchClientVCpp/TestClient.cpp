#include "stdafx.h"
#include "TestClient.h"
#include "TestClientDlg.h"

BEGIN_MESSAGE_MAP(CTestClientApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CTestClientApp::CTestClientApp()
{
	// TODO: ここに構築コードを追加し、すべての重要な初期化を InitInstance に配置する
}

// 唯一無二のオブジェクト
CTestClientApp theApp;

BOOL CTestClientApp::InitInstance()
{
	AfxEnableControlContainer();

	// プログラムの最初に呼び出されることを確認
	CoInitialize(NULL);

	CTestClientDlg dlg;
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

int CTestClientApp::ExitInstance() 
{
	// TODO: ここに特殊なコードを追加するか、基本クラスを呼び出す

	// プログラムの最後で呼び出されることを確認
	CoUninitialize();
	
	return CWinApp::ExitInstance();
}