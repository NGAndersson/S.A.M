#include "ScreenManager.h"
ScreenManager::ScreenManager()
{

}

ScreenManager::~ScreenManager()
{

}

void ScreenManager::Update(double time)
{

	//Checks input depending on what screen the user is in.
	switch (m_Current)
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


}

void ScreenManager::InitializeScreen(Input* Input)
{
	//Starting all the otherClasses etc..

	//Current screen is startscreen
	m_Current = START;
	//Create Modelhandlers...
}

void ScreenManager::Render()
{
	//Doing the rendering.....

}

