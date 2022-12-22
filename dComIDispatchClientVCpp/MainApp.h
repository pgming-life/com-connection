#pragma once

class MainApp : public CWinApp
{
public:
	MainApp();

	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};