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
	::InitCommonControls();

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
	for( uint32_t x = IDC_MAIN_STATUS; x < IDC_MAX; x++ )
		children[x] = new ChildWindow();

	const unsigned int padding = 10;
	const unsigned int listboxWidth = 150;
	const unsigned int buttonWidth = (listboxWidth - padding) / 2;
	const unsigned int checkboxWidth = 90;
	const unsigned int installButtonWidth = 20;
	const unsigned int buttonHeight = 23;
	const unsigned int statusBarHeight = 22;
	const unsigned int staticHeight = 20;
	const unsigned int editHeight = staticHeight;
	const unsigned int checkboxHeight = staticHeight - 2;
	
	RECT windowSize;
	::GetClientRect(windowHandle, &windowSize);

	RECT controlSize;
	controlSize.left = padding + listboxWidth + padding;
	controlSize.top = padding;
	controlSize.right = windowSize.right - controlSize.left - padding;

	if( !children[IDC_MAIN_STATUS]->create(0, STATUSCLASSNAME, L"", WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0, this, IDC_MAIN_STATUS, GetModuleHandle(NULL)) ||

		// Do the right-hand side first, top down

		!children[IDC_NAME_STATIC]->create(0, WC_STATIC, L"Name", WS_CHILD | WS_VISIBLE,
			controlSize.left, controlSize.top, controlSize.right, staticHeight, this, IDC_NAME_STATIC) ||

		!children[IDC_NAME_EDIT]->create(WS_EX_CLIENTEDGE, WC_EDIT, L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
			controlSize.left, (controlSize.top += staticHeight), controlSize.right, editHeight, this, IDC_NAME_EDIT) ||

		!children[IDC_USELAUNCHER_CHECKBOX]->create(0, WC_BUTTON, L"Use Launcher", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			windowSize.right - padding - checkboxWidth, (controlSize.top += editHeight + padding), checkboxWidth, checkboxHeight, this, IDC_USELAUNCHER_CHECKBOX) ||

		!children[IDC_INSTALL_STATIC]->create(0, WC_STATIC, L"Install Directory", WS_CHILD | WS_VISIBLE,
			controlSize.left, controlSize.top, controlSize.right - checkboxWidth - padding, staticHeight, this, IDC_INSTALL_STATIC) ||

		!children[IDC_INSTALL_EDIT]->create(WS_EX_CLIENTEDGE, WC_EDIT, L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
			controlSize.left, (controlSize.top += staticHeight), controlSize.right - installButtonWidth - padding, editHeight, this, IDC_INSTALL_EDIT) ||

		!children[IDC_INSTALL_BUTTON]->create(0, WC_BUTTON, L"...", WS_CHILD | WS_VISIBLE,
			windowSize.right - padding - installButtonWidth, controlSize.top - staticHeight + checkboxHeight, installButtonWidth, buttonHeight, this, IDC_INSTALL_BUTTON) ||

		!children[IDC_COMMANDLINE_STATIC]->create(0, WC_STATIC, L"Command-line Arguments", WS_CHILD | WS_VISIBLE,
			controlSize.left, (controlSize.top += editHeight + padding), controlSize.right, staticHeight, this, IDC_COMMANDLINE_STATIC) ||

		!children[IDC_COMMANDLINE_EDIT]->create(WS_EX_CLIENTEDGE, WC_EDIT, L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
			controlSize.left, (controlSize.top += staticHeight), controlSize.right, editHeight, this, IDC_COMMANDLINE_EDIT) ||

		!children[IDC_SETREALMLIST_CHECKBOX]->create(0, WC_BUTTON, L"Set Realmlist", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			windowSize.right - padding - checkboxWidth, (controlSize.top += editHeight + padding), checkboxWidth, checkboxHeight, this, IDC_SETREALMLIST_CHECKBOX) ||

		!children[IDC_REALM_STATIC]->create(0, WC_STATIC, L"Realmlist", WS_CHILD | WS_VISIBLE,
			controlSize.left, controlSize.top, controlSize.right - checkboxWidth - padding, staticHeight, this, IDC_REALM_STATIC) ||

		!children[IDC_REALM_EDIT]->create(WS_EX_CLIENTEDGE, WC_EDIT, L"", WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL | WS_VSCROLL,
			controlSize.left, (controlSize.top += staticHeight), controlSize.right, editHeight + padding + editHeight, this, IDC_REALM_EDIT) ||

		!children[IDC_DESCRIPTION_STATIC]->create(0, WC_STATIC, L"Description", WS_CHILD | WS_VISIBLE,
			controlSize.left, (controlSize.top += (editHeight + padding + editHeight) + padding), controlSize.right, staticHeight, this, IDC_DESCRIPTION_STATIC) ||

		!children[IDC_DESCRIPTION_EDIT]->create(WS_EX_CLIENTEDGE, WC_EDIT, L"", WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_WANTRETURN | ES_AUTOVSCROLL | WS_VSCROLL,
			controlSize.left, (controlSize.top += staticHeight), controlSize.right, editHeight + padding + editHeight, this, IDC_DESCRIPTION_EDIT) ||

		// Now do the bottom buttons, left to right

		!children[IDC_NEW_BUTTON]->create(0, WC_BUTTON, L"New", WS_CHILD | WS_VISIBLE,
		(controlSize.left = padding), (controlSize.top += (editHeight + padding + editHeight) + padding), buttonWidth, buttonHeight, this, IDC_NEW_BUTTON) ||

		!children[IDC_DELETE_BUTTON]->create(0, WC_BUTTON, L"Delete", WS_CHILD | WS_VISIBLE,
		(controlSize.left += buttonWidth + padding), controlSize.top, buttonWidth, buttonHeight, this, IDC_DELETE_BUTTON) ||

		!children[IDC_SAVE_BUTTON]->create(0, WC_BUTTON, L"Save", WS_CHILD | WS_VISIBLE,
		(controlSize.left += buttonWidth + padding), controlSize.top, buttonWidth, buttonHeight, this, IDC_SAVE_BUTTON) ||

		!children[IDC_LAUNCH_BUTTON]->create(0, WC_BUTTON, L"Launch", WS_CHILD | WS_VISIBLE,
			windowSize.right - padding - buttonWidth, controlSize.top, buttonWidth, buttonHeight, this, IDC_LAUNCH_BUTTON) ||

		// Now do the left-hand side

		!children[IDC_SERVER_LISTBOX]->create(WS_EX_CLIENTEDGE, WC_LISTBOX, L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY | LBS_WANTKEYBOARDINPUT | LBS_NOINTEGRALHEIGHT,
			padding, padding, listboxWidth, (controlSize.top - padding - padding), this, IDC_SERVER_LISTBOX) )
	{
		::MessageBox(NULL, L"Control Creation failed!", L"Error!", MB_ICONERROR | MB_OK);
		::PostMessage(windowHandle, WM_CLOSE, 0, 0);
		return FALSE;
	}

	// Now DPI scale the children
	for( auto itr = children.begin(); itr != children.end(); itr++ )
	{

		RECT rect = {};
		::GetWindowRect(itr->second->getHandle(), &rect);
		::MapWindowRect(HWND_DESKTOP, GetAncestor(itr->second->getHandle(), GA_PARENT), &rect);

		uint32_t width = MulDiv((rect.right - rect.left) * 2, dpi, 96) / 2;
		uint32_t X = MulDiv(rect.left, dpi, 96);

		// Limit the width of statics to their text width
		if( itr->first == IDC_NAME_STATIC ||
			itr->first == IDC_INSTALL_STATIC ||
			itr->first == IDC_COMMANDLINE_STATIC ||
			itr->first == IDC_REALM_STATIC ||
			itr->first == IDC_DESCRIPTION_STATIC )
		{
			HDC hdc = ::GetDC(itr->second->getHandle());
			wchar_t text[MAX_PATH] = {};
			int count = GetWindowText(itr->second->getHandle(), text, MAX_PATH);
			SIZE bounds;
			::GetTextExtentPoint32(hdc, text, count, &bounds);
			::ReleaseDC(itr->second->getHandle(), hdc);

			width = bounds.cx + padding;
		}

		if( X > windowSize.right )
			X = (windowSize.right - (padding * 2) - width);
		if( X + width > windowSize.right )
			width = windowSize.right - X - (padding * 2);

		// special case for the install edit, as there's a button to the side
		if( itr->first == IDC_INSTALL_EDIT )
		{
			RECT buttonSize = {};
			::GetWindowRect(children[IDC_INSTALL_BUTTON]->getHandle(), &buttonSize);

			width -= MulDiv((buttonSize.right - buttonSize.left), dpi, 96) + padding;
		}

		itr->second->SetPosition(
			X,
			MulDiv(rect.top, dpi, 96),
			width,
			MulDiv(rect.bottom - rect.top, dpi, 96),
			SWP_NOZORDER | SWP_NOACTIVATE
		);
	}

	// Now set their fonts
	auto hFontOld = reinterpret_cast<HFONT>(::SendMessage(children[IDC_NAME_STATIC]->getHandle(), WM_GETFONT, 0, 0));
	LOGFONT lfText = {};
	::SystemParametersInfoForDpi(SPI_GETICONTITLELOGFONT, sizeof(lfText), &lfText, FALSE, dpi);
	HFONT hFontNew = ::CreateFontIndirect(&lfText);
	if( hFontNew )
	{
		::DeleteObject(hFontOld);
		::EnumChildWindows(windowHandle, [](HWND hWnd, LPARAM lParam) -> BOOL
			{
				::SendMessage(hWnd, WM_SETFONT, (WPARAM)lParam, MAKELPARAM(TRUE, 0));
				return TRUE;
			}, (LPARAM)hFontNew);
	}

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

LRESULT mainWindow::onCTLColorStatic(HDC hdc, HWND hwnd)
{
	int controlID = ::GetDlgCtrlID(hwnd);
	if( controlID != IDC_NAME_STATIC &&
		controlID != IDC_INSTALL_STATIC &&
		controlID != IDC_COMMANDLINE_STATIC &&
		controlID != IDC_REALM_STATIC &&
		controlID != IDC_DESCRIPTION_STATIC &&
		controlID != IDC_USELAUNCHER_CHECKBOX &&
		controlID != IDC_SETREALMLIST_CHECKBOX )
		return TRUE;

	::SetBkMode(hdc, TRANSPARENT);
	::SetTextColor(hdc, RGB(0, 0, 0));
	return reinterpret_cast<LRESULT>(GetSysColorBrush(COLOR_MENU));
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