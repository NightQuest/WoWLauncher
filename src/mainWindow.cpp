#include "preCompiled.h"

const uint32_t snappingThreshold = 10;

mainWindow::mainWindow(const std::wstring& className)
	: Window(), className(className), windowHeight(0), windowWidth(0), recentlyCreated(false)
{
}

mainWindow::~mainWindow()
{
}

// Handle the onCreate event
// Returns: FALSE because we're handling it
LRESULT mainWindow::onCreate(LPCREATESTRUCT lpCreate)
{
	recentlyCreated = true;
	return FALSE;
}

// Handle the onShow event - scale app window, and create children.
// Returns: FALSE because we're handling it
LRESULT mainWindow::onShow(BOOL beingShown, UINT status)
{
	if( recentlyCreated )
	{
		recentlyCreated = false;
		return onFirstShow(beingShown, status);
	}

	return FALSE;
}

LRESULT mainWindow::onFirstShow(BOOL beingShown, UINT status)
{
	uint32_t dpi = getDPI();
	RECT rcWindow = {};
	RECT workingSize = getCurrentMonitorRect();

	// Adjust our window size for DPI
	::GetWindowRect(windowHandle, &rcWindow);
	rcWindow.right = MulDiv(windowWidth, dpi, 96);
	rcWindow.bottom = MulDiv(windowHeight, dpi, 96);
	rcWindow.left = ((workingSize.right - workingSize.left) - rcWindow.right) / 2;
	rcWindow.top = ((workingSize.bottom - workingSize.top) - rcWindow.bottom) / 2;
	::SetWindowPos(windowHandle, nullptr, rcWindow.left, rcWindow.top, rcWindow.right, rcWindow.bottom, SWP_NOZORDER | SWP_NOACTIVATE);

	// Create our controls

	return FALSE;
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

// Handle the position changing event
// Returns: FALSE because we're handling it
LRESULT mainWindow::onPosChanging(LPWINDOWPOS windowPos)
{
	RECT workingSize = getCurrentMonitorRect();
	if( workingSize.right == 0 )
		return TRUE;

	// Snap to left
	if( ::abs(windowPos->x - workingSize.left) <= snappingThreshold )
		windowPos->x = workingSize.left;

	// Snap to right
	else if( ::abs((windowPos->x + windowPos->cx) - workingSize.right) <= snappingThreshold )
		windowPos->x = (workingSize.right - windowPos->cx);

	// Snap to top
	if( ::abs(windowPos->y - workingSize.top) <= snappingThreshold )
		windowPos->y = workingSize.top;

	// Snap to bottom
	else if( ::abs((windowPos->y + windowPos->cy) - workingSize.bottom) <= snappingThreshold )
		windowPos->y = (workingSize.bottom - windowPos->cy);

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
	//DWORD style = 0; // Get rid of the titlebar buttons
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

	// Save our width & height for DPI scaling
	windowHeight = height;
	windowWidth = width;

	// Without this, we still have a titlebar
	//SetWindowLongPtr(windowHandle, GWL_STYLE, 0L);

	return true;
}