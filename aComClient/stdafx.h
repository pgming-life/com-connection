#pragma once

#include <Windows.h>
#include <iostream>

#define SAFE_RELEASE(x) if(x) x->Release();

using namespace std;