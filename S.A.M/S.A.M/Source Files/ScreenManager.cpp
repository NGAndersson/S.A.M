#include "ScreenManager.h"
ScreenManager::ScreenManager()
{

}

ScreenManager::~ScreenManager()
{

}

void ScreenManager::Uppdate(int CurrentScreen)
{

	//Checks input depending on what screen the user is in.
	switch (CurrentScreen)
	{
	case 0:
		//Startscreen

		break;
	case 1:
		//Userinterface

		break;
	case 2:
		//HighScore

		break;
	case 3:
		//Options

		break;
	case 4:
		//Pause

		break;
	case 5:
		//Endscreen

		break;
	default:
		break;
	}

	mCurrent = CurrentScreen;


}

void ScreenManager::InitializeScreen()
{
	//Starting all the otherClasses etc..

	//Current screen is startscreen
	mCurrent = 0;

}

void ScreenManager::Render()
{
	//Doing the rendering.....

}

