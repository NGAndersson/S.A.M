#include "Game.h"

Game::Game()
{
}

void Game::InitGame(Input* input, Display* disp)
{
	m_input = input;
	m_display = disp;


	//Create and initialize SoundManager
	m_soundManager = new SoundManager;  //Initializes in constructor

	//FUN STUFF! REMOVE!
	m_soundManager->LoadSound("Resources/wave.mp3", "wave", "music", LOAD_STREAM);
	m_soundManager->LoadSound("Resources/Song.mp3", "gangnam", "music", LOAD_STREAM);
	m_soundManager->PlayOneShotSound("music", 0.5f);
	m_soundManager->PauseSound("music");


	//Create and initialize ScreenManager
	m_screenManager = new ScreenManager;
	m_screenManager->InitializeScreen();

	//Create and initialize EntityManager
}

WPARAM Game::MainLoop()
{
	Timer _time;
	_time.StartTime();

	while (TRUE) {
		// Check to see if any messages are waiting in the queue
		while (PeekMessage(&m_winMSG, NULL, 0, 0, PM_REMOVE))
		{
			// translate keystroke messages into the right format
			TranslateMessage(&m_winMSG);

			// send the message to the WindowProc function
			DispatchMessage(&m_winMSG);
		}

		// If the message is WM_QUIT, exit the while loop
		if (m_winMSG.message == WM_QUIT)
			return m_winMSG.wParam;


		//Get Time
		//time = Time.GetTime() ?

		CheckInput();

		//Call update functions
		Update(_time.TimeCheck());

		//Call Render Functions
		Render();
	}
}

void Game::Update(double time)
{
	m_screenManager->Update(time);
	//if(m_screenManager->GetCurrentScreen() == USERINTERFACE)
	// Update Entity Manager
}

void Game::Render()
{
	m_screenManager->Render();
	//if(m_screenManager->GetCurrentScreen() == USERINTERFACE)
	// Render Entity Manager
}

void Game::CheckInput()
{
	double haj = 0;
	InputType _returnInput = m_input->CheckKeyBoardInput(haj);
	if (_returnInput & INPUT_ESC)
		exit(0);
	m_input->CheckMouseInput(haj);
}
