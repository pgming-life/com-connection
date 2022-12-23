#pragma once

#include "resource.h"

class CClientDlg;

// TEventHandler テンプレートを使用してイベント処理クラスを宣言
typedef TEventHandler<CClientDlg, ISumUp, _ISumUpEvents> ISumUpEventHandler;

class CClientDlg : public CDialog
{
public:
	CClientDlg(CWnd* pParent = NULL);
	enum { IDD = IDD_CLIENT_DIALOG };

	// ClassWizard によって生成された仮想関数のオーバーライド
protected:
	HICON m_hIcon;

	// スマートポインタのインスタンスを宣言
	ISumUpPtr m_spISumUp;

	// ISumUp オブジェクトの _ISumUpEvents イベントからイベントを受け取るように特別に調整された TEventHandler クラスへのポインタを宣言
	ISumUpEventHandler* m_pISumUpEventHandler;

	// 生成されたメッセージ マップ関数
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnButtonCallFunction();
	DECLARE_MESSAGE_MAP()

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