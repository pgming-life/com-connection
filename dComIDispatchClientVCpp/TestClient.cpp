#include "stdafx.h"
#include "TestClient.h"
#include "TestClientDlg.h"

BEGIN_MESSAGE_MAP(CTestClientApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CTestClientApp::CTestClientApp()
{
	// TODO: �����ɍ\�z�R�[�h��ǉ����A���ׂĂ̏d�v�ȏ������� InitInstance �ɔz�u����
}

// �B�ꖳ��̃I�u�W�F�N�g
CTestClientApp theApp;

BOOL CTestClientApp::InitInstance()
{
	AfxEnableControlContainer();

	// �v���O�����̍ŏ��ɌĂяo����邱�Ƃ��m�F
	CoInitialize(NULL);

	CTestClientDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (IDOK == nResponse)
	{
		// TODO: OK �Ń_�C�A���O������ꂽ�Ƃ��ɏ�������R�[�h�������ɔz�u
	}
	else if (IDCANCEL == nResponse)
	{
		// TODO: �_�C�A���O���L�����Z���ŕ���ꂽ�Ƃ��ɏ�������R�[�h�������ɔz�u
	}

	// �_�C�A���O������ꂽ�̂ŁA�A�v���P�[�V�����̃��b�Z�[�W �|���v���J�n����̂ł͂Ȃ��A�A�v���P�[�V�������I������悤�� FALSE ��Ԃ�
	return FALSE;
}

int CTestClientApp::ExitInstance() 
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A��{�N���X���Ăяo��

	// �v���O�����̍Ō�ŌĂяo����邱�Ƃ��m�F
	CoUninitialize();
	
	return CWinApp::ExitInstance();
}