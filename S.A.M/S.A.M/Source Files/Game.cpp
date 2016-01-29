#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
	if (m_deviceContext)
	{
		m_deviceContext->Release();
	}
	if (m_device)
	{
		m_device->Release();
	}
	if (m_swapChain)
	{
		m_swapChain->Release();
	}
	if (m_backbufferRTV)
	{
		m_backbufferRTV->Release();
	}
	if (m_depthStencilView)
	{
		m_depthStencilView->Release();
	}
	if (m_depthStencil)
	{
		m_depthStencil->Release();
	}
}

void Game::InitGame(Input* input, Display* disp)
{
	m_input = input;
	m_display = disp;


	//Create and initialize SoundManager
	m_soundManager = new SoundManager;  //Initializes in constructor

	//Create and initialize device/devicecontext/swapchain/depthstenciel
	CreateDirect3DContext(disp->GethWnd());

	//Sets the viewport
	SetViewport();

	//FUN STUFF! REMOVE!
	//m_soundManager->LoadSound("Resources/wave.mp3", "wave", "music", LOAD_STREAM);
	//m_soundManager->LoadSound("Resources/Song.mp3", "gangnam", "music", LOAD_STREAM);
	m_soundManager->LoadSound("Resources/ExitThePremises.mp3", "song", "music", LOAD_STREAM);
	m_soundManager->PlayOneShotSound("music", 0.5f);



	//Create and initialize ScreenManager
	m_screenManager = new ScreenManager;
	m_screenManager->InitializeScreen(m_input);

	//Create and initialize EntityManager
	m_entityManager = new EntityManager;
	m_entityManager->Initialize(m_soundManager, m_input, m_device, m_deviceContext);
}

WPARAM Game::MainLoop()
{
	Timer _time;
	_time.StartTime();
	_time.TimeCheck();
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

		//Update FMOD
		m_soundManager->Update();

		//Get Time
		float time = _time.TimeCheck();

		CheckInput();

		//Call update functions
		Update(time);

		//Call Render Functions
		Render();
	}
}

void Game::Update(double time)
{
	m_screenManager->Update(time);
	//if(m_screenManager->GetCurrentScreen() == USERINTERFACE)
	// Update Entity Manager
	m_entityManager->Update(time);
}

void Game::Render()
{
	// clear the back buffer to a deep blue
	float _clearColor[] = { 0, 0, 1, 1 };
	m_deviceContext->ClearRenderTargetView(m_backbufferRTV, _clearColor);
	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	m_deviceContext->OMSetRenderTargets(1, &m_backbufferRTV, m_depthStencilView);
	m_screenManager->Render();
	//if(m_screenManager->GetCurrentScreen() == USERINTERFACE)
	// Render Entity Manager
	m_entityManager->Render();

	m_swapChain->Present(0, 0);
}

void Game::CheckInput()
{
	InputType _returnInput = m_input->CheckKeyBoardInput();
	//if (_returnInput & INPUT_ESC)  HEY LOOK AT ME I DON'T WORK OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOH HEJ EEEEEEEEEPER
	//	exit(0);
	m_input->CheckMouseInput();
}

void Game::SetViewport()
{
	D3D11_VIEWPORT _viewport;
	_viewport.Width = (float)640;
	_viewport.Height = (float)480;
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

	_hr = DepthStencilInitialicer(); //skapar depthstencil/desc 

	if (SUCCEEDED(_hr))
	{
		// get the address of the back buffer
		ID3D11Texture2D* _backBuffer = nullptr;
		m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&_backBuffer);

		// use the back buffer address to create the render target
		_hr = m_device->CreateRenderTargetView(_backBuffer, NULL, &m_backbufferRTV);
		_backBuffer->Release();

		// set the render target as the back buffer
		m_deviceContext->OMSetRenderTargets(1, &m_backbufferRTV, m_depthStencilView);
	}
	return _hr;
}

HRESULT Game::DepthStencilInitialicer()
{
	HRESULT _hr;

	//create the depth stencil
	D3D11_TEXTURE2D_DESC _descDepth;
	_descDepth.Width = 640;
	_descDepth.Height = 480;
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
