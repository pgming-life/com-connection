#include "stdafx.h"
#include "MainApp.h"
#include "CClientDlg.h"

MainApp::MainApp()
{
	// TODO: �����ɍ\�z�R�[�h��ǉ����A���ׂĂ̏d�v�ȏ������� InitInstance �ɔz�u����
}

// �B�ꖳ��̃I�u�W�F�N�g
MainApp theApp;

BOOL MainApp::InitInstance()
{
	AfxEnableControlContainer();

	// �v���O�����̍ŏ��ɌĂяo����邱�Ƃ��m�F
	CoInitialize(NULL);

	CClientDlg dlg;
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

int MainApp::ExitInstance() 
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A��{�N���X���Ăяo��

	// �v���O�����̍Ō�ŌĂяo����邱�Ƃ��m�F
	CoUninitialize();
	
	return CWinApp::ExitInstance();
}