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

// �G���g���|�C���g
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

// DLL��OLE�ɂ���ăA�����[�h�ł��邩�ǂ����𔻒f
STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

// �N���X�t�@�N�g����Ԃ��A�v�����ꂽ�^�̃I�u�W�F�N�g���쐬
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

// �V�X�e�����W�X�g���ɃG���g����ǉ�
STDAPI DllRegisterServer(void)
{
    // �I�u�W�F�N�g�A�^�C�v���C�u�����A�y�т��ׂẴC���^�[�t�F�[�X���^�C�v���C�u�����ɓo�^
    return _Module.RegisterServer(TRUE);
}

// �V�X�e�����W�X�g������G���g�����폜
STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}