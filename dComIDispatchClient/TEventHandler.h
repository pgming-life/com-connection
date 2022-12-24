#pragma once

namespace TEventHandlerNamespace
{
	// 一般的なイベントハンドラーテンプレートクラス (ATL 以外のクライアントに特に役立つが、これに限定されない)
	template <
		class event_handler_class,
		typename device_interface,
		typename device_event_interface>
	class TEventHandler : IDispatch
	{
		friend class class_event_handler;
		
		typedef HRESULT (event_handler_class::*parent_on_invoke)(
			TEventHandler<event_handler_class, device_interface, device_event_interface>* pthis,
			DISPID dispidMember, 
			REFIID riid,
			LCID lcid,
			WORD wFlags,
			DISPPARAMS* pdispparams,
			VARIANT* pvarResult,
			EXCEPINFO* pexcepinfo,
			UINT* puArgErr);

	public:
		TEventHandler(
			event_handler_class& parent,
			device_interface* pdevice_interface,	// Non-ref counted.
			parent_on_invoke parent_on_invoke_function) :
			m_cRef(1),
			m_parent(parent),
			m_parent_on_invoke(parent_on_invoke_function),
			m_pIConnectionPoint(0),
			m_dwEventCookie(0)
		{
			SetupConnectionPoint(pdevice_interface);
		}
		
		~TEventHandler()
		{
			// 以前に切断されていたはずなので、ここで ShutdownConnectionPoint() を呼び出す
			ShutdownConnectionPoint();
		}
		
		void ShutdownConnectionPoint()
		{
			if (m_pIConnectionPoint)
			{
				m_pIConnectionPoint->Unadvise(m_dwEventCookie);
				m_dwEventCookie = 0;
				SAFE_RELEASE(m_pIConnectionPoint);
				m_pIConnectionPoint = NULL;
			}
		}
	
		STDMETHOD_(ULONG, AddRef)()
		{
			InterlockedIncrement(&m_cRef);
			return m_cRef;
		}
		   
		STDMETHOD_(ULONG, Release)()
		{
			InterlockedDecrement(&m_cRef);
		
			if (m_cRef == 0)
			{
				delete this;
				return 0;
			}
			
			return m_cRef;
		}
		   
		STDMETHOD(QueryInterface)(REFIID riid, void** ppvObject)
		{
			if (riid == IID_IUnknown)
			{
				*ppvObject = (IUnknown*)this;
				AddRef();
				return S_OK;
			}
			
			if ((riid == IID_IDispatch) || (riid == __uuidof(device_event_interface)))
			{
				*ppvObject = (IDispatch*)this;
				AddRef();
				return S_OK;
			}
			
			return E_NOINTERFACE;
		}
		   
		STDMETHOD(GetTypeInfoCount)(UINT* pctinfo)
		{
			return E_NOTIMPL;
		}
		   
		STDMETHOD(GetTypeInfo)(UINT itinfo, LCID lcid, ITypeInfo** pptinfo)
		{
			return E_NOTIMPL;
		}
		   
		STDMETHOD(GetIDsOfNames)(
			REFIID riid,
			LPOLESTR* rgszNames,
			UINT cNames,
			LCID lcid,
			DISPID* rgdispid)
		{
			return E_NOTIMPL;
		}
		   
		STDMETHOD(Invoke)(
			DISPID dispidMember,
			REFIID riid,
			LCID lcid,
			WORD wFlags,
			DISPPARAMS* pdispparams,
			VARIANT* pvarResult,
			EXCEPINFO* pexcepinfo,
			UINT* puArgErr)
		{
			return (m_parent.*m_parent_on_invoke)(
				this,
				dispidMember,
				riid,
				lcid,
				wFlags,
				pdispparams,
				pvarResult,
				pexcepinfo,
				puArgErr);
		}
	
	protected:
		LONG m_cRef;
	
		// このオブジェクトの所有者に関するもの
		// 非参照カウント。これは、循環参照を防ぐため。
		event_handler_class& m_parent;
	
		// 接続ポイントに関するもの
		IConnectionPoint* m_pIConnectionPoint;	// 参照カウント
		DWORD m_dwEventCookie;
		parent_on_invoke m_parent_on_invoke;
	
		void SetupConnectionPoint(device_interface* pdevice_interface)
		{
			IConnectionPointContainer* pIConnectionPointContainerTemp = NULL;
			IUnknown* pIUnknown = NULL;
	
			// このオブジェクト自体の IUnknown ポインタを QI する。
			// このポインタは、後で device_interface オブジェクトの接続ポイントに接続するために使用される。
			this->QueryInterface(IID_IUnknown, (void**)&pIUnknown);
	
			if (pIUnknown)
			{
				try
				{
					// 接続ポイントの pdevice_interface を QI します。
					pdevice_interface->QueryInterface(IID_IConnectionPointContainer, (void**)&pIConnectionPointContainerTemp);
				}
				catch (...)
				{
					cout << "ターゲットCOMサーバーが存在しません。" << endl;
					cout << "終了します..." << endl;
					Sleep(2000);
					exit(0);
				}
				
				if (pIConnectionPointContainerTemp)
				{
					pIConnectionPointContainerTemp->FindConnectionPoint(__uuidof(device_event_interface), &m_pIConnectionPoint);
					SAFE_RELEASE(pIConnectionPointContainerTemp);
					pIConnectionPointContainerTemp = NULL;
				}
				
				if (m_pIConnectionPoint)
				{
					m_pIConnectionPoint->Advise(pIUnknown, &m_dwEventCookie);
				}
				
				SAFE_RELEASE(pIUnknown);
				pIUnknown = NULL;
			}
		}
	};
};