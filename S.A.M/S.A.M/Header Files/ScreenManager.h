#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "Gamelogic\Input.h"
#include "Graphics\ModelHandler.h"

enum EnumScreens { MENU, GAME, HIGHSCORE, OPTION, PAUSE, ENDSCREEN };

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
	void InitializeScreen(Input* input);
	//Rendercall
	void Render();
	
	//Returns the current screen
	EnumScreens GetCurrentScreen() { return m_Current; }

//----------------------------Attributes----------------------------------------
private:
	//Current status.
	EnumScreens m_Current;
	//Different screens

	//input
	Input* m_input;

	//Modelhandler

	//ModelHandler m_uI;
	//ModelHandler m_highScore;
	//ModelHandler m_options;
	//ModelHandler m_pause;
	//ModelHandler m_start;
	//ModelHandler m_endScreen;

};

#endif
