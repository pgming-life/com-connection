#include "ConnectionCOM.h"
#import "ConnectionCOM.tlb" named_guids raw_interfaces_only 

class CSink : public _IAddEvents
{
private:
    DWORD m_dwRefCount;
public:
	CSink();
	virtual ~CSink();
    STDMETHODIMP ExecutionOver(int ret)
    {
        cout << "ExecutionOver: " << ret << endl;
	    return S_OK;
    };

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** ppvObject)
    {
        if (iid == IID__IAddEvents)
        {
            m_dwRefCount++;
            *ppvObject = (void*)this;
            return S_OK;
        }

        if (iid == IID_IUnknown)
        {
            m_dwRefCount++;
            *ppvObject = (void*)this;
            return S_OK;
        }

        return E_NOINTERFACE;
    }

	ULONG STDMETHODCALLTYPE AddRef()
    {
        m_dwRefCount++;
        return m_dwRefCount;
    }
    
	ULONG STDMETHODCALLTYPE Release()
    {
        ULONG l;
        l  = m_dwRefCount--;

        if (0 == m_dwRefCount)
        {
            delete this;
        }
        
        return l;
    }
};