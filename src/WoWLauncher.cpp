#include "preCompiled.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	// Create our window
	mainWindow window(L"WoWLauncherApp");
	if( !window.create(L"WoW Launcher", 422, 405) )
	{
		MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONERROR | MB_OK);
		return 0;
	}

	// Display our window
	window.Show(nShowCmd);
	window.Update();

	MSG msg;
	BOOL bRet;
	while( (bRet = GetMessage(&msg, 0, 0, 0)) != 0 )
	{
		if( bRet == -1 )
			break;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
}
