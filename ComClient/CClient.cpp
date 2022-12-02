#include "stdafx.h"
#include "CClient.h"
#include "CSink.h"
#include <atlbase.h>

CClient::CClient() :
	dwAdvise(0),
	pCP(NULL)
{
	m_number1 = 0;
	m_number2 = 0;
}

CClient::~CClient()
{

}

HRESULT CClient::OnInit(UINT num1, UINT num2)
{
	m_number1 = num1;
	m_number2 = num2;
	
	// COM初期化
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr)) return hr;
	
	return S_OK;
}

HRESULT CClient::OnSendToServer() 
{
	HRESULT  hr;

    // COMオブジェクトインスタンス生成
	CComPtr<IAdd> pAdd;
	hr = pAdd.CoCreateInstance(CLSID_Add);
	if (FAILED(hr)) return hr;

	// インターフェースコンテナを使用
	IConnectionPointContainer* pCPC;
    
	// インターフェースが接続可能なオブジェクトをサポートしているかを確認
    hr = pAdd->QueryInterface(IID_IConnectionPointContainer,(void **)&pCPC);
    if (FAILED(hr)) return hr;

    // 接続ポイントのインターフェースを取得
    hr = pCPC->FindConnectionPoint(IID__IAddEvents, &pCP);
	if (FAILED(hr)) return hr;

	// コンテナ解放
	pCPC->Release();
    
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
    pAdd->Add(m_number1, m_number2);

	// サーバーから切断
	pCP->Unadvise(dwAdvise);

	// 接続ポイント解放
	pCP->Release();
	
    return hr;
}