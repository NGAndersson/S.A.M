#include "../../../Header Files/Screens/Menu/PauseMenu.h" 

PauseMenu::PauseMenu(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input) : Screen(Device, DeviceContext, ScreenHeight, ScreenWidth, input)
{
	m_font = make_unique<SpriteFont>(Device, L"Resources/moonhouse.spritefont");

	SimpleMath::Vector2 _offsetV;
	_offsetV.x = 0.0f;
	_offsetV.y = 50.f * (float(m_screenHeight) / float(1440));

	m_choices[0].m_position.y = m_screenHeight / 2 - _offsetV.y * 2;
	m_choices[0].m_position.x = m_screenWidth / 2;
	m_choices[0].m_origin = m_font->MeasureString(m_resume.c_str()) / 2.f;
	m_choices[0].m_color = Colors::White;

	m_choices[1].m_position.y = m_screenHeight / 2 - _offsetV.y;
	m_choices[1].m_position.x = m_screenWidth / 2;
	m_choices[1].m_origin = m_font->MeasureString(m_menu.c_str()) / 2.f;
	m_choices[1].m_color = Colors::Crimson;

	m_choices[2].m_position.y = m_screenHeight / 2;
	m_choices[2].m_position.x = m_screenWidth / 2;
	m_choices[2].m_origin = m_font->MeasureString(m_options.c_str()) / 2.f;;
	m_choices[2].m_color = Colors::Crimson;

	m_choices[3].m_position.y = m_screenHeight / 2 + _offsetV.y;
	m_choices[3].m_position.x = m_screenWidth / 2;
	m_choices[3].m_origin = m_font->MeasureString(m_exit.c_str()) / 2.f;
	m_choices[3].m_color = Colors::Crimson;
	m_currentFont = 0;
}

void PauseMenu::Update(double time)
{

	InputType _inputReturn;

	_inputReturn = m_input->CheckKeyBoardInput();

	if (_inputReturn == INPUT_MOVE_DOWN&&!m_keyDown)
	{
		m_choices[m_currentFont].m_color = Colors::Crimson;
		m_currentFont = (m_currentFont + 1) % 4;
		m_choices[m_currentFont].m_color = Colors::White;
		m_keyDown = true;
	}
	else if (_inputReturn == INPUT_MOVE_UP&&!m_keyDown)
	{
		m_choices[m_currentFont].m_color = Colors::Crimson;
		m_currentFont = (m_currentFont - 1) % 4;
		if (m_currentFont == -1)
			m_currentFont = 3;

		m_choices[m_currentFont].m_color = Colors::White;
		m_keyDown = true;
	}
	else if (_inputReturn == INPUT_DEFAULT)
	{
		m_keyDown = false;
	}

}

void PauseMenu::Render()
{
	m_spriteBatch->Begin();

	m_font->DrawString(m_spriteBatch.get(), m_resume.c_str(), m_choices[0].m_position, m_choices[0].m_color, 0.f, m_choices[0].m_origin, float(m_screenWidth) / float(1058));

	m_font->DrawString(m_spriteBatch.get(), m_menu.c_str(), m_choices[1].m_position, m_choices[1].m_color, 0.f, m_choices[1].m_origin, float(m_screenWidth) / float(1058));

	m_font->DrawString(m_spriteBatch.get(), m_options.c_str(), m_choices[2].m_position, m_choices[2].m_color, 0.f, m_choices[2].m_origin, float(m_screenWidth) / float(1058));

	m_font->DrawString(m_spriteBatch.get(), m_exit.c_str(), m_choices[3].m_position, m_choices[3].m_color, 0.f, m_choices[3].m_origin, float(m_screenWidth) / float(1058));

	m_spriteBatch->End();
}

