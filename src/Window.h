#pragma once

class Window
{
public:
	Window();
	virtual ~Window();

	// Utility
	const HWND getHandle() const { return windowHandle; }

	// Pure virtuals
#ifdef UNICODE
	virtual bool create(const std::wstring& title, uint32_t width, uint32_t height) = 0;
#else
	virtual bool create(const std::string& title, uint32_t width, uint32_t height) = 0;
#endif

protected:
	HINSTANCE hInstance;
	ATOM windowClass;
	HWND windowHandle;
};
