#include "../../Header Files/Screens/Screen.h"

void Screen::Initialize(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext)
{
	ComPtr<ID3D11Resource> _resource;
	CreateWICTextureFromFile(Device, L"Resources / Models / Enemy1.png", _resource.GetAddressOf(), m_texture.ReleaseAndGetAddressOf());
	ComPtr<ID3D11Texture2D> _sprite1;

	CD3D11_TEXTURE2D_DESC _spriteDesc;
	_sprite1->GetDesc(&_spriteDesc);

	t_sprite.m_origin.x = _spriteDesc.Width / 2;
	t_sprite.m_origin.y = _spriteDesc.Height / 2;

	t_sprite.m_position.x = 720 / 2;
	t_sprite.m_position.y = 940 / 2;

}

void Screen::Update()
{

}

void Screen::Render()
{
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(m_texture.Get(), t_sprite.m_position, nullptr, Colors::White, 0.f, t_sprite.m_origin);
	m_spriteBatch->End();

}

