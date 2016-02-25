#include "Graphics/Display.h"
#include "Game.h"
#include "Audio/SoundManager.h"
#include "Gamelogic/Input.h"


// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand(int(time(0)));
	int _width = WIDTH;
	int _height = HEIGHT;
	Display _display(hInstance, hPrevInstance, lpCmdLine, nCmdShow, _width, _height);

	//FOR DEBUGGING PURPOSE
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(1612);

	//Create and initialize Input	
	HWND _hWnd = _display.GethWnd();
	Input _input;
	_input.Initialize(hInstance, _hWnd, _width, _height);

	//Create, initialize and START the game
	Game _Game;
	_Game.InitGame(&_input, &_display);
	WPARAM test = _Game.MainLoop();
	return test;
}