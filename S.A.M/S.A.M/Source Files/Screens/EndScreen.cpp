#include "Screens/EndScreen.h"

EndScreen::EndScreen(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, Stats* stats) : Screen(Device, DeviceContext, ScreenHeight, ScreenWidth, input)
{
	m_font = make_unique<SpriteFont>(Device, L"Resources/moonhouse.spritefont");
	m_stats = stats;

	m_highScore = L"High Score";
    m_menu = L"Return to Menu";
	m_message1 = L"Congratulations!";
	m_message2 = L"You have been killed!";
	m_message3 = L"Score: 0 ";

	SimpleMath::Vector2 _offsetV;
	_offsetV.x = 0.0f;
	_offsetV.y = 50.f;

	m_texts[0].m_position.y = m_screenHeight / 2 - _offsetV.y * 2;
	m_texts[0].m_position.x = m_screenWidth / 2;
	m_texts[0].m_origin = m_font->MeasureString(m_message1) / 2.f;
	m_texts[0].m_color = Colors::Crimson;

	m_texts[1].m_position.y = m_screenHeight / 2 - _offsetV.y;
	m_texts[1].m_position.x = m_screenWidth / 2;
	m_texts[1].m_origin = m_font->MeasureString(m_message2) / 2.f;
	m_texts[1].m_color = Colors::Crimson;
	
	m_texts[2].m_position.y = m_screenHeight / 2;
	m_texts[2].m_position.x = m_screenWidth / 2;
	m_texts[2].m_origin = m_font->MeasureString(m_message3) / 2.f;;
	m_texts[2].m_color = Colors::Crimson;

	m_choices[0].m_position.y = m_screenHeight / 2 + _offsetV.y;
	m_choices[0].m_position.x = m_screenWidth / 2;
	m_choices[0].m_origin = m_font->MeasureString(m_highScore) / 2.f;
	m_choices[0].m_color = Colors::White;

	m_choices[1].m_position.y = m_screenHeight / 2 + _offsetV.y * 2;
	m_choices[1].m_position.x = m_screenWidth / 2;
	m_choices[1].m_origin = m_font->MeasureString(m_menu) / 2.f;
	m_choices[1].m_color = Colors::Crimson;

	m_currentFont = 0;
}

void EndScreen::Update()
{
	InputType _input;

	_input = m_input->CheckKeyBoardInput();

	if (_input == INPUT_MOVE_DOWN && !m_keyDown)
	{
		m_choices[m_currentFont].m_color = Colors::Crimson;
		m_currentFont = (m_currentFont + 1) % 2;
		m_choices[m_currentFont].m_color = Colors::White;
		m_keyDown = true;
	}
	else if (_input == INPUT_MOVE_UP && !m_keyDown)
	{
		m_choices[m_currentFont].m_color = Colors::Crimson;
		m_currentFont = (m_currentFont - 1) % 2;
		if (m_currentFont == -1)
			m_currentFont = 1;

		m_choices[m_currentFont].m_color = Colors::White;
		m_keyDown = true;
	}
	else if (_input == INPUT_DEFAULT)
	{
		m_keyDown = false;
	}
}

void EndScreen::Render()
{
	m_spriteBatch->Begin();

	m_font->DrawString(m_spriteBatch.get(), m_highScore, m_choices[0].m_position, m_choices[0].m_color, 0.f, m_choices[0].m_origin);

	m_font->DrawString(m_spriteBatch.get(), m_menu, m_choices[1].m_position, m_choices[1].m_color, 0.f, m_choices[1].m_origin);

	m_font->DrawString(m_spriteBatch.get(), m_message1, m_texts[0].m_position, m_texts[0].m_color, 0.f, m_texts[0].m_origin);

	m_font->DrawString(m_spriteBatch.get(), m_message2, m_texts[1].m_position, m_texts[1].m_color, 0.f, m_texts[1].m_origin);

	m_font->DrawString(m_spriteBatch.get(), m_message3, m_texts[2].m_position, m_texts[2].m_color, 0.f, m_texts[2].m_origin);

	m_spriteBatch->End();
}
