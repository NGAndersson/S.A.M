#ifndef _PAUSEMENU_H
#define _PAUSEMENU_H

#include "../Screen.h"

class PauseMenu : public Screen
{

public:
	PauseMenu() {}

	~PauseMenu() {}
	PauseMenu(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input);
	void Update();
	void Render();
	virtual MenuScreens GetTargetMenu() {
		switch (m_currentFont)
		{
		case 0:
			return GAME;
			break;
		case 1:
			return OPTION;
			break;
		case 2:
			return HIGHSCORE;
			break;
		case 3:
			return ENDSCREEN;
			break;
		}
	}

private:
	const wchar_t* m_resume = L"Resume";
	const wchar_t* m_options = L"Options";
	const wchar_t* m_highScore = L"HighScore";
	const wchar_t* m_exit = L"Quit";
	bool m_keyDown = false;
	Font m_choices[4];

	int m_currentFont;
};


#endif
