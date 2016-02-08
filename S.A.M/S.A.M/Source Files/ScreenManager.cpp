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
		//Start Menu
		m_menuScreen.Update();
		break;
	case 1:
		//Game

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
	m_Current = MENU;
	//m_Current = USERINTERFACE;
	//Create Modelhandlers...
}

void ScreenManager::Render(ID3D11Device *device, ID3D11DeviceContext *deviceContext)
{
	//Renders different things depending on what screen the user is in.
	switch (m_Current)
	{
	case 0:
		//Start Menu
		m_menuScreen.Render(device, deviceContext);
		break;
	case 1:
		//Game

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



