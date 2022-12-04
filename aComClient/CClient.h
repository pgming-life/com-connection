#include "stdafx.h"
#include "CServer.h"

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
	// サーバーへ渡すデータ
	int m_num1;
	int m_num2;
};