#ifndef _STARTMENU_H
#define _STARTMENU_H

#include "../Screen.h"

class StartMenu : public Screen
{
public:
	StartMenu(){}
	~StartMenu(){}
	StartMenu(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input);
	void Update(double time);
	void Render();
	virtual MenuScreens GetTargetMenu() { 
		switch (m_currentFont)
		{
		case 0:
			return SONGSELECT;
			break;
		case 1:
			return OPTION;
			break;
		case 2:
			return HIGHSCORE;
			break;
		case 3:
			return EXIT;
			break;
		}
	}

private:
	wstring m_start = L"StartGame";
	wstring m_options = L"Options";
	wstring m_highScore = L"HighScore";
	wstring m_exit = L"Quit";
	bool m_keyDown = false;
	Font m_choices[4];

	int m_currentFont;
};


#endif
