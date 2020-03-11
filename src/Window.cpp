#include "preCompiled.h"

Window::Window()
	: windowHandle(0), windowClass(0), hInstance(GetModuleHandle(NULL))
{
}

Window::~Window()
{
	if( windowClass )
	{
		::UnregisterClass(MAKEINTATOM(windowClass), hInstance);
		windowClass = 0;
	}
}

LRESULT Window::windowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_CREATE:
		return onCreate(reinterpret_cast<LPCREATESTRUCT>(lParam));

	case WM_DESTROY:
		return onDestroy();

	case WM_CLOSE:
		return onClose();

	case WM_SHOWWINDOW:
		return onShow(static_cast<BOOL>(wParam), static_cast<UINT>(lParam));

	case WM_WINDOWPOSCHANGING:
		return onPosChanging(reinterpret_cast<WINDOWPOS*>(lParam));
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::handleWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* window;
	if( msg == WM_NCCREATE )
	{
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		window = reinterpret_cast<Window*>(cs->lpCreateParams);
		::SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
	}
	else
		window = reinterpret_cast<Window*>(::GetWindowLongPtr(hwnd, GWLP_USERDATA));

	if( !window )
		return ::DefWindowProc(hwnd, msg, wParam, lParam);

	return window->windowProc(hwnd, msg, wParam, lParam);
}
