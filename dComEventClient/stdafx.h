#pragma once

#include <Windows.h>
#include <iostream>

#define SAFE_RELEASE(x) if(x) x->Release();

#import "EventFiringObject.dll"
using namespace EVENTFIRINGOBJECTLib;

#include "TEventHandler.h"
using namespace TEventHandlerNamespace;

using namespace std;