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
	// Win32 では、LoadIcon は後続の DestroyIcon を必要としないことに注意
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	// 注: ClassWizard は DDX および DDV 呼び出しをここに追加する
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

	// システム メニューに「About...」メニュー項目を追加

	// IDM_ABOUTBOX は、システムコマンドの範囲内にある必要がある
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

	// このダイアログのアイコンを設定
	// アプリケーションのメインウィンドウがダイアログでない場合、フレームワークはこれを自動的に行う
	SetIcon(m_hIcon, TRUE);		// Set big icon
	SetIcon(m_hIcon, FALSE);	// Set small icon
	
	// TODO: ここに初期化を追加

	// ISumUp を実装するオブジェクトのインスタンスを作成
	m_spISumUp.CreateInstance(__uuidof(SumUp));

	// ISumUpEventHandler オブジェクトをインスタンス化
	m_pISumUpEventHandler = new ISumUpEventHandler(*this, m_spISumUp, &CTestClientDlg::OnSumUpInvoke);
	
	return TRUE;	// コントロールにフォーカスを設定しない限り TRUE を返す
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

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するために以下のコードが必要になる
// document/view モデルを使用する MFC アプリケーションの場合、これはフレームワークによって自動的に行われる
void CTestClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);	// ペイントのデバイスコンテキスト
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの四角形の中央にアイコンを配置
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// システムはこれを呼び出して、ユーザーが最小化されたウィンドウをドラッグしているときに表示するカーソルを取得
HCURSOR CTestClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// OnSumUpInvoke() は、ISumUp を実装する COM オブジェクトからイベントが発生したときに、TEventHandler ベースのクラス オブジェクトによって呼び出される
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
		// 第１パラメータ : [in] int Result
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
	
	// TODO: ここにメッセージ ハンドラー コードを追加

	// プログラムが終了するとき、ISumUp インターフェイスを実装したオブジェクトの接続ポイントから切断するようにイベントハンドラーに指示する
	// また、(削除する代わりに) Release() する必要がある
	if (m_pISumUpEventHandler)
	{
		m_pISumUpEventHandler -> ShutdownConnectionPoint();
		m_pISumUpEventHandler -> Release();
		m_pISumUpEventHandler = NULL;
	}
}

void CTestClientDlg::OnButtonCallFunction() 
{
	// TODO: コントロール通知ハンドラ コードをここに追加
	// ISumUp.ExecutionOver() を呼び出す
	// これにより、ISumUp を実装するオブジェクトが Event1 を起動する
	m_spISumUp->SumUp(123);
}