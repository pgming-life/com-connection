#include "stdafx.h"
#include "CClientDlg.h"

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	// Win32 では、LoadIcon は後続の DestroyIcon を必要としないことに注意
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	// 注: ClassWizard は DDX および DDV 呼び出しをここに追加する
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

	// システム メニューに「About...」メニュー項目を追加

	// IDM_ABOUTBOX は、システムコマンドの範囲内にある必要がある
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

	// このダイアログのアイコンを設定
	// アプリケーションのメインウィンドウがダイアログでない場合、フレームワークはこれを自動的に行う
	SetIcon(m_hIcon, TRUE);		// Set big icon
	SetIcon(m_hIcon, FALSE);	// Set small icon
	
	// TODO: ここに初期化を追加

	// ISumUp を実装するオブジェクトのインスタンスを作成
	m_spISumUp.CreateInstance(__uuidof(SumUp));

	// ISumUpEventHandler オブジェクトをインスタンス化
	m_pISumUpEventHandler = new ISumUpEventHandler(*this, m_spISumUp, &CClientDlg::OnSumUpInvoke);
	
	return TRUE;	// コントロールにフォーカスを設定しない限り TRUE を返す
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するために以下のコードが必要になる
// document/view モデルを使用する MFC アプリケーションの場合、これはフレームワークによって自動的に行われる
void CClientDlg::OnPaint() 
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
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// OnSumUpInvoke() は、ISumUp を実装する COM オブジェクトからイベントが発生したときに、TEventHandler ベースのクラスオブジェクトによって呼び出される
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
		// 第１パラメータ : [in] int Result
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
	
	// TODO: ここにメッセージ ハンドラー コードを追加

	// プログラムが終了するとき、ISumUp インターフェイスを実装したオブジェクトの接続ポイントから切断するようにイベントハンドラーに指示する
	// また、(削除する代わりに) Release() する必要がある
	if (m_pISumUpEventHandler)
	{
		m_pISumUpEventHandler->ShutdownConnectionPoint();
		m_pISumUpEventHandler->Release();
		m_pISumUpEventHandler = NULL;
	}
}

void CClientDlg::OnButtonCallFunction()
{
	// TODO: コントロール通知ハンドラ コードをここに追加
	// ISumUp.SumUp() を呼び出す
	// これにより、ISumUp を実装するオブジェクトが Event1 を起動する
	m_spISumUp->SumUp(2, 3);
}