#include "stdafx.h"
#include "CServer.h"
#include "SumUp.h"

STDMETHODIMP CSumUp::SumUp(int a, int b)
{
	// TODO: ここに実装コードを追加

	// 長いプロセスをシミュレート
	Sleep(2000);
	
	// プロセスを終了してクライアントに通知
	Fire_ExecutionOver(a+b); 

	return S_OK;
}
