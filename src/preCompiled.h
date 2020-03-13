#pragma once

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <commctrl.h>
#pragma comment(lib,"comctl32.lib")
#pragma comment(linker, "/manifestdependency:"\
"\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


#include <string>

#include "resource.h"

#include "Registry.h"
#include "Window.h"
#include "mainWindow.h"
