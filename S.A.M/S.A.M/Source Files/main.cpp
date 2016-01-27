#include "Display.h"
#include "Game.h"
#include "SoundManager.h"
#include "Input.h"

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Display display(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	HWND hWnd = display.GethWnd();
	// display the window on the screen
	ShowWindow(hWnd, nCmdShow);
	
	//Create and initialize Input


	//Create, initialize and START the game
	Game _Game;
	_Game.InitGame(&_input, &display);
	return _Game.MainLoop();
}