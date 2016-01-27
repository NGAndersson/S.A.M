#include "SoundManager.h"
#include "Display.h"
#include <iostream>	//Not needed

SoundManager sm;

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Display display(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	HWND hWnd = display.GethWnd();
	// display the window on the screen
	ShowWindow(hWnd, nCmdShow);

	// set up and initialize Direct3D
	display.InitD3D(hWnd);

	// enter the main loop:

	// this struct holds Windows event messages
	MSG msg;

	// Enter the infinite message loop
	while (TRUE)
	{
		// Check to see if any messages are waiting in the queue
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// translate keystroke messages into the right format
			TranslateMessage(&msg);

			// send the message to the WindowProc function
			DispatchMessage(&msg);
		}

		// If the message is WM_QUIT, exit the while loop
		if (msg.message == WM_QUIT)
			break;

		//Starts the current 3D scene
		display.BeginFrame();

		//Enter call to Game here
		//...
		sm.LoadSound("Resources/wave.mp3", "wave", LOAD_MEMORY);
		sm.PlayOneShotSound("wave");

		std::cin.ignore();

		//Ends the current 3D scene
		display.EndFrame();
	}

	display.CleanD3D();
	// return this part of the WM_QUIT message to Windows
	return msg.wParam;
}