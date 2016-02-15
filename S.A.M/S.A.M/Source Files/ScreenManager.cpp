#include "ScreenManager.h"
ScreenManager::ScreenManager()
{

}

ScreenManager::~ScreenManager()
{
	
	delete m_screenMenu;

}

void ScreenManager::Update( )
{

	//Checks input depending on what screen the user is in.




	switch (m_current)
	{
	case MENU_DEFAULT:
			break;
	case MENU:
		//Startscreen
		m_screenMenu->Update();
		if (m_input->CheckReturn())
		{
			m_current =	m_screenMenu->GetTargetMenu();
		}
		break;
	case GAME:
		//Game

		break;
	case 3:
		//HighScore

		break;
	case 4:
		//Options

		break;
	case 5:
		//Pause

		break;
	case 6:
		//Endscreen

		break;
	default:
		break;
	}


}

void ScreenManager::InitializeScreen(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input)
{
	//Starting all the otherClasses etc..

	//Current screen is startscreen
	m_current = MENU;
	//m_Current = USERINTERFACE;
	//Create Modelhandlers...
	m_input = input;
	m_screenMenu = new StartMenu(Device, DeviceContext, ScreenHeight, ScreenWidth, input);
}

void ScreenManager::Render()
{
	//Renders different things depending on what screen the user is in.
	switch (m_current)
	{
	case MENU_DEFAULT:
		
		break;
	case MENU:
		//StartMenu
		m_screenMenu->Render();
		break;
	case GAME:
		//Userinterface

		break;
	case 3:
		//HighScore

		break;
	case 4:
		//Options

		break;
	case 5:
		//Pause

		break;
	case 6:
		//Endscreen

		break;
	default:
		break;
	}
}



