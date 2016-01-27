#include "Display.h"
#include "Game.h"
#include "SoundManager.h"
#include "Input.h"

#define WIDTH 1080;
#define HEIGHT 720;

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int _width = WIDTH;
	int _height = HEIGHT;
	Display display(hInstance, hPrevInstance, lpCmdLine, nCmdShow, _width, _height);
	HWND hWnd = display.GethWnd();
	// display the window on the screen
	ShowWindow(hWnd, nCmdShow);
	
	//Create and initialize Input
	Input _input;
	_input.Initialize(hInstance, hWnd, _width, _height);

	//Create, initialize and START the game
	Game _Game;
	_Game.InitGame(&_input, &display);
	WPARAM test = _Game.MainLoop();
	return test;
}