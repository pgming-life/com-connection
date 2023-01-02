#pragma once

#include <Windows.h>
#include <iostream>

using namespace std;

#define SAFE_RELEASE(x) if(x) x->Release();

#import "../bin/Win32/Release/ComIDispatchServer.dll"
using namespace CONNECTIONCOMLib;

#include "TEventHandler.h"
using namespace TEventHandlerNamespace;