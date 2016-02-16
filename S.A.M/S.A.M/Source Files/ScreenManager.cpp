#include "ScreenManager.h"
ScreenManager::ScreenManager()
{

}

ScreenManager::~ScreenManager()
{
	delete m_screenGame;
	delete m_screenMenu;
	delete m_screenOptions;
	delete m_screenPause;
	delete m_screenHighScore;
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
		m_screenGame->Update();
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
	case ENDSCREEN:
		//Endscreen
		m_endScreen->Update();
		if (m_input->CheckReturn())
		{
			m_current = m_endScreen->GetTargetMenu();
		}
		break;
	default:
		break;
	}


}

void ScreenManager::InitializeScreen(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input,Stats* stats)
{
	//Starting all the otherClasses etc..

	//Current screen is startscreen
	m_current = ENDSCREEN;
	//m_Current = USERINTERFACE;
	//Create Modelhandlers...
	m_input = input;
	m_screenMenu = new StartMenu(Device, DeviceContext, ScreenHeight, ScreenWidth, input);
	m_screenGame = new UI(Device, DeviceContext, ScreenHeight, ScreenWidth, input, stats);
	m_endScreen = new EndScreen(Device, DeviceContext, ScreenHeight, ScreenWidth, input, stats);
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
		m_screenGame->Render();
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
	case ENDSCREEN:
		//Endscreen
		m_endScreen->Render();
		break;
	default:
		break;
	}
}



