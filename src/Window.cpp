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
