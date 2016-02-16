#ifndef _OPTIONSMENU_H
#define _OPTIONSMENU_H

#include "../Screen.h"

class OptionsMenu : public Screen
{

public:
	OptionsMenu() {}

	~OptionsMenu() {}
	OptionsMenu(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input);
	void Update();
	void Render();
	virtual MenuScreens GetTargetMenu() {
		switch (m_currentFont)
		{
		case 0:
			return MENU;
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
	const wchar_t* m_start = L"";
	const wchar_t* m_options = L"";
	const wchar_t* m_highScore = L"";
	const wchar_t* m_exit = L"";
	bool m_keyDown = false;
	Font m_choices[4];

	int m_currentFont;
};


#endif