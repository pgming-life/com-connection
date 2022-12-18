#include "stdafx.h"
#include "interface/CServer.h"

class CClient
{
public:
	CClient();
	~CClient();

	virtual HRESULT OnInit();
	HRESULT OnSendToServer(UINT num1, UINT num2);

// Implementation
protected:
	DWORD dwAdvise;
	IConnectionPoint* pCP;

private:
	// サーバーへ渡すデータ
	int m_num1;
	int m_num2;
};