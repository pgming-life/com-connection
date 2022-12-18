#include "stdafx.h"
#include "CClient.h"

CClient::CClient()
{

}

CClient::~CClient()
{
	// TODO: Add your message handler code here

	// ***** When the program is terminating, make sure that we instruct our *****
	// ***** Event Handler to disconnect from the connection point of the *****
	// ***** object which implemented the IEventFiringObject interface. *****
	// ***** We also needs to Release() it (instead of deleting it). *****
	if (m_pIEventFiringObjectEventHandler)
	{
		m_pIEventFiringObjectEventHandler->ShutdownConnectionPoint();
		SAFE_RELEASE(m_pIEventFiringObjectEventHandler);
		m_pIEventFiringObjectEventHandler = NULL;
	}

	CoUninitialize();
}

BOOL CClient::OnInit()
{
	// COM‰Šú‰»
	BOOL bResult = CoInitialize(NULL);
	if (!bResult) return FALSE;

	// ***** Create an instance of an object which implements IEventFiringObject. *****
	m_spIEventFiringObject.CreateInstance(__uuidof(EventFiringObject));

	// ***** Instantiate an IEventFiringObjectEventHandler object. *****
	m_pIEventFiringObjectEventHandler = new IEventFiringObjectEventHandler(*this, m_spIEventFiringObject, &CClient::OnEventFiringObjectInvoke);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// ***** OnEventFiringObjectInvoke() is inoked by the TEventHandler based class object *****
// ***** when an event is fired from the COM object that implements IEventFiringObject. *****
HRESULT CClient::OnEventFiringObjectInvoke
(
	IEventFiringObjectEventHandler* pEventHandler,
	DISPID dispidMember,
	REFIID riid,
	LCID lcid,
	WORD wFlags,
	DISPPARAMS* pdispparams,
	VARIANT* pvarResult,
	EXCEPINFO* pexcepinfo,
	UINT* puArgErr
)
{
	if (dispidMember == 0x01)  // Event1 event.
	{
		// 1st param : [in] long lValue.
		VARIANT	varlValue;
		long	lValue = 0;

		VariantInit(&varlValue);
		VariantClear(&varlValue);

		varlValue = (pdispparams->rgvarg)[0];

		lValue = V_I4(&varlValue);

		cout << "Event 1 is fired with value : " << lValue << endl;
	}

	return S_OK;
}

VOID CClient::Execute()
{
	// TODO: Add your control notification handler code here
	// ***** Call the IEventFiringObject.TestFunction(). *****
	// ***** This will cause the object which implements *****
	// ***** IEventFiringObject to fire Event1. *****
	m_spIEventFiringObject->TestFunction(456);
}