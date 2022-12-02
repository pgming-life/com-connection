#include "stdafx.h"
#include "ConnectionCOM.h"

class CClient
{
public:
	CClient();
	~CClient();

	virtual HRESULT OnInit(UINT num1, UINT num2);
	HRESULT OnSendToServer();

// Implementation
protected:
	DWORD dwAdvise;
	IConnectionPoint* pCP;

private:
	// ìnÇ∑ÉfÅ[É^
	int m_number1;
	int m_number2;
};