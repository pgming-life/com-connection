#include "stdafx.h"
#include "CServer.h"
#include "SumUp.h"

STDMETHODIMP CSumUp::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISumUp
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid)) return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSumUp::SumUp(long lValue)
{
	// TODO: ここに実装コードを追加

	// 長いプロセスをシミュレート
	Sleep(2000);

	// プロセスを終了してクライアントに通知
	Fire_Event1(lValue);

	return S_OK;
}