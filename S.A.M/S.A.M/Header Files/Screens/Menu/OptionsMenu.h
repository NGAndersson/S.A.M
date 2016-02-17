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
		}
	}

private:
	const wchar_t* m_menu = L"Return to Menu";
	bool m_keyDown = false;
	Font m_choices[1];

	int m_currentFont;
};


#endif