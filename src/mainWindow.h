#pragma once

class mainWindow : public Window
{
public:
	mainWindow() = delete;
	mainWindow(const std::wstring& className);
	~mainWindow() override;

	bool create(const std::wstring& title, uint32_t width, uint32_t height) override;

private:
	std::wstring className;
};
