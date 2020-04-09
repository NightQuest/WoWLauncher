#pragma once

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <windowsx.h>

#include <commctrl.h>
#pragma comment(lib,"comctl32.lib")
#pragma comment(linker, "/manifestdependency:"\
"\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <winver.h>
#pragma comment(lib, "version.lib")

#include <string>
#include <sstream>
#include <unordered_map>
#include <filesystem>
#include <memory>
#include <algorithm>

#include "resource.h"

#include "Registry.h"
#include "Window.h"
#include "ChildWindow.h"
#include "Program.h"
#include "mainWindow.h"
