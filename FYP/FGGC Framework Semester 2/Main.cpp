#include "Application.h"

void GameLoopDelay(const float frameStartTime)
{
	const float currentFrameTime = GetTickCount();

	const float frameProcessingTime = currentFrameTime - frameStartTime;

	if (frameProcessingTime < 1.f/60.f)
	{
		//  delay so that time interval between adjacent frames is equal to preset value
		Sleep(float(1.f/60.f) - frameProcessingTime);
	}
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	AllocConsole();
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	Application * theApp = new Application();

	if (FAILED(theApp->Initialise(hInstance, nCmdShow)))
	{
		return -1;
	}

    // Main message loop
    MSG msg = {0};

    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
			bool handled = false;

			if (msg.message >= WM_KEYFIRST && msg.message <= WM_KEYLAST)
			{
				handled = theApp->HandleKeyboard(msg);
			}
			else if (WM_QUIT == msg.message)
				break;

			if (!handled)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
        else
        {
			const float frameStartTime = GetTickCount();

			if (GetAsyncKeyState(VK_ESCAPE))			
				break;
			
			theApp->Update();
            theApp->Draw();

			GameLoopDelay(frameStartTime);
        }
    }

	delete theApp;
	theApp = nullptr;

    return (int) msg.wParam;
}
