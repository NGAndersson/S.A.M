#include "../../../Header Files/Screens/Menu/LoadingScreen.h"

LoadingScreen::LoadingScreen(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input) : Screen(Device, DeviceContext, ScreenHeight, ScreenWidth, input)
{
	m_font = make_unique<SpriteFont>(Device, L"Resources/moonhouse.spritefont");

	CreateWICTextureFromFile(Device, L"Resources/Sprites/Background.png", nullptr, m_background.ReleaseAndGetAddressOf());
	m_Hints[0].m_color = Colors::White;
	m_Hints[0].m_origin = DirectX::SimpleMath::Vector2(ScreenWidth / 2, ScreenHeight / 2);
	m_Hints[0].m_position = DirectX::SimpleMath::Vector2(ScreenWidth / 2, ScreenHeight / 2);

	m_dyk = L"Now Loading";
	m_Hints[1].m_color = Colors::Crimson;
	m_Hints[1].m_origin = m_font->MeasureString(m_dyk.c_str()) / 2.f;
	m_Hints[1].m_position = DirectX::SimpleMath::Vector2(ScreenWidth / 2, ScreenHeight - 100);
}

LoadingScreen::~LoadingScreen()
{
	m_background.Reset();
}

void LoadingScreen::Render()
{
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(m_background.Get() , m_Hints[0].m_position, nullptr, m_Hints[0].m_color, 0.f, m_Hints[0].m_origin, 1.f);
	m_font->DrawString(m_spriteBatch.get(), m_dyk.c_str(), m_Hints[1].m_position, m_Hints[1].m_color, 0.f, m_Hints[1].m_origin, 1.f);
	m_spriteBatch->End();
}