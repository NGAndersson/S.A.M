#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "Gamelogic\Input.h"
#include "Graphics\ModelHandler.h"
#include "Gamelogic\Stats.h"
#include "Audio\SoundManager.h"

#include "Screens\Screen.h"
#include "Screens\Menu\StartMenu.h"
#include "Screens\Menu\UI.h"
#include "Screens\Menu\PauseMenu.h"
#include "Screens\Menu\HighscoreMenu.h"
#include "Screens\EndScreen.h"
#include "Screens\Menu\OptionsMenu.h"
#include "Screens\Menu\SongSelect.h"

class ScreenManager
{
//----------------------------Functions----------------------------------------
public:
	//Destructor and Constructor
	ScreenManager();
	~ScreenManager();
	//Uppdate screens
	void Update(double time);
	//Initializing the screen manager
	void InitializeScreen(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input,Stats* stats, SoundManager* soundManager);
	//Rendercall
	void Render();
	//Returns the current screen
	MenuScreens GetCurrentScreen() { return m_current; }
	bool GetGameState() { return m_gameOngoing; }
	void SetCurrentScreenPAUSE() { m_current = PAUSE; }
	void SetCurrentScreenQUIT() { m_current = EXIT;}
	string GetSelectedSongFile() { return m_songSelect->GetSelectedSongFile(); }
//----------------------------Attributes----------------------------------------
private:
	//Current status.
	MenuScreens m_current;
	//Different screens
	Screen* m_screenGame;
	Screen* m_screenMenu;
	Screen* m_screenOptions;
	Screen* m_screenPause;
	Screen* m_screenHighScore;
	Screen* m_endScreen;
	Screen* m_songSelect;
	Stats* m_stats;
	SoundManager* m_soundManager;
	bool m_keyDown = false, m_gameOngoing = false;
	//input
	Input* m_input;

};

#endif
