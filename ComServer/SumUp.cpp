#include "stdafx.h"
#include "CServer.h"
#include "SumUp.h"

STDMETHODIMP CSumUp::SumUp(int a, int b)
{
	// TODO: �����Ɏ����R�[�h��ǉ�

	// �����v���Z�X���V�~�����[�g
	Sleep(2000);
	
	// �v���Z�X���I�����ăN���C�A���g�ɒʒm
	Fire_ExecutionOver(a+b); 

	return S_OK;
}
