#ifndef _SCREEN_H
#define _SCREEN_H
#include <iostream>

#include "WICTextureLoader.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "SimpleMath.h"
#include <vector>
#include "../Gamelogic/Input.h"
#include <wrl.h>

using namespace std;
using namespace DirectX;
using namespace Microsoft;
using namespace WRL;
enum MenuScreens {MENU_DEFAULT, MENU, GAME, HIGHSCORE, OPTION, PAUSE, ENDSCREEN ,EXIT, SONGSELECT};

class Screen
{
public:
	Screen() {}
	virtual ~Screen() {}
	Screen(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input);
	virtual void Update(double time);
	virtual void Render();
	virtual MenuScreens GetTargetMenu() { return m_currentTargetMenu; }
	virtual void SetTargetMenu(MenuScreens menu) { m_currentTargetMenu = menu; }
	virtual void Reset(){}
	virtual string GetSelectedSongFile() {	return "You shouldn't be here";}
	virtual string GetScoreFile() { return "You shouldn't be here"; }
protected:
	struct Font
	{
		SimpleMath::Vector2 m_position;
		SimpleMath::Vector2 m_origin;
		XMVECTORF32 m_color;
	};

	struct Sprite
	{
		SimpleMath::Vector2 m_position;
		SimpleMath::Vector2 m_origin;
		RECT m_rect;
		FXMVECTOR m_color;
	};

	MenuScreens m_currentTargetMenu;
	Input* m_input;
	int m_screenHeight;
	int m_screenWidth;
	unique_ptr<SpriteBatch> m_spriteBatch;
	ComPtr<ID3D11ShaderResourceView> m_backRound;
	unique_ptr<SpriteFont> m_font;
	SimpleMath::Vector2 m_fontPosition;

};

#endif