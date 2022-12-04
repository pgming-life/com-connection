#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "CServer.h"
#include "CServer_i.c"
#include "SumUp.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_SumUp, CSumUp)
END_OBJECT_MAP()

// エントリポイント
extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_CONNECTIONCOMLib);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    return TRUE;
}

// DLLがOLEによってアンロードできるかどうかを判断
STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

// クラスファクトリを返し、要求された型のオブジェクトを作成
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

// システムレジストリにエントリを追加
STDAPI DllRegisterServer(void)
{
    // オブジェクト、タイプライブラリ、及びすべてのインターフェースをタイプライブラリに登録
    return _Module.RegisterServer(TRUE);
}

// システムレジストリからエントリを削除
STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}