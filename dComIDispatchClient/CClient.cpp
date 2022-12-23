#include "stdafx.h"
#include "CClient.h"

CClient::CClient()
{
	m_num1 = 0;
	m_num2 = 0;
}

CClient::~CClient()
{
	
}

HRESULT CClient::OnInit(UINT num1, UINT num2)
{
	m_num1 = num1;
	m_num2 = num2;

	// COM初期化
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr)) return hr;

	// ISumUp を実装するオブジェクトのインスタンスを作成
	m_spISumUp.CreateInstance(__uuidof(SumUp));

	// ISumUpEventHandler オブジェクトをインスタンス化
	m_pISumUpEventHandler = new ISumUpEventHandler(*this, m_spISumUp, &CClient::OnSumUpInvoke);
	
	return S_OK;
}

// OnSumUpInvoke() は、ISumUp を実装する COM オブジェクトからイベントが発生したときに、TEventHandler ベースのクラスオブジェクトによって呼び出される
HRESULT CClient::OnSumUpInvoke(
	ISumUpEventHandler* pEventHandler,
	DISPID dispidMember, 
	REFIID riid,
	LCID lcid, 
	WORD wFlags, 
	DISPPARAMS* pdispparams, 
	VARIANT* pvarResult,
	EXCEPINFO* pexcepinfo, 
	UINT* puArgErr)
{
	if (0x01 == dispidMember)	// Event1 event.
	{
		// 第１パラメータ : [in] int Result
		VARIANT varResult;
		int	Result = 0;
		VariantInit(&varResult);
		VariantClear(&varResult);
		varResult = (pdispparams->rgvarg)[0];
		Result = V_I4(&varResult);

		TCHAR szMessage[256];
		sprintf_s(szMessage, "Sum up result : %d", Result);
		cout << szMessage << endl;
	}

	return S_OK;
}

VOID CClient::OnDestroy()
{
	// プログラムが終了するとき、ISumUp インターフェイスを実装したオブジェクトの接続ポイントから切断するようにイベントハンドラーに指示する
	// また、(削除する代わりに) Release() する必要がある
	if (m_pISumUpEventHandler)
	{
		m_pISumUpEventHandler->ShutdownConnectionPoint();
		m_pISumUpEventHandler->Release();
		m_pISumUpEventHandler = NULL;
	}

	// スマートポイントなので不要
	//CoUninitialize();
}

VOID CClient::OnSendToServer()
{
	// スケルトンコード
	// COMサーバーにパラメータを送信
	cout << "Sending..." << endl;
	m_spISumUp->SumUp(m_num1, m_num2);
}