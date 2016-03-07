#include "../../Header Files/Screens/Screen.h"

Screen::Screen(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth,Input* input)
{
	//ComPtr<ID3D11Resource> _resource;
	//HRESULT hr;

	//m_font = make_unique<SpriteFont>(Device, L"Resources/moonhouse.spritefont");
	m_input = input;
	m_spriteBatch = make_unique<SpriteBatch>(DeviceContext);

	m_screenHeight = ScreenHeight;
	m_screenWidth = ScreenWidth;
}

void Screen::Update(double time)
{

}

void Screen::UpdateOP(double time)
{

}

void Screen::Render()
{

}

void Screen::Render(int offset)
{

}

