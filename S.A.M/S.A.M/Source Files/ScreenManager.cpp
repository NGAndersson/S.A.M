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
	delete m_endScreen;
	delete m_songSelect;
}

newOptions ScreenManager::Update(double time)
{

	//Checks input depending on what screen the user is in.
	switch (m_current)
	{
	case MENU_DEFAULT:
		break;
	case MENU:
		//Startscreen
		m_screenMenu->Update(time);
		if (m_input->CheckReturn() && !m_keyDown)
		{
			m_keyDown = true;
			m_current =	m_screenMenu->GetTargetMenu();
		}
		else if (!m_input->CheckReturn())
		{
			m_keyDown = false;
		}
		break;
	case GAME:
		//Game
		m_screenGame->Update(time);
		if (m_stats->GetLives() == 0)
		{
			m_current = ENDSCREEN;
			m_soundManager->PauseMusic();
			//m_stats->SavePoints()
			//m_stats->ResetPointsAndLives()
			//ResetGame()
		}
		break;
	case 3:
		//HighScore
		//m_screenHighScore->Update(time); Doesn't need to actually update anything
		if (m_input->CheckEsc() && !m_keyDown)
		{
			m_keyDown = true;
			m_current = SONGSELECT;
			delete m_screenHighScore;			//Highscore screen has served its purpose and can be deleted, will be remade when going back from songselect
		}
		else if (!m_input->CheckReturn())
			m_keyDown = false;
		break;
	case OPTION:
		//Options
		m_screenOptions->UpdateOP(time);
		m_current = m_screenOptions->GetTargetMenu();
		if (m_current == MENU || m_current == PAUSE)
			m_screenOptions->Reset();
		break;
	case PAUSE:
		//Pause
		m_screenPause->Update(time);
		if (m_input->CheckReturn() && !m_keyDown)
		{
			m_current = m_screenPause->GetTargetMenu();
			m_keyDown = true;
		}	
		if (m_current == MENU)
		{
			m_gameOngoing = false;
			m_stats->ResetBeat();
		}
		else if (!m_input->CheckReturn())
			m_keyDown = false;
		
		break;
	case ENDSCREEN:
		//Endscreen
		m_endScreen->Update(time);
		if (m_input->CheckReturn() && !m_keyDown)
		{
			m_stats->SaveScore(m_endScreen->GetPlayerName());
			m_keyDown = true;
			m_current = HIGHSCORE;
			m_screenHighScore = new HighScoreMenu(m_device, m_deviceContext, m_screenHeight, m_screenWidth, m_input, m_stats); //Make new song-specific highscore screen
		}
		else if (!m_input->CheckReturn())
			m_keyDown = false;
		break;
	case SONGSELECT:
	{
		m_songSelect->Update(time);

		InputType _leftCheck = m_input->CheckKeyBoardInput();
		if (_leftCheck == INPUT_MOVE_LEFT)			//Check right arrow to move to highscore
		{
			m_soundManager->StopMusic();
			m_keyDown = true;
			m_current = HIGHSCORE;
			m_screenHighScore = new HighScoreMenu(m_device, m_deviceContext, m_screenHeight, m_screenWidth, m_input, m_stats); //Make new song-specific highscore screen
		}
		else if (m_input->CheckReturn() && !m_keyDown)		//Continue to GAME when pressing enter
		{
			m_keyDown = true;
			m_gameOngoing = true;
			m_soundManager->StopMusic();
			m_current = GAME;
		}
		else if (m_input->CheckEsc() && !m_keyDown)		//Go back to main menu on ESC
		{
			m_keyDown = true;
			m_soundManager->StopMusic();
			m_current = MENU;
		}
		else if (!m_input->CheckReturn() && !m_input->CheckEsc())
			m_keyDown = false;
	}
	break;
	case NEWRES:
		m_screenOptions->saveSettings();
		return NEW_RES;
		break;
	case EXIT:
		//Do nothing will exit when going to update in game class
			break;
	default:
		break;
	}
	return NO_NEW;
}

void ScreenManager::InitializeScreen(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, Stats* stats, SoundManager* soundManager)
{
	m_stats = stats;
	m_soundManager = soundManager;
	m_device = Device;
	m_deviceContext = DeviceContext;
	//Starting all the otherClasses etc..
	m_screenHeight = ScreenHeight;
	m_screenWidth = ScreenWidth;

	//Current screen is startscreen
	m_current = MENU;
	//m_Current = USERINTERFACE;
	//Create Modelhandlers...
	m_input = input;

	m_screenOptions = new OptionsMenu(Device, DeviceContext, ScreenHeight, ScreenWidth, input, soundManager);
	m_screenMenu = new StartMenu(Device, DeviceContext, ScreenHeight, ScreenWidth, input);
	m_screenGame = new UI(Device, DeviceContext, ScreenHeight, ScreenWidth, input, stats);
	m_screenPause = new PauseMenu(Device, DeviceContext, ScreenHeight, ScreenWidth, input);
	m_endScreen = new EndScreen(Device, DeviceContext, ScreenHeight, ScreenWidth, input, stats);
	m_songSelect = new SongSelect(Device, DeviceContext, ScreenHeight, ScreenWidth, input, stats, soundManager);

}

void ScreenManager::Render(int offset)
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
		m_screenGame->Render(offset);
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
	case ENDSCREEN:
		//Endscreen
		m_endScreen->Render();
		break;
	case SONGSELECT:
		m_songSelect->Render();
	default:
		break;
	}
}
