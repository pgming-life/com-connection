#pragma once

#include <Windows.h>
#include <iostream>

using namespace std;

#import "../bin/Win32/Release/ComIDispatchServer.dll"
using namespace CONNECTIONCOMLib;

#include "TEventHandler.h"
using namespace TEventHandlerNamespace;

#define SAFE_RELEASE(x) if(x) x->Release();