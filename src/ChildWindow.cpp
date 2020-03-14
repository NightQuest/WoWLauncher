#include "preCompiled.h"

ChildWindow::ChildWindow()
	: windowHandle(0), windowID(0), parentWindow(nullptr)
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
	if( windowHandle )
	{
		windowID = ID;
		hInstance = hInst;
		parentWindow = parent;

		return true;
	}

	return false;
}
