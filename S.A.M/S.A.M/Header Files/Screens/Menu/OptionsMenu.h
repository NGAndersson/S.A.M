#ifndef _OPTIONSMENU_H
#define _OPTIONSMENU_H

#include "../Screen.h"
#include "DirectXMath.h"
#include "../../Audio/SoundManager.h"

enum Options { MUSICVOLUME, SHOTSVOLUME, RESOLUTION, KEYBINDING, APPLY, MAINMENU };
enum InKey {NOT_KEY,IN_KEY};
class OptionsMenu : public Screen
{

public:
	OptionsMenu() {
		delete m_choices;
		delete m_tempWidth;
		delete m_tempHeight;
		delete m_volym;
	}

	~OptionsMenu() {}
	OptionsMenu(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, SoundManager* SoundManager);
	void Update(double time);
	void Render();
	virtual MenuScreens GetTargetMenu() {
		if (m_doneOption)
			return MENU;
		else
			return OPTION;
	}
	void Reset() { m_doneOption = false; m_keyDown = true; m_currentFont = 0; }

private:
	void setUpdateKeys();
	void saveSettings();
	wstring m_menu;
	wstring m_resolution;
	wstring m_volumeMusic;
	wstring m_volumeEffect;
	wstring m_keyBin;
	wstring m_apply;
	wstring m_unBound;
	//Resolution
	wstring m_res[4];
	bool m_keyDown = false, m_doneOption = false, m_unBoundKey = false;
	//Choices for options
	Font m_choices[6];
	SoundManager* m_soundManager;
	//ints to check what shit we are on
	int m_currentFont,m_currentRes,m_currentMVol,m_currentSVol,m_currentKeyBinding;
	int m_tempWidth[4], m_tempHeight[4];
	int m_volym[10];
	//Shit for Keybindings
	wstring m_keys[9];
	Font m_keyChoice[9];
	int m_keyBindings[9];
	InKey m_ifKey;


};


#endif