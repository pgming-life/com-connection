#include "stdafx.h"
#include "CClient.h"

int main()
{
	cout << "������������  Test Start ������������" << endl;

	// COM������
	if (FAILED(CoInitialize(NULL)))
	{
		cout << "COM�������Ɏ��s���܂����B" << endl;
		cout << "�I�����܂�..." << endl;
		Sleep(2000);
		return 0;
	}

	// �X�}�[�g�|�C���^�C���X�^���X�ł���m_spISumUp�͎����ϐ��ł���ARelease�����̂�CoUninitialize�����s�������main�X�R�[�v���o���Ƃ��ł��邽�߃A�N�Z�X�ᔽ��������B
	// ���̂��߁ACoInitialize��CoUninitialize�̊Ԃ̃u���b�N����m_spISumUp���Ǘ�����N���X�C���X�^���X�ł���client������K�v������B
	{
		CClient client;
		client.OnInit(2, 3);
		client.OnSendToServer();
		client.OnDestroy();
	}
	// �f�X�g���N�^�ďo���im_spISumUp����j

	// COM���
	CoUninitialize();

	cout << "������������ Test Finish ������������" << endl;
	system("PAUSE");
}