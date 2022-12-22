#pragma once

// MFC support for Windows Common Controls
#include <afxwin.h>
#include <afxext.h>
#include <afxdisp.h>
#include <afxdtctl.h>
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>
#endif

#import "../bin/Win32/Release/ComIDispatchServer.dll"
using namespace CONNECTIONCOMLib;

#include "TEventHandler.h"
using namespace TEventHandlerNamespace;