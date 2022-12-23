#pragma once

class CClient;

// TEventHandler �e���v���[�g���g�p���ăC�x���g�����N���X��錾
typedef TEventHandler<CClient, ISumUp, _ISumUpEvents> ISumUpEventHandler;

class CClient
{
public:
	CClient();
	~CClient();

	HRESULT OnInit(UINT num1, UINT num2);
	VOID OnDestroy();
	VOID OnSendToServer();

private:
	// �T�[�o�[�֓n���f�[�^
	int m_num1;
	int m_num2;

	// �X�}�[�g�|�C���^�̃C���X�^���X��錾
	ISumUpPtr m_spISumUp;

	// ISumUp �I�u�W�F�N�g�� _ISumUpEvents �C�x���g����C�x���g���󂯎��悤�ɓ��ʂɒ������ꂽ TEventHandler �N���X�ւ̃|�C���^��錾
	ISumUpEventHandler* m_pISumUpEventHandler;

	HRESULT OnSumUpInvoke(
	  ISumUpEventHandler* pEventHandler,
	  DISPID dispidMember, 
	  REFIID riid,
	  LCID lcid, 
	  WORD wFlags, 
	  DISPPARAMS* pdispparams, 
	  VARIANT* pvarResult,
	  EXCEPINFO* pexcepinfo, 
	  UINT* puArgErr);
};