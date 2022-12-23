#include "stdafx.h"
#include "CClient.h"

CClient::CClient()
{
	m_num1 = 0;
	m_num2 = 0;
}

CClient::~CClient()
{
	
}

HRESULT CClient::OnInit(UINT num1, UINT num2)
{
	m_num1 = num1;
	m_num2 = num2;

	// COM������
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr)) return hr;

	// ISumUp ����������I�u�W�F�N�g�̃C���X�^���X���쐬
	m_spISumUp.CreateInstance(__uuidof(SumUp));

	// ISumUpEventHandler �I�u�W�F�N�g���C���X�^���X��
	m_pISumUpEventHandler = new ISumUpEventHandler(*this, m_spISumUp, &CClient::OnSumUpInvoke);
	
	return S_OK;
}

// OnSumUpInvoke() �́AISumUp ���������� COM �I�u�W�F�N�g����C�x���g�����������Ƃ��ɁATEventHandler �x�[�X�̃N���X�I�u�W�F�N�g�ɂ���ČĂяo�����
HRESULT CClient::OnSumUpInvoke(
	ISumUpEventHandler* pEventHandler,
	DISPID dispidMember, 
	REFIID riid,
	LCID lcid, 
	WORD wFlags, 
	DISPPARAMS* pdispparams, 
	VARIANT* pvarResult,
	EXCEPINFO* pexcepinfo, 
	UINT* puArgErr)
{
	if (0x01 == dispidMember)	// Event1 event.
	{
		// ��P�p�����[�^ : [in] int Result
		VARIANT varResult;
		int	Result = 0;
		VariantInit(&varResult);
		VariantClear(&varResult);
		varResult = (pdispparams->rgvarg)[0];
		Result = V_I4(&varResult);

		TCHAR szMessage[256];
		sprintf_s(szMessage, "Sum up result : %d", Result);
		cout << szMessage << endl;
	}

	return S_OK;
}

VOID CClient::OnDestroy()
{
	// �v���O�������I������Ƃ��AISumUp �C���^�[�t�F�C�X�����������I�u�W�F�N�g�̐ڑ��|�C���g����ؒf����悤�ɃC�x���g�n���h���[�Ɏw������
	// �܂��A(�폜��������) Release() ����K�v������
	if (m_pISumUpEventHandler)
	{
		m_pISumUpEventHandler->ShutdownConnectionPoint();
		m_pISumUpEventHandler->Release();
		m_pISumUpEventHandler = NULL;
	}

	// �X�}�[�g�|�C���g�Ȃ̂ŕs�v
	//CoUninitialize();
}

VOID CClient::OnSendToServer()
{
	// �X�P���g���R�[�h
	// COM�T�[�o�[�Ƀp�����[�^�𑗐M
	cout << "Sending..." << endl;
	m_spISumUp->SumUp(m_num1, m_num2);
}