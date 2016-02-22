#ifndef _OPTIONSMENU_H
#define _OPTIONSMENU_H

#include "../Screen.h"
#include "DirectXMath.h"
#include "../../Audio/SoundManager.h"

enum Options { MUSICVOLUME, SHOTSVOLUME, RESOLUTION, KEYBINDING, APPLY, MAINMENU };

class OptionsMenu : public Screen
{

public:
	OptionsMenu() {
		delete m_choices;
		
	}

	~OptionsMenu() {}
	OptionsMenu(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, SoundManager* SoundManager);
	void Update(double time);
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
	wstring m_menu;
	wstring m_resolution;
	wstring m_volumeMusic;
	wstring m_volumeShots;
	wstring m_keyBindings;
	wstring m_apply;
	wstring m_res[4];

	bool m_keyDown = false;
	Font m_choices[6];
	SoundManager* m_soundManager;
	int m_currentFont,m_currentRes,m_currentMVol,m_currentSVol;
	int m_tempWidth[4], m_tempHeight[4];


};


#endif