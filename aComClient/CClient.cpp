#include "stdafx.h"
#include "CClient.h"
#include "CSink.h"
#include <atlbase.h>

CClient::CClient() :
	dwAdvise(0),
	pCP(NULL)
{
	m_num1 = 0;
	m_num2 = 0;
}

CClient::~CClient()
{
	// COM解放
	CoUninitialize();
}

HRESULT CClient::OnInit(UINT num1, UINT num2)
{
	m_num1 = num1;
	m_num2 = num2;
	
	// COM初期化
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr)) return hr;
	
	return S_OK;
}

HRESULT CClient::OnSendToServer() 
{
	HRESULT  hr;

    // COMオブジェクトインスタンス生成
	CComPtr<ISumUp> pAdd;
	hr = pAdd.CoCreateInstance(CLSID_SumUp);
	if (FAILED(hr)) return hr;

	// インターフェースコンテナを使用
	IConnectionPointContainer* pCPC;
    
	// インターフェースが接続可能なオブジェクトをサポートしているかを確認
    hr = pAdd->QueryInterface(IID_IConnectionPointContainer, (void**)&pCPC);
    if (FAILED(hr)) return hr;

    // 接続ポイントのインターフェースを取得
    hr = pCPC->FindConnectionPoint(IID__ISumUpEvents, &pCP);
	if (FAILED(hr)) return hr;

	// コンテナ解放
	SAFE_RELEASE(pCPC);
    
	// ハンドラ
	IUnknown* pSinkUnk;
	
	// 通知オブジェクトを作成
	CSink* pSink;
    pSink = new CSink;
    if (NULL == pSink) return E_FAIL;

    // IUnknownのポインタを取得
	hr = pSink->QueryInterface(IID_IUnknown, (void**)&pSinkUnk);

	// _IAddEventsインターフェース(pCP)を介してCOMに送信
	// 返却値がFAILの場合は IConnectionPoint:UnAdvise が呼び出され、接続が切断される
	hr = pCP->Advise(pSinkUnk, &dwAdvise); 
	
	// COMサーバーにパラメータを送信
	cout << "Sending..." << endl;
    pAdd->SumUp(m_num1, m_num2);

	// サーバーから切断
	pCP->Unadvise(dwAdvise);

	// 接続ポイント解放
	SAFE_RELEASE(pCP);
	
    return hr;
}