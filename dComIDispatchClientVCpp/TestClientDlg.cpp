#include "stdafx.h"
#include "TestClient.h"
#include "TestClientDlg.h"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	// No message handlers
END_MESSAGE_MAP()

CTestClientDlg::CTestClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestClientDlg::IDD, pParent)
{
	// Win32 �ł́ALoadIcon �͌㑱�� DestroyIcon ��K�v�Ƃ��Ȃ����Ƃɒ���
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	// ��: ClassWizard �� DDX ����� DDV �Ăяo���������ɒǉ�����
}

BEGIN_MESSAGE_MAP(CTestClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CALL_TEST_FUNCTION, OnButtonCallFunction)
END_MESSAGE_MAP()

BOOL CTestClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �V�X�e�� ���j���[�ɁuAbout...�v���j���[���ڂ�ǉ�

	// IDM_ABOUTBOX �́A�V�X�e���R�}���h�͈͓̔��ɂ���K�v������
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
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
	m_pISumUpEventHandler = new ISumUpEventHandler(*this, m_spISumUp, &CTestClientDlg::OnSumUpInvoke);
	
	return TRUE;	// �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ����� TRUE ��Ԃ�
}

void CTestClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (IDM_ABOUTBOX == (nID & 0xFFF0))
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂Ɉȉ��̃R�[�h���K�v�ɂȂ�
// document/view ���f�����g�p���� MFC �A�v���P�[�V�����̏ꍇ�A����̓t���[�����[�N�ɂ���Ď����I�ɍs����
void CTestClientDlg::OnPaint() 
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
HCURSOR CTestClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// OnSumUpInvoke() �́AISumUp ���������� COM �I�u�W�F�N�g����C�x���g�����������Ƃ��ɁATEventHandler �x�[�X�̃N���X �I�u�W�F�N�g�ɂ���ČĂяo�����
HRESULT CTestClientDlg::OnSumUpInvoke
(
	ISumUpEventHandler* pEventHandler,
	DISPID dispidMember, 
	REFIID riid,
	LCID lcid, 
	WORD wFlags, 
	DISPPARAMS* pdispparams, 
	VARIANT* pvarResult,
	EXCEPINFO* pexcepinfo, 
	UINT* puArgErr
)
{
	if (dispidMember == 0x01)  // Event1 event.
	{
		// ��P�p�����[�^ : [in] int Result
		VARIANT varResult;
		int	Result = 0;
		VariantInit(&varResult);
		VariantClear(&varResult);
		varResult = (pdispparams -> rgvarg)[0];
		Result = V_I4(&varResult);

		TCHAR szMessage[256];
		sprintf_s (szMessage, "SumUp is fired with value : %d.", Result);
		::MessageBox (NULL, szMessage, "Event", MB_OK);
	}

  return S_OK;
}

void CTestClientDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ�

	// �v���O�������I������Ƃ��AISumUp �C���^�[�t�F�C�X�����������I�u�W�F�N�g�̐ڑ��|�C���g����ؒf����悤�ɃC�x���g�n���h���[�Ɏw������
	// �܂��A(�폜��������) Release() ����K�v������
	if (m_pISumUpEventHandler)
	{
		m_pISumUpEventHandler -> ShutdownConnectionPoint();
		m_pISumUpEventHandler -> Release();
		m_pISumUpEventHandler = NULL;
	}
}

void CTestClientDlg::OnButtonCallFunction() 
{
	// TODO: �R���g���[���ʒm�n���h�� �R�[�h�������ɒǉ�
	// ISumUp.ExecutionOver() ���Ăяo��
	// ����ɂ��AISumUp ����������I�u�W�F�N�g�� Event1 ���N������
	m_spISumUp->SumUp(123);
}