#ifndef _PAUSEMENU_H
#define _PAUSEMENU_H

#include "../Screen.h"

class PauseMenu : public Screen
{

public:
	PauseMenu() {}

	~PauseMenu() {}
	PauseMenu(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input);
	void Update(double time);
	void Render();
	virtual MenuScreens GetTargetMenu() {
		switch (m_currentFont)
		{
		case 0:
			return GAME;
			break;
		case 1:
			return MENU;
			break;
		case 2:
			return OPTION;
			break;
		case 3:
			return EXIT;
			break;
		}
	}

private:
	const wstring m_resume = L"Resume";
	const wstring m_menu = L"Main menu";
	const wstring m_options = L"Options";
	const wstring m_exit = L"Quit";
	bool m_keyDown = false;
	Font m_choices[4];
	int m_currentFont;
};


#endif
