#ifndef _GAME_H_
#define _GAME_H_

#include "Display.h"
#include "SoundManager.h"
#include "ScreenManager.h"
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
	void DepthStencilInitialicer();

public:
	Game();
	~Game();
	void InitGame(Input* input, Display* disp);
	WPARAM MainLoop();

private:
	SoundManager* m_soundManager;
	ScreenManager* m_screenManager;
	Input* m_input;
	Display* m_display;
	MSG m_winMSG;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11Device* m_device;
	IDXGISwapChain* m_swapChain;
	ID3D11RenderTargetView* m_backbufferRTV;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11Texture2D* m_depthStencil;

public:
};

#endif 

