#include "CServer.h"

class CClient
{
public:
	CClient();
	~CClient();

	HRESULT OnInit(UINT num1, UINT num2);
	HRESULT OnSendToServer();

private:
	DWORD dwAdvise;
	IConnectionPoint* pCP;

	// �T�[�o�[�֓n���f�[�^
	int m_num1;
	int m_num2;
};