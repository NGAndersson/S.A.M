#ifndef _GAME_H_
#define _GAME_H_

#include "Display.h"
#include "SoundManager.h"
#include "ScreenManager.h"
#include "Input.h"
#include "Time.h"

class Game
{
private:
	void Update(double time);
	void Render();

public:
	Game();
	void InitGame(Input* input, Display* disp);
	WPARAM MainLoop();

private:
	SoundManager* m_soundManager;
	ScreenManager* m_screenManager;
	Input* m_input;
	Display* m_display;
	MSG m_winMSG;

public:
}

#endif 

