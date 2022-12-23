#pragma once

class CClient;

// TEventHandler テンプレートを使用してイベント処理クラスを宣言
typedef TEventHandler<CClient, ISumUp, _ISumUpEvents> ISumUpEventHandler;

class CClient
{
public:
	CClient();
	~CClient();

	HRESULT OnInit(UINT num1, UINT num2);
	VOID OnDestroy();
	VOID OnSendToServer();

private:
	// サーバーへ渡すデータ
	int m_num1;
	int m_num2;

	// スマートポインタのインスタンスを宣言
	ISumUpPtr m_spISumUp;

	// ISumUp オブジェクトの _ISumUpEvents イベントからイベントを受け取るように特別に調整された TEventHandler クラスへのポインタを宣言
	ISumUpEventHandler* m_pISumUpEventHandler;

	HRESULT OnSumUpInvoke(
	  ISumUpEventHandler* pEventHandler,
	  DISPID dispidMember, 
	  REFIID riid,
	  LCID lcid, 
	  WORD wFlags, 
	  DISPPARAMS* pdispparams, 
	  VARIANT* pvarResult,
	  EXCEPINFO* pexcepinfo, 
	  UINT* puArgErr);
};