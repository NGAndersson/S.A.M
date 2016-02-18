#include "../../Header Files/Screens/Screen.h"

Screen::Screen(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth,Input* input)
{
	//ComPtr<ID3D11Resource> _resource;
	//HRESULT hr;

	//m_font = make_unique<SpriteFont>(Device, L"Resources/moonhouse.spritefont");
	m_input = input;
	m_spriteBatch = make_unique<SpriteBatch>(DeviceContext);
	//hr = CreateWICTextureFromFile(Device, L"Resources/Models/Backround2.jpg", _resource.GetAddressOf(), m_backRound.ReleaseAndGetAddressOf());
	//ComPtr<ID3D11Texture2D> _sprite1;

	//CD3D11_TEXTURE2D_DESC _spriteDesc;
	//hr = _resource.As(&_sprite1);
	//_sprite1->GetDesc(&_spriteDesc);

	m_screenHeight = ScreenHeight;
	m_screenWidth = ScreenWidth;
}

void Screen::Update(double time)
{

}

void Screen::Render()
{

}

