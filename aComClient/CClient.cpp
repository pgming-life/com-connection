#include "stdafx.h"
#include "CClient.h"
#include "CSink.h"
#include <atlbase.h>

CClient::CClient() :
	dwAdvise(0),
	pCP(NULL)
{
	m_num1 = 0;
	m_num2 = 0;
}

CClient::~CClient()
{
	// COM���
	CoUninitialize();
}

HRESULT CClient::OnInit(UINT num1, UINT num2)
{
	m_num1 = num1;
	m_num2 = num2;
	
	// COM������
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr)) return hr;
	
	return S_OK;
}

HRESULT CClient::OnSendToServer() 
{
	HRESULT  hr;

    // COM�I�u�W�F�N�g�C���X�^���X����
	CComPtr<ISumUp> pAdd;
	hr = pAdd.CoCreateInstance(CLSID_SumUp);
	if (FAILED(hr)) return hr;

	// �C���^�[�t�F�[�X�R���e�i���g�p
	IConnectionPointContainer* pCPC;
    
	// �C���^�[�t�F�[�X���ڑ��\�ȃI�u�W�F�N�g���T�|�[�g���Ă��邩���m�F
    hr = pAdd->QueryInterface(IID_IConnectionPointContainer, (void**)&pCPC);
    if (FAILED(hr)) return hr;

    // �ڑ��|�C���g�̃C���^�[�t�F�[�X���擾
    hr = pCPC->FindConnectionPoint(IID__ISumUpEvents, &pCP);
	if (FAILED(hr)) return hr;

	// �R���e�i���
	SAFE_RELEASE(pCPC);
    
	// �n���h��
	IUnknown* pSinkUnk;
	
	// �ʒm�I�u�W�F�N�g���쐬
	CSink* pSink;
    pSink = new CSink;
    if (NULL == pSink) return E_FAIL;

    // IUnknown�̃|�C���^���擾
	hr = pSink->QueryInterface(IID_IUnknown, (void**)&pSinkUnk);

	// _IAddEvents�C���^�[�t�F�[�X(pCP)�����COM�ɑ��M
	// �ԋp�l��FAIL�̏ꍇ�� IConnectionPoint:UnAdvise ���Ăяo����A�ڑ����ؒf�����
	hr = pCP->Advise(pSinkUnk, &dwAdvise); 
	
	// COM�T�[�o�[�Ƀp�����[�^�𑗐M
	cout << "Sending..." << endl;
    pAdd->SumUp(m_num1, m_num2);

	// �T�[�o�[����ؒf
	pCP->Unadvise(dwAdvise);

	// �ڑ��|�C���g���
	SAFE_RELEASE(pCP);
	
    return hr;
}