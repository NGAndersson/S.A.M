#include "Game.h"

Game::Game()
{

}

Game::~Game()
{
	if (m_swapChain != nullptr)
	{
		m_swapChain->Release();
	}
	if (m_backbufferRTV != nullptr)
	{
		m_backbufferRTV->Release();
	}
	if (m_depthStencilView != nullptr)
	{
		m_depthStencilView->Release();
	}
	if (m_depthStencil != nullptr)
	{
		m_depthStencil->Release();
	}
	if (m_sampleState != nullptr)
	{
		m_sampleState->Release();
	}
	if (m_blendState != nullptr)
	{
		m_blendState->Release();
	}
	if (m_depthStencilState != nullptr)
	{
		m_depthStencilState->Release();
	}
	if (m_deviceContext != nullptr)
	{
		m_deviceContext->Release();
	}
	if (m_device != nullptr)
	{
		m_device->Release();
	}

	delete m_soundManager;
	m_soundManager = 0;
	delete m_screenManager;
	m_screenManager = 0;
	delete m_entityManager;
	m_entityManager = 0;
	delete m_display;
	m_display = 0;
	delete m_backgroundPartSys;
	delete m_statsManager;
	delete m_gaussianFilter;
	delete m_input;
	m_input = 0;
}

void Game::ReadOptions()
{
	std::fstream _file;
	_file.open("Options/Settings.txt");
	std::string _tempLine;
	char _key[100];
	char _value[100];
	if (_file.is_open())
	{
		while (getline(_file, _tempLine))
		{
			std::istringstream _ss(_tempLine);
			_ss.get(_key, 100, '|');
			_ss.ignore();
			if (_key[0] != '#')
			{
				_ss.get(_value, 100, '|');
				if (std::string(_key) == "ScreenHeight")
					m_height = atoi(_value);

				else if (std::string(_key) == "ScreenWidth")
					m_width = atoi(_value);

			}
		}
		_file.close();
	}
}

void Game::InitGame(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	ReadOptions();
	//Create inputclass
	m_display = new Display(hInstance, hPrevInstance, lpCmdLine, nCmdShow, m_width, m_height);


	HWND _hwnd = m_display->GethWnd();

	m_input = new Input();
	m_input->Initialize(hInstance, _hwnd);

	//Create and initialize device/devicecontext/swapchain/depthstenciel
	CreateDirect3DContext(_hwnd);

	//Create and initialize SoundManager
	m_soundManager = new SoundManager(0.5, 0.5);  //Initializes in constructor

	 //Initialize Stats manager
	m_statsManager = new Stats;

	//Create and initialize ScreenManager
	m_screenManager = new ScreenManager();
	m_screenManager->InitializeScreen(m_device, m_deviceContext,m_height,m_width, m_input, m_statsManager, m_soundManager);

	//Sets the viewport
	SetViewport();


	//Create and initialize EntityManager
	m_entityManager = new EntityManager;
	m_entityManager->Initialize(m_soundManager, m_input, m_device, m_deviceContext, m_statsManager);

	wstring _texName = L"Resources\\Models\\star3.jpg";

	m_backgroundPartSys = new SpacePart();
	m_backgroundPartSys->CreateBuffer(m_device, m_deviceContext, _texName);
	m_partShader.CreateShadersPosOnly(m_device, "Shaders\\PartVS.hlsl", "Shaders\\PartGS.hlsl", "Shaders\\PartPS.hlsl");;
	m_glowshader.CreateShadersCompute(m_device, "Shaders\\ComputeShader.hlsl");

	//Init defered buffer and render
	m_deferredBuffer.Initialize(m_device, m_width, m_height);

	m_deferredRender.InitializeShader(m_device);
	m_deferredRender.InitializeBufferString(m_device);

	m_gaussianFilter = new GaussianBlur(m_device, m_deviceContext, &m_glowshader, m_width, m_height);
}


void Game::InitGameRedo(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HRESULT _hr;
	ReadOptions();
	ID3D11RenderTargetView* _nullViews[] = { nullptr };
	m_deviceContext->OMSetRenderTargets(ARRAYSIZE(_nullViews), _nullViews, nullptr);
	m_backbufferRTV->Release();
	m_depthStencil->Release();
	m_depthStencilView->Release();
	//Resize for the new resolution
	DXGI_MODE_DESC _newRes;
	_newRes.Height = m_height;
	_newRes.Width = m_width;

	m_swapChain->ResizeBuffers(1, m_width, m_height, DXGI_FORMAT_R8G8B8A8_UNORM, NULL);
	m_swapChain->ResizeTarget(&_newRes);

	//Create and initialize ScreenManager
	m_screenManager = new ScreenManager();
	m_screenManager->InitializeScreen(m_device, m_deviceContext,m_height,m_width, m_input, m_statsManager, m_soundManager);

	ID3D11Texture2D* _backBuffer = nullptr;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&_backBuffer);

	// use the back buffer address to create the render target
	_hr = m_device->CreateRenderTargetView(_backBuffer, NULL, &m_backbufferRTV);
	_backBuffer->Release();

	//Sets the viewport
	SetViewport();

	DepthStencilInitialicer();
	m_deferredBuffer.~DeferredBuffer();
	//Init defered buffer and render
	m_deferredBuffer.Initialize(m_device, m_width, m_height);//could be this little bastard 

	m_gaussianFilter = new GaussianBlur(m_device, m_deviceContext, &m_glowshader, m_width, m_height);
}

WPARAM Game::MainLoop(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Timer _time;
	static float _frameTime = 0.f;
	_time.StartTime();
	_time.TimeCheck();

	InitGame(hInstance,hPrevInstance,lpCmdLine,nCmdShow);//initialize the things that does not need ScreenWidh/m_height

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
		m_input->Update();
		//Update FMOD
		m_soundManager->Update();

		//Get Time
		float time = _time.TimeCheck();
		_frameTime += time;
		CheckInput();

		//Call update functions
		Update(time, hInstance, hPrevInstance, lpCmdLine, nCmdShow);

		//Call Render Functions
		if (_frameTime*1000.f >= 16.6f) {
			Render();
			m_swapChain->Present(0, 0);
			_frameTime = 0.f;
		}
	}

}

void Game::Update(double time, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	static MenuScreens _prevScreen;

	if( NEW_RES == m_screenManager->Update(time))
	{
		delete m_screenManager;
		delete m_gaussianFilter;

		InitGameRedo(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	}
	else
	{

	if ((m_screenManager->GetCurrentScreen() == PAUSE && _prevScreen == GAME) || m_screenManager->GetCurrentScreen() == GAME && _prevScreen == PAUSE)	//When switching from game to pause or vice versa, pause/resume the music
		m_soundManager->PauseMusic();

	if (m_screenManager->GetCurrentScreen() == GAME)
	{
		if (_prevScreen == SONGSELECT)
		{
			m_entityManager->Reset();
			m_entityManager->InitMusic(m_screenManager->GetSelectedSongFile());
		}
		m_entityManager->Update(time);
	}

	if (m_screenManager->GetCurrentScreen() == EXIT)
	{
		PostQuitMessage(0);
	}

	if (m_screenManager->GetCurrentScreen() == HIGHSCORE && _prevScreen == ENDSCREEN)
	{
		m_entityManager->Reset();
	}

	if (m_screenManager->GetCurrentScreen() == MENU && _prevScreen == PAUSE)
	{
		m_entityManager->Reset();
	}

	_prevScreen = m_screenManager->GetCurrentScreen();
	}

	//Updates space
	m_backgroundPartSys->Update(m_deviceContext, time, 40);

}

void Game::Render()
{

	// clear the back buffer to a deep blue
	float _clearColor[] = { 0, 0, 0, 1 };
	m_deviceContext->ClearRenderTargetView(m_backbufferRTV, _clearColor);
	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	m_deviceContext->OMSetRenderTargets(1, &m_backbufferRTV, m_depthStencilView);

	//if(m_screenManager->GetCurrentScreen() == USERINTERFACE)
	// Render Entity Manager
	m_deferredBuffer.SetCleanResource(m_deviceContext);
	m_deferredBuffer.ClearRenderTargets(m_deviceContext);
	m_deferredBuffer.SetRenderTargets(m_deviceContext);
	m_partShader.SetShaders(m_deviceContext);
	m_backgroundPartSys->Render(m_deviceContext);
	if (m_screenManager->GetGameState() == true/*m_screenManager->GetCurrentScreen() == GAME || m_screenManager->GetCurrentScreen()==PAUSE*/)
	{
		m_entityManager->Render();
	}

	m_deviceContext->OMSetRenderTargets(1, &m_backbufferRTV, m_depthStencilView);
	m_deferredBuffer.SetShaderResource(m_deviceContext);
	m_gaussianFilter->Blur(m_device, m_deviceContext, 4, m_deferredBuffer.GetResourceView(4));
	m_deferredRender.Render(m_deviceContext);
	
	m_screenManager->Render(m_entityManager->GetOffset());

	//spritbatch goes retard and setts rendershit to 2D things... This is the reset for those things 
	float _blendF[4] = { 0.0f,0.0f,0.0f,0.0f };
	UINT _sampleM = 0xffffffff;
	m_deviceContext->OMSetBlendState(m_blendState,_blendF,_sampleM);

	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 0);

}

void Game::CheckInput()
{
	//InputType _returnInput = m_input->CheckKeyBoardInput();
	if (m_input->CheckEsc()) 
	{
		switch (m_screenManager->GetCurrentScreen())
		{
		case MENU:
			break;
		case GAME:
			m_screenManager->SetCurrentScreen(PAUSE);
			break;
		}
	}
}

void Game::SetViewport()
{
	D3D11_VIEWPORT _viewport;
	_viewport.Width = (float)m_width;
	_viewport.Height = (float)m_height;
	_viewport.MinDepth = 0.0f;
	_viewport.MaxDepth = 1.0f;
	_viewport.TopLeftX = 0;
	_viewport.TopLeftY = 0;
	m_deviceContext->RSSetViewports(1, &_viewport);
}

HRESULT Game::CreateDirect3DContext(HWND wndHandle)
{
	// create a struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC _swapChainDesc;

	// clear out the struct for use
	ZeroMemory(&_swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	_swapChainDesc.BufferCount = 1;                                    // one back buffer
	_swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	_swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	_swapChainDesc.OutputWindow = wndHandle;                           // the window to be used
	_swapChainDesc.SampleDesc.Count = 1;                               // how many multisamples
	_swapChainDesc.Windowed = TRUE;                                    // windowed/full-screen mode

															// create a device, device context and swap chain using the information in the scd struct
	HRESULT _hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&_swapChainDesc,
		&m_swapChain,
		&m_device,
		NULL,
		&m_deviceContext);

	

	if (SUCCEEDED(_hr))
	{
		_hr = DepthStencilInitialicer(); //skapar depthstencil/desc 

		// get the address of the back buffer
		ID3D11Texture2D* _backBuffer = nullptr;
		m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&_backBuffer);

		// use the back buffer address to create the render target
		_hr = m_device->CreateRenderTargetView(_backBuffer, NULL, &m_backbufferRTV);
		_backBuffer->Release();

		// set the render target as the back buffer
		m_deviceContext->OMSetRenderTargets(1, &m_backbufferRTV, m_depthStencilView);

		// description for sampler
		D3D11_SAMPLER_DESC samplDesc;
		ZeroMemory(&samplDesc, sizeof(D3D11_SAMPLER_DESC));

		samplDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplDesc.MinLOD = 0;
		samplDesc.MaxLOD = D3D11_FLOAT32_MAX;

		// create the sampler
		_hr = m_device->CreateSamplerState(&samplDesc, &m_sampleState);
		//Set the sampler state
		m_deviceContext->PSSetSamplers(0, 1, &m_sampleState);
	}

	
	return _hr;
}

HRESULT Game::DepthStencilInitialicer()
{
	HRESULT _hr;

	//create the depth stencil
	D3D11_TEXTURE2D_DESC _descDepth;
	_descDepth.Width = m_width;
	_descDepth.Height = m_height;
	_descDepth.MipLevels = 1;
	_descDepth.ArraySize = 1;
	_descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	_descDepth.SampleDesc.Count = 1;
	_descDepth.SampleDesc.Quality = 0;
	_descDepth.Usage = D3D11_USAGE_DEFAULT;
	_descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	_descDepth.CPUAccessFlags = 0;
	_descDepth.MiscFlags = 0;
	_hr = m_device->CreateTexture2D(&_descDepth, NULL, &m_depthStencil);
	if (SUCCEEDED(_hr))
	{
		_hr = m_device->CreateDepthStencilView(m_depthStencil, NULL, &m_depthStencilView);
	}
	return _hr;
}
