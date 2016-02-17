#ifndef _HIGHSCOREMENU_H
#define _HIGHSCOREMENU_H

#include "../Screen.h"

class HighScoreMenu : public Screen
{

public:
	HighScoreMenu() {}

	~HighScoreMenu() {}
	HighScoreMenu(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input);
	void Update();
	void Render();
	virtual MenuScreens GetTargetMenu() {
		switch (m_currentFont)
		{
		case 0:
			return GAME;
			break;
		case 1:
			return ENDSCREEN;
			break;
		}
	}

private:
	const wstring m_start = L"Main Menu";
	const wstring m_exit = L"Quit";
	bool m_keyDown = false;
	Font m_choices[2];

	int m_currentFont;
};


#endif
