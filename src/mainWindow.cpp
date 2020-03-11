#include "preCompiled.h"

mainWindow::mainWindow(const std::wstring& className)
	: Window(), className(className)
{
}

mainWindow::~mainWindow()
{
}

// Handle the close event
// Returns: FALSE because we're handling it
LRESULT mainWindow::onClose()
{
	::DestroyWindow(windowHandle);
	return FALSE;
}

// Handle the destroy event
// Returns: FALSE because we're handling it
LRESULT mainWindow::onDestroy()
{
	::PostQuitMessage(EXIT_SUCCESS);
	return FALSE;
}

// Create our window
// Return: true on success
bool mainWindow::create(const std::wstring& title, uint32_t width, uint32_t height)
{
	// Create our window class
	WNDCLASSEX wcx;
	wcx.cbSize = sizeof(WNDCLASSEX);
	wcx.style = 0;
	wcx.lpfnWndProc = Window::handleWindowProc;
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = hInstance;
	wcx.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN_ICON));
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	//wcx.hbrBackground = hBackgroundBrush = CreateSolidBrush(RGB(20, 25, 30));
	wcx.hbrBackground = GetSysColorBrush(COLOR_MENU);
	wcx.lpszMenuName = 0;
	wcx.lpszClassName = className.c_str();
	wcx.hIconSm = reinterpret_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(IDI_MAIN_ICON_BLACK), IMAGE_ICON, 16, 16, 0));

	// Register our class
	if( !registerClassEx(wcx) )
		return false;

	// Convert from client area to window size
	DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	//DWORD style = 0;
	RECT windowSize;
	windowSize.right = width;
	windowSize.bottom = height;
	::AdjustWindowRectEx(&windowSize, style, FALSE, NULL);

	// Create our Window
	windowHandle = ::CreateWindowEx(NULL, MAKEINTATOM(windowClass), title.c_str(),
		WS_OVERLAPPED | style,
		(GetSystemMetrics(SM_CXSCREEN) - windowSize.right) / 2, // X center
		(GetSystemMetrics(SM_CYSCREEN) - windowSize.bottom) / 2, // Y center
		windowSize.right, windowSize.bottom, static_cast<HWND>(NULL), static_cast<HMENU>(NULL),
		hInstance, this);

	if( !windowHandle )
		return false;

	// Without this, we still have a titlebar
	//SetWindowLongPtr(windowHandle, GWL_STYLE, 0L);

	return true;
}