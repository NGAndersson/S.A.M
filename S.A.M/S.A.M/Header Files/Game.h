#ifndef _GAME_H_
#define _GAME_H_

#include "Graphics\Display.h"
#include "Audio/SoundManager.h"
#include "ScreenManager.h"
#include "EntityManager.h"
#include "Gamelogic\Input.h"
#include "Gamelogic\Timer.h"
#include "Graphics\DeferredRender.h"
#include "Graphics\DeferredBuffer.h"
#include "Gamelogic\Stats.h"

#include <d3d11.h>	//temp
#include <dxgidebug.h>



#define WIDTH 720
#define HEIGHT 980

class Game
{
private:
	void Update(double time);
	void Render();
	void CheckInput();
	void SetViewport();
	HRESULT CreateDirect3DContext(HWND wndHandle);
	HRESULT DepthStencilInitialicer();

public:
	Game();
	~Game();
	void InitGame(Input* input, Display* disp);
	WPARAM MainLoop();

private:
	SoundManager* m_soundManager;
	ScreenManager* m_screenManager;
	EntityManager* m_entityManager;
	Stats* m_statsManager;
	DeferredBuffer m_deferredBuffer;
	DeferredRender m_deferredRender;
	Input* m_input;
	Display* m_display;
	MSG m_winMSG;
	ID3D11DeviceContext* m_deviceContext = nullptr;
	ID3D11Device* m_device = nullptr;
	IDXGISwapChain* m_swapChain = nullptr;
	ID3D11RenderTargetView* m_backbufferRTV = nullptr;
	ID3D11DepthStencilView* m_depthStencilView = nullptr;
	ID3D11Texture2D* m_depthStencil = nullptr;
	ID3D11SamplerState* m_sampleState = nullptr;

public:
};

#endif 

