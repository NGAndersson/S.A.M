#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "Gamelogic\Input.h"
#include "Graphics\ModelHandler.h"
#include "Gamelogic\Stats.h"

#include "Screens\Screen.h"
#include "Screens\Menu\StartMenu.h"
#include "Screens\Menu\UI.h"
#include "Screens\EndScreen.h"

class ScreenManager
{
//----------------------------Functions----------------------------------------
public:
	//Destructor and Constructor
	ScreenManager();
	~ScreenManager();
	//Uppdate screens
	void Update();
	//Initializing the screen manager
	void InitializeScreen(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input,Stats* stats);
	//Rendercall
	void Render();
	//Returns the current screen
	MenuScreens GetCurrentScreen() { return m_current; }

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

	//input
	Input* m_input;


};

#endif
