#pragma once

#include <windows.h>

namespace TEventHandlerNamespace
{
	// ��ʓI�ȃC�x���g�n���h���[�e���v���[�g�N���X (ATL �ȊO�̃N���C�A���g�ɓ��ɖ𗧂��A����Ɍ��肳��Ȃ�)
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
			// �ȑO�ɐؒf����Ă����͂��Ȃ̂ŁA������ ShutdownConnectionPoint() ���Ăяo��
			ShutdownConnectionPoint();
		}
		
		void ShutdownConnectionPoint()
		{
			if (m_pIConnectionPoint)
			{
				m_pIConnectionPoint->Unadvise(m_dwEventCookie);
				m_dwEventCookie = 0;
				m_pIConnectionPoint->Release();
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
	
		// ���̃I�u�W�F�N�g�̏��L�҂Ɋւ������
		// ��Q�ƃJ�E���g�B����́A�z�Q�Ƃ�h�����߁B
		event_handler_class& m_parent;
	
		// �ڑ��|�C���g�Ɋւ������
		IConnectionPoint* m_pIConnectionPoint;	// �Q�ƃJ�E���g
		DWORD m_dwEventCookie;
		parent_on_invoke m_parent_on_invoke;
	
		void SetupConnectionPoint(device_interface* pdevice_interface)
		{
			IConnectionPointContainer* pIConnectionPointContainerTemp = NULL;
			IUnknown* pIUnknown = NULL;
	
			// ���̃I�u�W�F�N�g���̂� IUnknown �|�C���^�� QI ����B
			// ���̃|�C���^�́A��� device_interface �I�u�W�F�N�g�̐ڑ��|�C���g�ɐڑ����邽�߂Ɏg�p�����B
			this->QueryInterface(IID_IUnknown, (void**)&pIUnknown);
	
			if (pIUnknown)
			{
				// �ڑ��|�C���g�� pdevice_interface �� QI ���܂��B
				pdevice_interface->QueryInterface(IID_IConnectionPointContainer, (void**)&pIConnectionPointContainerTemp);
				
				if (pIConnectionPointContainerTemp)
				{
					pIConnectionPointContainerTemp->FindConnectionPoint(__uuidof(device_event_interface), &m_pIConnectionPoint);
					pIConnectionPointContainerTemp->Release();
					pIConnectionPointContainerTemp = NULL;
				}
				
				if (m_pIConnectionPoint)
				{
					m_pIConnectionPoint->Advise(pIUnknown, &m_dwEventCookie);
				}
				
				pIUnknown->Release();
				pIUnknown = NULL;
			}
		}
	};
};