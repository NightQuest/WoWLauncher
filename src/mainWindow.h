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
	LRESULT onCTLColorStatic(HDC hdc, HWND hwnd) override;

	bool create(const std::wstring& title, uint32_t width, uint32_t height) override;

	LRESULT onFirstShow(BOOL beingShown, UINT status);

private:
	std::wstring className;
	uint32_t windowWidth;
	uint32_t windowHeight;
	bool recentlyCreated;

	std::unordered_map<DWORD, ChildWindow*> children;
};

enum IDCs
{
	IDC_MAIN_STATUS = 100,
	IDC_SERVER_LISTBOX,
	IDC_NAME_EDIT,
	IDC_NAME_STATIC,
	IDC_INSTALL_EDIT,
	IDC_INSTALL_STATIC,
	IDC_INSTALL_BUTTON,
	IDC_USELAUNCHER_CHECKBOX,
	IDC_COMMANDLINE_EDIT,
	IDC_COMMANDLINE_STATIC,
	IDC_SETREALMLIST_CHECKBOX,
	IDC_REALM_EDIT,
	IDC_REALM_STATIC,
	IDC_DESCRIPTION_EDIT,
	IDC_DESCRIPTION_STATIC,
	IDC_NEW_BUTTON,
	IDC_DELETE_BUTTON,
	IDC_SAVE_BUTTON,
	IDC_LAUNCH_BUTTON,

	IDC_MAX
};
