#include "preCompiled.h"

ChildWindow::ChildWindow()
	: windowHandle(0), windowID(0), hInstance(0), parentWindow(nullptr), windowWidth(0), windowHeight(0)
{
}

ChildWindow::~ChildWindow()
{
}

bool ChildWindow::create(DWORD dwExStyle, const std::wstring& className, const std::wstring& windowName, DWORD dwStyle, uint32_t x, uint32_t y, uint32_t width, uint32_t height, Window* parent, DWORD ID, HINSTANCE hInst, LPVOID lpParam)
{
	if( windowHandle != 0 )
		return false;

	windowHandle = ::CreateWindowEx(dwExStyle, className.c_str(), windowName.c_str(), dwStyle, x, y, width, height, parent->getHandle(), reinterpret_cast<HMENU>(ID), hInst, lpParam);
	if( !windowHandle )
		return false;

	windowID = ID;
	hInstance = hInst;
	parentWindow = parent;

	windowWidth = width;
	windowHeight = height;

	return true;
}

void ChildWindow::scaleToDPI(uint32_t dpi)
{
	RECT rect = {};
	::GetWindowRect(windowHandle, &rect);

	POINT rXY = { rect.left, rect.top };
	::ScreenToClient(parentWindow->getHandle(), &rXY);

	::SetWindowPos(windowHandle, nullptr,
		::MulDiv(rXY.x, dpi, USER_DEFAULT_SCREEN_DPI),
		::MulDiv(rXY.y, dpi, USER_DEFAULT_SCREEN_DPI),
		::MulDiv(windowWidth, dpi, USER_DEFAULT_SCREEN_DPI),
		::MulDiv(windowHeight, dpi, USER_DEFAULT_SCREEN_DPI),
		SWP_NOZORDER | SWP_NOACTIVATE);
}
