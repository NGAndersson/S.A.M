#ifndef _OPTIONSMENU_H
#define _OPTIONSMENU_H

#include "../Screen.h"
#include "DirectXMath.h"

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
	const wchar_t* m_option1 = L"Resolution";
	const wchar_t* m_option2 = L"Volume";
	bool m_keyDown = false;
	Font m_choices[3];

	Font m_options[2];

	int m_currentFont;
};


#endif