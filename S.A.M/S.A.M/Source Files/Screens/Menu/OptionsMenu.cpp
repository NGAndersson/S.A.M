#include "../../../Header Files/Screens/Menu/OptionsMenu.h" 

OptionsMenu::OptionsMenu(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, SoundManager* SoundManager) : Screen(Device, DeviceContext, ScreenHeight, ScreenWidth, input)
{
	m_font = make_unique<SpriteFont>(Device, L"Resources/moonhouse.spritefont");

	SimpleMath::Vector2 _offsetV,_originV;
	_offsetV.x = 0.0f;
	_offsetV.y = 50.f;
	_originV.x = 0;
	_originV.y = 0;

	m_volumeMusic = L"Music Volume: ";// + to_wstring(SoundManager->GetVolume());//fix getvolume in soundmanager
	m_choices[MUSICVOLUME].m_position.y = m_screenHeight / 2 - _offsetV.y * 3;
	m_choices[MUSICVOLUME].m_origin = _originV;
	m_choices[MUSICVOLUME].m_position.x = m_choices[MUSICVOLUME].m_origin.x;
	m_choices[MUSICVOLUME].m_color = Colors::White;

	m_volumeShots = L"Shots Volume: ";// + to_wstring(SoundManager->GetVolume());//fix getvolume in soundmanager
	m_choices[SHOTSVOLUME].m_position.y = m_screenHeight / 2 - _offsetV.y * 2;
	m_choices[SHOTSVOLUME].m_origin = _originV;
	m_choices[SHOTSVOLUME].m_position.x = m_choices[SHOTSVOLUME].m_origin.x;
	m_choices[SHOTSVOLUME].m_color = Colors::Crimson;

	m_resolution = L"Resolution: " + to_wstring(m_screenHeight) + L" x " + to_wstring(m_screenWidth);
	m_choices[RESOLUTION].m_position.y = m_screenHeight / 2 - _offsetV.y;
	m_choices[RESOLUTION].m_origin = _originV;
	m_choices[RESOLUTION].m_position.x = m_choices[RESOLUTION].m_origin.x;
	m_choices[RESOLUTION].m_color = Colors::Crimson;

	m_keyBindings = L"KeyBindings:";
	m_choices[KEYBINDING].m_position.y = m_screenHeight / 2;
	m_choices[KEYBINDING].m_origin = _originV;
	m_choices[KEYBINDING].m_position.x = m_choices[KEYBINDING].m_origin.x;
	m_choices[KEYBINDING].m_color = Colors::Crimson;

	m_apply = L"Apply";
	m_choices[APPLY].m_position.y = m_screenHeight * 6 / 7;
	m_choices[APPLY].m_origin = m_font->MeasureString(m_apply.c_str()) / 2.f;
	m_choices[APPLY].m_position.x = m_screenWidth / 2.f;
	m_choices[APPLY].m_color = Colors::Crimson;

	m_menu = L"Return to Main Menu";
	m_choices[MAINMENU].m_position.y = m_screenHeight * 6 /7+_offsetV.y;
	m_choices[MAINMENU].m_origin = m_font->MeasureString(m_menu.c_str()) / 2.f;
	m_choices[MAINMENU].m_position.x = m_screenWidth / 2.f;
	m_choices[MAINMENU].m_color = Colors::Crimson;

	m_currentFont = 0;
	m_soundManager = SoundManager;
}

void OptionsMenu::Update(double time)
{

	InputType _inputReturn;

	_inputReturn = m_input->CheckKeyBoardInput();
	if (_inputReturn == INPUT_MOVE_DOWN&&!m_keyDown)
	{
		m_choices[m_currentFont].m_color = Colors::Crimson;
		m_currentFont = (m_currentFont + 1) % 6;
		m_choices[m_currentFont].m_color = Colors::White;
		m_keyDown = true;
	}
	else if (_inputReturn == INPUT_MOVE_UP&&!m_keyDown)
	{
		m_choices[m_currentFont].m_color = Colors::Crimson;
		m_currentFont = (m_currentFont - 1) % 6;
		if (m_currentFont == -1)
			m_currentFont = 5;

		m_choices[m_currentFont].m_color = Colors::White;
		m_keyDown = true;
	}
	else if (_inputReturn == INPUT_ENTER && !m_keyDown)
	{
		
	}
	else if (_inputReturn == INPUT_MOVE_LEFT && !m_keyDown)
	{
		switch (m_currentFont)
		{
		default:
			break;
		}
	}
	else if (_inputReturn == INPUT_MOVE_RIGHT && !m_keyDown)
	{
		switch (m_currentFont)
		{
		default:
			break;
		}
	}
	else if (_inputReturn == INPUT_DEFAULT)
	{
		m_keyDown = false;
	}
}

void OptionsMenu::Render()
{
	SimpleMath::Vector3 _scale{ 0.7f,0.7f,0.7f };
//Get Volume and Resolution and add..
	m_spriteBatch->Begin();
	m_font->DrawString(m_spriteBatch.get(), m_volumeMusic.c_str(), m_choices[MUSICVOLUME].m_position, m_choices[MUSICVOLUME].m_color,0.f, m_choices[MUSICVOLUME].m_origin,_scale);
	m_font->DrawString(m_spriteBatch.get(), m_volumeShots.c_str(), m_choices[SHOTSVOLUME].m_position, m_choices[SHOTSVOLUME].m_color, 0.f, m_choices[SHOTSVOLUME].m_origin,_scale);
	m_font->DrawString(m_spriteBatch.get(), m_resolution.c_str(), m_choices[RESOLUTION].m_position, m_choices[RESOLUTION].m_color, 0.f, m_choices[RESOLUTION].m_origin, _scale);
	m_font->DrawString(m_spriteBatch.get(), m_keyBindings.c_str(), m_choices[KEYBINDING].m_position, m_choices[KEYBINDING].m_color, 0.f, m_choices[KEYBINDING].m_origin,_scale);
	m_font->DrawString(m_spriteBatch.get(), m_apply.c_str(), m_choices[APPLY].m_position, m_choices[APPLY].m_color, 0.f, m_choices[APPLY].m_origin);
	m_font->DrawString(m_spriteBatch.get(), m_menu.c_str(), m_choices[MAINMENU].m_position, m_choices[MAINMENU].m_color, 0.f, m_choices[MAINMENU].m_origin);
	m_spriteBatch->End();
}

