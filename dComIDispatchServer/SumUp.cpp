#include "stdafx.h"
#include "CServer.h"
#include "SumUp.h"

STDMETHODIMP CSumUp::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISumUp
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid)) return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSumUp::SumUp(long lValue)
{
	// TODO: �����Ɏ����R�[�h��ǉ�

	// �����v���Z�X���V�~�����[�g
	Sleep(2000);

	// �v���Z�X���I�����ăN���C�A���g�ɒʒm
	Fire_Event1(lValue);

	return S_OK;
}