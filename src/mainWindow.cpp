#include "preCompiled.h"

mainWindow::mainWindow(const std::wstring& className)
	: Window(), className(className)
{
}

mainWindow::~mainWindow()
{
}

bool mainWindow::create(const std::wstring& title, uint32_t width, uint32_t height)
{
	return true;
}
