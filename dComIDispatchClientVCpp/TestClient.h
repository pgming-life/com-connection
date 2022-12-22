#include "resource.h"

class CTestClientApp : public CWinApp
{
public:
	CTestClientApp();

	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};