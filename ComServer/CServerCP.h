#pragma once

template <class T>
class CProxy_ISumUpEvents : public IConnectionPointImpl<T, &IID__ISumUpEvents, CComDynamicUnkArray>
{
	// 警告: このクラスはウィザードによって再作成される可能性アリ
public:
	HRESULT Fire_ExecutionOver(INT Result)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			_ISumUpEvents* p_ISumUpEvents = reinterpret_cast<_ISumUpEvents*>(sp.p);
			if (p_ISumUpEvents != NULL)
				ret = p_ISumUpEvents->ExecutionOver(Result);
		}	return ret;
	}
};