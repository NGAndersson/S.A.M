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
	delete m_endScreen;
	delete m_songSelect;
}

void ScreenManager::Update(double time)
{
	//Checks input depending on what screen the user is in.
	switch (m_current)
	{
	case MENU_DEFAULT:
		break;
	case MENU:
		//Startscreen
		m_screenMenu->Update(time);
		if (m_input->CheckReturn())
		{
			m_current =	m_screenMenu->GetTargetMenu();
			if (m_current == GAME)
			{
				m_gameOngoing = true;
		}
		}
		break;
	case GAME:
		//Game
		m_screenGame->Update(time);
		if (m_stats->GetLives() == 0)
		{
			m_current = ENDSCREEN;
		}
		break;
	case 3:
		//HighScore
		m_screenHighScore->Update(time);
		break;
	case 4:
		//Options
		m_screenOptions->Update();
		if (m_input->CheckReturn())
		{
			m_current = m_screenPause->GetTargetMenu();
		}
		break;
	case PAUSE:
		//Pause
		m_screenPause->Update(time);
		if (m_input->CheckReturn())
		{
			m_current = m_screenPause->GetTargetMenu();
			if (m_current == MENU)
			{
				m_gameOngoing = false;
			}
		}
		break;
	case 6:
		//Endscreen
		m_endScreen->Update(time);
		if (m_input->CheckReturn())
		{
			m_current = m_screenPause->GetTargetMenu();
		}
		break;
	case SONGSELECT:
		m_songSelect->Update(time);
		if (m_input->CheckReturn())
		{
			//m_current = GAME;
		}
	case EXIT:
		//Do nothing will exit when going to update in game class
			break;
	default:
		break;
	}
}

void ScreenManager::InitializeScreen(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, Stats* stats, SoundManager* soundManager)
{
	m_stats = stats;
	//Starting all the otherClasses etc..

	//Current screen is startscreen
	m_current = MENU;
	//m_Current = USERINTERFACE;
	//Create Modelhandlers...
	m_input = input;
	m_screenMenu = new StartMenu(Device, DeviceContext, ScreenHeight, ScreenWidth, input);
	m_screenGame = new UI(Device, DeviceContext, ScreenHeight, ScreenWidth, input, stats);
	m_screenPause = new PauseMenu(Device, DeviceContext, ScreenHeight, ScreenWidth, input);
	m_screenHighScore = new HighScoreMenu(Device, DeviceContext, ScreenHeight, ScreenWidth, input);
	m_endScreen = new EndScreen(Device, DeviceContext, ScreenHeight, ScreenWidth, input, stats);
	m_songSelect = new SongSelect(Device, DeviceContext, ScreenHeight, ScreenWidth, input, stats, soundManager);
	m_screenOptions = new OptionsMenu(Device, DeviceContext, ScreenHeight, ScreenWidth, input);
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
		m_screenHighScore->Render();
		break;
	case 4:
		//Options
		m_screenOptions->Render();
		break;
	case 5:
		//Pause
		m_screenPause->Render();
		break;
	case 6:
		//Endscreen
		m_endScreen->Render();
		break;
	case SONGSELECT:
		m_songSelect->Render();
	default:
		break;
	}
}
