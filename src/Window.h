#pragma once

class Window
{
public:
	Window();
	virtual ~Window();

	// Utility
	const HWND getHandle() const { return windowHandle; }
	const uint32_t getDPI() const;
	const RECT getCurrentMonitorRect() const;

	// easy-access to API
	BOOL Show(int nShowCmd) { return ::ShowWindow(windowHandle, nShowCmd); }
	BOOL Update() { return ::UpdateWindow(windowHandle); }
	bool registerClass(const WNDCLASS& wc) { return ((windowClass = ::RegisterClass(&wc)) != 0); }
	bool registerClassEx(const WNDCLASSEX& wc) { return ((windowClass = ::RegisterClassEx(&wc)) != 0); }

	// Events - for most of them, return FALSE if we process them
	virtual LRESULT onCreate(LPCREATESTRUCT lpCreate) { UNREFERENCED_PARAMETER(lpCreate); return TRUE; }
	virtual LRESULT onDestroy() { return TRUE; }
	virtual LRESULT onClose() { return TRUE; }
	virtual LRESULT onShow(BOOL beingShown, UINT status) { UNREFERENCED_PARAMETER(beingShown); UNREFERENCED_PARAMETER(status); return TRUE; }
	virtual LRESULT onPosChanging(LPWINDOWPOS windowPos) { UNREFERENCED_PARAMETER(windowPos); return TRUE; }
	virtual LRESULT onPosChanged(LPWINDOWPOS windowPos) { UNREFERENCED_PARAMETER(windowPos); return TRUE; }
	virtual LRESULT onVKeyToItem(HWND hListBox, uint32_t keyCode, uint32_t caretPosition) { UNREFERENCED_PARAMETER(hListBox); UNREFERENCED_PARAMETER(keyCode); UNREFERENCED_PARAMETER(caretPosition); return TRUE; }
	virtual LRESULT onCommandMenu(DWORD menu) { UNREFERENCED_PARAMETER(menu); return TRUE; }
	virtual LRESULT onCommandAccel(DWORD accel) { UNREFERENCED_PARAMETER(accel); return TRUE; }
	virtual LRESULT onCommandControl(DWORD controlID, HWND controlHandle, DWORD notificationCode) { UNREFERENCED_PARAMETER(controlID); UNREFERENCED_PARAMETER(controlHandle); UNREFERENCED_PARAMETER(notificationCode); return TRUE; }
	virtual LRESULT onMenuCommand(HMENU menuHandle, DWORD selectedIndex) { UNREFERENCED_PARAMETER(menuHandle); UNREFERENCED_PARAMETER(selectedIndex); return TRUE; }
	virtual LRESULT onCTLColorStatic(HDC hdc, HWND hwnd) { UNREFERENCED_PARAMETER(hdc); UNREFERENCED_PARAMETER(hwnd); return FALSE; }
	virtual LRESULT onDPIChanged(uint32_t newDPI, LPRECT newScale) { UNREFERENCED_PARAMETER(newDPI); UNREFERENCED_PARAMETER(newScale); return TRUE; }

	// Pure virtuals
	virtual bool create(const std::wstring& title, uint32_t width, uint32_t height) = 0;

	// Event procs
	virtual LRESULT windowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK handleWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	HINSTANCE hInstance;
	ATOM windowClass;
	HWND windowHandle;
};
