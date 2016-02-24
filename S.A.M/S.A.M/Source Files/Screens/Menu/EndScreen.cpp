#include "Screens/Menu/EndScreen.h"

EndScreen::EndScreen(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, Stats* stats) : Screen(Device, DeviceContext, ScreenHeight, ScreenWidth, input)
{
	m_font = make_unique<SpriteFont>(Device, L"Resources/moonhouse.spritefont");
	m_stats = stats;
	m_screenHeight = ScreenHeight;
	m_screenWidth = ScreenWidth;
}

void EndScreen::Update(double time)
{
	InputType _input;
	static bool _keyDown;

//	if (m_input->CheckReturn())
//		m_stats->SaveScore(m_playerName);

	_input = m_input->CheckKeyBoardInput();

	if (_input == INPUT_MOVE_DOWN && !_keyDown)
	{
		_keyDown = true;
	}
	else if (_input == INPUT_DEFAULT)
	{
		_keyDown = false;
	}
}

void EndScreen::Render()
{
	wstring _scoreMessage = L"Score: " + to_wstring(m_stats->GetScore());

	m_spriteBatch->Begin();

	XMVECTOR _origin = m_font->MeasureString(L"Game Over");
	_origin = XMVectorSetY(_origin, 0);
	m_font->DrawString(m_spriteBatch.get(), 
		L"Game Over", 
		SimpleMath::Vector2(m_screenWidth/2, m_screenHeight/3), 
		DirectX::Colors::Crimson, 
		0.f, 
		_origin/2, 
		SimpleMath::Vector3(1.5f));

	_origin = m_font->MeasureString(_scoreMessage.c_str());
	_origin = XMVectorSetY(_origin, 0);
	m_font->DrawString(m_spriteBatch.get(),
		_scoreMessage.c_str(),
		SimpleMath::Vector2(m_screenWidth / 2, m_screenHeight / 3 + 60),
		DirectX::Colors::Crimson,
		0.f,
		_origin / 2);

	_origin = m_font->MeasureString(L"Input Name: ");
	_origin = XMVectorSetY(_origin, 0);
	m_font->DrawString(m_spriteBatch.get(),
		L"Input Name: ",
		SimpleMath::Vector2(m_screenWidth / 2, m_screenHeight / 2),
		DirectX::Colors::Crimson,
		0.f,
		_origin);

	/*Add when input works
	_origin = m_font->MeasureString(m_playerName.c_str());
	float _prevLength = XMVectorGetX(_origin);
	m_font->DrawString(m_spriteBatch.get(),
		m_playerName,
		SimpleMath::Vector2(m_screenWidth / 3 + _prevLength, m_screenHeight / 2),
		DirectX::Colors::Crimson,
		0.f,
		SimpleMath::Vector2(0.f));
	*/

	m_spriteBatch->End();
}
