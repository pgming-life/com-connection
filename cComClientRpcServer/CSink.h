#include "interface/CServer.h"
#import "interface/ComServer.tlb" named_guids raw_interfaces_only 

class CSink : public _ISumUpEvents
{
public:
	CSink();
	virtual ~CSink();

    STDMETHODIMP ExecutionOver(int ret)
    {
        cout << "Sum up result: " << ret << endl;
	    return S_OK;
    };

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** ppvObject)
    {
        if (iid == IID__ISumUpEvents)
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

private:
    DWORD m_dwRefCount;
};