#pragma once

class ChildWindow
{
public:
	ChildWindow();
	virtual ~ChildWindow();

	// Utility
	const HWND getHandle() const { return windowHandle; }
	const DWORD getID() const { return windowID; }
	const Window* getParent() const { return parentWindow; }

	// easy-access to API
	BOOL SetPosition(uint32_t X, uint32_t Y, uint32_t width, uint32_t height, uint32_t flags) const { return ::SetWindowPos(windowHandle, nullptr, X, Y, width, height, flags); }

	// Events - return FALSE if we process them
	virtual LRESULT onTextChange() { return TRUE; }
	virtual LRESULT onButtonClicked() { return TRUE; }
	virtual LRESULT onListBoxSelChange() { return TRUE; }
	virtual LRESULT onListBoxDoubleClick() { return TRUE; }

	bool create(DWORD dwExStyle, const std::wstring& className, const std::wstring& windowName, DWORD dwStyle, uint32_t x, uint32_t y, uint32_t width, uint32_t height, Window* parent, DWORD windowID, HINSTANCE hInst = 0, LPVOID lpParam = 0);

protected:
	HWND windowHandle;
	DWORD windowID;
	HINSTANCE hInstance;
	Window* parentWindow;
};
