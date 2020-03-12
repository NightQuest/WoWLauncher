#pragma once

class mainWindow : public Window
{
public:
	mainWindow() = delete;
	mainWindow(const std::wstring& className);
	~mainWindow() override;

	LRESULT onCreate(LPCREATESTRUCT lpCreate) override;
	LRESULT onDestroy() override;
	LRESULT onClose() override;
	LRESULT onShow(BOOL beingShown, UINT status) override;
	LRESULT onPosChanging(LPWINDOWPOS windowPos) override;

	bool create(const std::wstring& title, uint32_t width, uint32_t height) override;

	LRESULT onFirstShow(BOOL beingShown, UINT status);

private:
	std::wstring className;
	uint32_t windowWidth;
	uint32_t windowHeight;
	bool recentlyCreated;
};
