#include "stdafx.h"
#include "CClientDlg.h"

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	// Win32 �ł́ALoadIcon �͌㑱�� DestroyIcon ��K�v�Ƃ��Ȃ����Ƃɒ���
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	// ��: ClassWizard �� DDX ����� DDV �Ăяo���������ɒǉ�����
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CALL_FUNCTION, OnButtonCallFunction)
END_MESSAGE_MAP()

BOOL CClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �V�X�e�� ���j���[�ɁuAbout...�v���j���[���ڂ�ǉ�

	// IDM_ABOUTBOX �́A�V�X�e���R�}���h�͈͓̔��ɂ���K�v������
	ASSERT(IDM_ABOUTBOX == (IDM_ABOUTBOX & 0xFFF0));
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (NULL != pSysMenu)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���̃_�C�A���O�̃A�C�R����ݒ�
	// �A�v���P�[�V�����̃��C���E�B���h�E���_�C�A���O�łȂ��ꍇ�A�t���[�����[�N�͂���������I�ɍs��
	SetIcon(m_hIcon, TRUE);		// Set big icon
	SetIcon(m_hIcon, FALSE);	// Set small icon
	
	// TODO: �����ɏ�������ǉ�

	// ISumUp ����������I�u�W�F�N�g�̃C���X�^���X���쐬
	m_spISumUp.CreateInstance(__uuidof(SumUp));

	// ISumUpEventHandler �I�u�W�F�N�g���C���X�^���X��
	m_pISumUpEventHandler = new ISumUpEventHandler(*this, m_spISumUp, &CClientDlg::OnSumUpInvoke);
	
	return TRUE;	// �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ����� TRUE ��Ԃ�
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂Ɉȉ��̃R�[�h���K�v�ɂȂ�
// document/view ���f�����g�p���� MFC �A�v���P�[�V�����̏ꍇ�A����̓t���[�����[�N�ɂ���Ď����I�ɍs����
void CClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);	// �y�C���g�̃f�o�C�X�R���e�L�X�g
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// �N���C�A���g�̎l�p�`�̒����ɃA�C�R����z�u
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R����`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// �V�X�e���͂�����Ăяo���āA���[�U�[���ŏ������ꂽ�E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// OnSumUpInvoke() �́AISumUp ���������� COM �I�u�W�F�N�g����C�x���g�����������Ƃ��ɁATEventHandler �x�[�X�̃N���X�I�u�W�F�N�g�ɂ���ČĂяo�����
HRESULT CClientDlg::OnSumUpInvoke(
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
		::MessageBox(NULL, szMessage, "Event", MB_OK);
	}

	return S_OK;
}

void CClientDlg::OnDestroy()
{
	CDialog::OnDestroy();
	
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ�

	// �v���O�������I������Ƃ��AISumUp �C���^�[�t�F�C�X�����������I�u�W�F�N�g�̐ڑ��|�C���g����ؒf����悤�ɃC�x���g�n���h���[�Ɏw������
	// �܂��A(�폜��������) Release() ����K�v������
	if (m_pISumUpEventHandler)
	{
		m_pISumUpEventHandler->ShutdownConnectionPoint();
		m_pISumUpEventHandler->Release();
		m_pISumUpEventHandler = NULL;
	}
}

void CClientDlg::OnButtonCallFunction()
{
	// TODO: �R���g���[���ʒm�n���h�� �R�[�h�������ɒǉ�
	// ISumUp.SumUp() ���Ăяo��
	// ����ɂ��AISumUp ����������I�u�W�F�N�g�� Event1 ���N������
	m_spISumUp->SumUp(2, 3);
}