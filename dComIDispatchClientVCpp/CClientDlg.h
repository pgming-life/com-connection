#pragma once

#include "resource.h"

class CClientDlg;

// TEventHandler �e���v���[�g���g�p���ăC�x���g�����N���X��錾
typedef TEventHandler<CClientDlg, ISumUp, _ISumUpEvents> ISumUpEventHandler;

class CClientDlg : public CDialog
{
public:
	CClientDlg(CWnd* pParent = NULL);
	enum { IDD = IDD_CLIENT_DIALOG };

	// ClassWizard �ɂ���Đ������ꂽ���z�֐��̃I�[�o�[���C�h
protected:
	HICON m_hIcon;

	// �X�}�[�g�|�C���^�̃C���X�^���X��錾
	ISumUpPtr m_spISumUp;

	// ISumUp �I�u�W�F�N�g�� _ISumUpEvents �C�x���g����C�x���g���󂯎��悤�ɓ��ʂɒ������ꂽ TEventHandler �N���X�ւ̃|�C���^��錾
	ISumUpEventHandler* m_pISumUpEventHandler;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnButtonCallFunction();
	DECLARE_MESSAGE_MAP()

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