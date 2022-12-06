#include "stdafx.h"

class CClient;
typedef TEventHandler<CClient, IEventFiringObject, _IEventFiringObjectEvents> IEventFiringObjectEventHandler;

class CClient
{
public:
	CClient();
	~CClient();

	// ***** Declare an instance of a IEventFiringObject smart pointer. *****
	IEventFiringObjectPtr			m_spIEventFiringObject;

	// ***** Declare a pointer to a TEventHandler class which is specially tailored *****
	// ***** to receiving events from the _IEventFiringObjectEvents events of an *****
	// ***** IEventFiringObject object. *****
	IEventFiringObjectEventHandler* m_pIEventFiringObjectEventHandler;

	BOOL OnInit();

	HRESULT OnEventFiringObjectInvoke
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
	);

	VOID Execute();
};