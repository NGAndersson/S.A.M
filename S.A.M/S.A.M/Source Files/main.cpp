#include "Graphics/Display.h"
#include "Game.h"
#include "Audio/SoundManager.h"
#include "Gamelogic/Input.h"


// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand(int(time(0)));

	//FOR DEBUGGING PURPOSE
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(647128);

	//Create, initialize and START the game
	Game _Game;
//	_Game.InitGame(&_input, &_display);
	WPARAM test = _Game.MainLoop(hInstance,hPrevInstance,lpCmdLine,nCmdShow);
	return test;
}