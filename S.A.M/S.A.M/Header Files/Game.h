#ifndef _GAME_H_
#define _GAME_H_

#include "Display.h"
#include "SoundManager.h"
#include "ScreenManager.h"
#include "EntityManager.h"
#include "Input.h"
#include "Timer.h"

#include <d3d11.h>	//temp

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
	Input* m_input;
	Display* m_display;
	MSG m_winMSG;
	ID3D11DeviceContext* m_deviceContext = nullptr;
	ID3D11Device* m_device = nullptr;
	IDXGISwapChain* m_swapChain = nullptr;
	ID3D11RenderTargetView* m_backbufferRTV = nullptr;
	ID3D11DepthStencilView* m_depthStencilView = nullptr;
	ID3D11Texture2D* m_depthStencil = nullptr;

public:
};

#endif 

