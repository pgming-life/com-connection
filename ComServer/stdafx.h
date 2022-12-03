#if !defined(AFX_STDAFX_H__4828F255_35B0_4661_90BD_CA0B28497AAA__INCLUDED_)
#define AFX_STDAFX_H__4828F255_35B0_4661_90BD_CA0B28497AAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
// CComModuleからクラスを派生させ、オーバーライドする場合はそれを使用できる
// ただし、_Moduleの名称は変更不可
extern CComModule _Module;
#include <atlcom.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は、前の行の直前に追加の宣言を挿入

#endif // !defined(AFX_STDAFX_H__4828F255_35B0_4661_90BD_CA0B28497AAA__INCLUDED)