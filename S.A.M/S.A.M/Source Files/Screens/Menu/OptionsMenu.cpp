#include "../../../Header Files/Screens/Menu/OptionsMenu.h" 

OptionsMenu::OptionsMenu(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, SoundManager* SoundManager) : Screen(Device, DeviceContext, ScreenHeight, ScreenWidth, input)
{
	m_font = make_unique<SpriteFont>(Device, L"Resources/moonhouse.spritefont");

	SimpleMath::Vector2 _offsetV,_originV;
	_offsetV.x = 0.0f;
	_offsetV.y = 50.f;
	_originV.x = 0;
	_originV.y = 0;

	for (int i = 0; i < 10; i++)
	{
		m_volym[i] = i;
	}
	m_volumeMusic = L"Music Volume: ";
	m_choices[MUSICVOLUME].m_position.y = m_screenHeight / 2 - _offsetV.y * 3;
	m_choices[MUSICVOLUME].m_origin = _originV;
	m_choices[MUSICVOLUME].m_position.x = m_choices[MUSICVOLUME].m_origin.x;
	m_choices[MUSICVOLUME].m_color = Colors::White;

	m_volumeShots = L"Shots Volume: ";
	m_choices[SHOTSVOLUME].m_position.y = m_screenHeight / 2 - _offsetV.y * 2;
	m_choices[SHOTSVOLUME].m_origin = _originV;
	m_choices[SHOTSVOLUME].m_position.x = m_choices[SHOTSVOLUME].m_origin.x;
	m_choices[SHOTSVOLUME].m_color = Colors::Crimson;

	m_resolution = L"Resolution: " + to_wstring(m_screenHeight) + L" x " + to_wstring(m_screenWidth);
	m_choices[RESOLUTION].m_position.y = m_screenHeight / 2 - _offsetV.y;
	m_choices[RESOLUTION].m_origin = _originV;
	m_choices[RESOLUTION].m_position.x = m_choices[RESOLUTION].m_origin.x;
	m_choices[RESOLUTION].m_color = Colors::Crimson;

	m_keyBin = L"KeyBindings:";
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
	//The different Resolutions.
	m_tempHeight[0] = 653;
	m_tempHeight[1] = 980;
	m_tempHeight[2] = 1080;
	m_tempHeight[3] = 1440;

	m_tempWidth[0] = 480;
	m_tempWidth[1] = 720;
	m_tempWidth[2] = 793;
	m_tempWidth[3] = 1058;

	m_unBound = L"Press a Key";

	for (int i = 0; i < 9; i++)
		m_keyBindings[i] = m_input->GetKeyBiningArray(i);

	m_res[0] = to_wstring(m_tempHeight[0]) + L" x " + to_wstring(m_tempWidth[0]);
	m_res[1] = to_wstring(m_tempHeight[1]) + L" x " + to_wstring(m_tempWidth[1]);
	m_res[2] = to_wstring(m_tempHeight[2]) + L" x " + to_wstring(m_tempWidth[2]);
	m_res[3] = to_wstring(m_tempHeight[3]) + L" x " + to_wstring(m_tempWidth[3]);
	//Keybindings
	m_keys[WEAPON_1] = L"Weapon 1:"+m_input->GetKeyBinding(     m_keyBindings[WEAPON_1]);
	m_keys[WEAPON_2] = L"Weapon 2:" + m_input->GetKeyBinding(   m_keyBindings[WEAPON_2]);
	m_keys[WEAPON_3] = L"Weapon 3:" + m_input->GetKeyBinding(   m_keyBindings[WEAPON_3]);
	m_keys[WEAPON_4] = L"Weapon 4:" + m_input->GetKeyBinding(   m_keyBindings[WEAPON_4]);
	m_keys[MOVELEFT] = L"Move Left:" + m_input->GetKeyBinding(  m_keyBindings[MOVELEFT]);
	m_keys[MOVERIGHT] = L"Move Right:" + m_input->GetKeyBinding(m_keyBindings[MOVERIGHT]);
	m_keys[MOVEDOWN] = L"Move Down:" + m_input->GetKeyBinding(  m_keyBindings[MOVEDOWN]);
	m_keys[MOVEUP] = L"Move up:" + m_input->GetKeyBinding(      m_keyBindings[MOVEUP]);
	m_keys[COMBO] = L"Combo key:" + m_input->GetKeyBinding(     m_keyBindings[COMBO]);

	SimpleMath::Vector2 _offset(60.0, 30.0);
	SimpleMath::Vector2 _origin(0.0, 30.0);
	m_keyChoice[WEAPON_1].m_color = Colors::Crimson;
	m_keyChoice[WEAPON_1].m_origin = _origin;
	m_keyChoice[WEAPON_1].m_position = SimpleMath::Vector2(_origin.x, m_screenHeight / 2 + _offset.y * 2);
	SimpleMath::Vector2 _tempV = m_font->MeasureString(m_keys[WEAPON_1].c_str()) / 2.f;
	_origin.x += _tempV.x + _offset.x;
	m_keyChoice[WEAPON_2].m_color = Colors::Crimson;
	m_keyChoice[WEAPON_2].m_origin = _offset;
	m_keyChoice[WEAPON_2].m_position = SimpleMath::Vector2(_origin.x, m_screenHeight / 2 + _offset.y * 2);
	_tempV = m_font->MeasureString(m_keys[WEAPON_1].c_str()) / 2.f;
	_origin.x += _tempV.x + _offset.x;
	m_keyChoice[WEAPON_3].m_color = Colors::Crimson;
	m_keyChoice[WEAPON_3].m_origin = _offset;
	m_keyChoice[WEAPON_3].m_position = SimpleMath::Vector2(_origin.x, m_screenHeight / 2 + _offset.y * 2);
	_tempV = m_font->MeasureString(m_keys[WEAPON_1].c_str()) / 2.f;
	_origin.x += _tempV.x + _offset.x;
	m_keyChoice[WEAPON_4].m_color = Colors::Crimson;
	m_keyChoice[WEAPON_4].m_origin = _offset;
	m_keyChoice[WEAPON_4].m_position = SimpleMath::Vector2(_origin.x, m_screenHeight / 2 + _offset.y * 2);

	_offset.x = 60.0;
	_offset.y = 60.0;
	_origin.x = 0.0f;
	_origin.y = 60.0f;
	m_keyChoice[MOVELEFT].m_color = Colors::Crimson;
	m_keyChoice[MOVELEFT].m_origin = _origin;
	m_keyChoice[MOVELEFT].m_position = SimpleMath::Vector2(_origin.x, m_screenHeight / 2 + _offset.y * 2);
	_tempV = m_font->MeasureString(m_keys[WEAPON_1].c_str()) / 2.f;
	_origin.x += _tempV.x + _offset.x;
	m_keyChoice[MOVERIGHT].m_color = Colors::Crimson;
	m_keyChoice[MOVERIGHT].m_origin = _offset;
	m_keyChoice[MOVERIGHT].m_position = SimpleMath::Vector2(_origin.x, m_screenHeight / 2 + _offset.y * 2);
	_tempV = m_font->MeasureString(m_keys[WEAPON_1].c_str()) / 2.f;
	_origin.x += _tempV.x + _offset.x;
	m_keyChoice[MOVEUP].m_color = Colors::Crimson;
	m_keyChoice[MOVEUP].m_origin = _offset;
	m_keyChoice[MOVEUP].m_position = SimpleMath::Vector2(_origin.x, m_screenHeight / 2 + _offset.y * 2);
	_tempV = m_font->MeasureString(m_keys[WEAPON_1].c_str()) / 2.f;
	_origin.x += _tempV.x + _offset.x;
	m_keyChoice[MOVEDOWN].m_color = Colors::Crimson;
	m_keyChoice[MOVEDOWN].m_origin = _offset;
	m_keyChoice[MOVEDOWN].m_position = SimpleMath::Vector2(_origin.x, m_screenHeight / 2 + _offset.y * 2);
	_origin.x = 0.0f;
	_origin.y = 90.0f;
	m_keyChoice[COMBO].m_color = Colors::Crimson;
	m_keyChoice[COMBO].m_origin = _origin;
	m_keyChoice[COMBO].m_position = SimpleMath::Vector2(_origin.x, m_screenHeight / 2 + _offset.y * 3);

	//Determening what the current resolutions is. 
	switch (m_screenHeight)
	{
	case 653:
		m_currentRes = 0;
		break;
	case 980:
		m_currentRes = 1;
		break;
	case 1080:
		m_currentRes = 2;
		break;
	case 1440:
		m_currentRes = 3;
		break;
	}
	m_currentFont = 0;
	m_soundManager = SoundManager;
	m_ifKey = NOT_KEY;

}

void OptionsMenu::Update(double time)
{
	switch (m_currentRes)
	{
	case 0:
		m_resolution = L"Resolution: " + m_res[0];
		break;
	case 1:
		m_resolution = L"Resolution: " + m_res[1];
		break;
	case 2:
		m_resolution = L"Resolution: " + m_res[2];
		break;
	case 3:
		m_resolution = L"Resolution: " + m_res[3];
		break;
	default:
		break;
	}

	m_volumeMusic = L"Music Volume: " + to_wstring(m_volym[m_currentMVol]);
	m_volumeShots = L"Shot Volume: " + to_wstring(m_volym[m_currentSVol]);

	if (m_input->CheckReturn() && !m_keyDown)
	{
		if (m_ifKey == NOT_KEY)
		{
			if (m_currentFont == MAINMENU)
			{
				m_doneOption = true;
				m_keyDown = true;
				m_choices[MAINMENU].m_color = Colors::Crimson;
				m_currentFont = MUSICVOLUME;
				m_choices[m_currentFont].m_color = Colors::White;
			}
			else if (m_currentFont == KEYBINDING)
			{
				m_currentKeyBinding = WEAPON_1;
				m_keyChoice[m_currentKeyBinding].m_color = Colors::White;
				m_keyDown = true;
				m_ifKey = IN_KEY;
			}
		}
		else if (m_ifKey == IN_KEY && m_currentFont == KEYBINDING && !m_keyDown)
		{
			switch (m_currentKeyBinding)//Check what key the player want to unbind
			{
			case WEAPON_1:
				
				break;

			default:
				break;
			}
			m_keyDown = true;
			m_unBoundKey = true;
		}
	}

	InputType _inputReturn;
	_inputReturn = m_input->CheckKeyBoardInput();
	if (_inputReturn == INPUT_MOVE_DOWN&&!m_keyDown)
	{
		switch (m_ifKey)
		{
		case NOT_KEY:
		m_choices[m_currentFont].m_color = Colors::Crimson;
		m_currentFont = (m_currentFont + 1) % 6;
		m_choices[m_currentFont].m_color = Colors::White;
		m_keyDown = true;
		break;
		case IN_KEY:
			m_keyChoice[m_currentKeyBinding].m_color = Colors::Crimson;
			m_currentKeyBinding=(m_currentKeyBinding + 4) % 9;
			m_keyChoice[m_currentKeyBinding].m_color = Colors::White;
			m_keyDown = true;
			break;
		default:
			break;
		}
	}
	else if (_inputReturn == INPUT_MOVE_UP&&!m_keyDown)
	{
		switch (m_ifKey)
		{
		case NOT_KEY:
			m_choices[m_currentFont].m_color = Colors::Crimson;
			m_currentFont = (m_currentFont - 1) % 6;
			if (m_currentFont == -1)
				m_currentFont = 5;

			m_choices[m_currentFont].m_color = Colors::White;
			m_keyDown = true;
			break;
		case IN_KEY:
			m_keyChoice[m_currentKeyBinding].m_color = Colors::Crimson;
			m_currentKeyBinding=(m_currentKeyBinding - 4) % 9;
			if (m_currentKeyBinding < 0)
				m_currentKeyBinding + 4;
			m_keyChoice[m_currentKeyBinding].m_color = Colors::White;
			m_keyDown = true;
			break;
		default:
			break;
		}

	}
	else if (_inputReturn == INPUT_MOVE_LEFT && !m_keyDown)
	{
		switch (m_currentFont)
		{
		case RESOLUTION:
			m_currentRes = (m_currentRes - 1) % 4;
			if (m_currentRes < 0)
				m_currentRes = 3;
			m_keyDown = true;
			break;
		case MUSICVOLUME:
			m_currentMVol = (m_currentMVol - 1) % 10;
			if (m_currentMVol < 0)
				m_currentMVol = 9;
			m_keyDown = true;
			break;
		case SHOTSVOLUME:
			m_currentSVol = (m_currentSVol - 1) % 10;
			if (m_currentSVol < 0)
				m_currentSVol = 9;
			m_keyDown = true;
			break;
		case KEYBINDING:
			if (m_ifKey == IN_KEY)
			{
				m_keyChoice[m_currentKeyBinding].m_color = Colors::Crimson;
				m_currentKeyBinding = (m_currentKeyBinding - 1) % 9;
				if (m_currentKeyBinding < 0)
					m_currentKeyBinding = 8;
				m_keyChoice[m_currentKeyBinding].m_color = Colors::White;
				m_keyDown = true;
			}
			break;
		default:
			break;
		}
	}
	else if (_inputReturn == INPUT_MOVE_RIGHT && !m_keyDown)
	{
		switch (m_currentFont)
		{
		case RESOLUTION:
			m_currentRes = (m_currentRes + 1) % 4;
			m_keyDown = true;
			break;
		case MUSICVOLUME:
			m_currentMVol = (m_currentMVol + 1) % 10;
			m_keyDown = true;
			break;
		case SHOTSVOLUME:
			m_currentSVol = (m_currentSVol + 1) % 10;
			m_keyDown = true;
			break;
		case KEYBINDING:
			if (m_ifKey == IN_KEY)
			{
				m_keyChoice[m_currentKeyBinding].m_color = Colors::Crimson;
				m_currentKeyBinding = (m_currentKeyBinding + 1) % 9;
				m_keyChoice[m_currentKeyBinding].m_color = Colors::White;
				m_keyDown = true;
				
			}
			break;
		default:
			break;
		}
	}
	else if (_inputReturn == INPUT_DEFAULT)
	{
		m_keyDown = false;
	}

	if (m_input->CheckEsc())
	{
		switch (m_ifKey)
		{
		case NOT_KEY:
			m_choices[m_currentFont].m_color = Colors::Crimson;
			m_currentFont = MAINMENU;
			break;
		case IN_KEY:
			m_keyChoice[m_currentKeyBinding].m_color = Colors::Crimson;
			m_ifKey = NOT_KEY;
			break;
		default:
			break;
		}
	}
}

void OptionsMenu::setUpdateKeys()
{
	//Keybindings
	m_keys[WEAPON_1] = L"Weapon 1:" + m_keyBindings[WEAPON_1];
	m_keys[WEAPON_2] = L"Weapon 2:" + m_keyBindings[WEAPON_2];
	m_keys[WEAPON_3] = L"Weapon 3:" + m_keyBindings[WEAPON_3];
	m_keys[WEAPON_4] = L"Weapon 4:" + m_keyBindings[WEAPON_4];
	m_keys[MOVELEFT] = L"Move Left:" + m_keyBindings[MOVELEFT];
	m_keys[MOVERIGHT] = L"Move Right:" + m_keyBindings[MOVERIGHT];
	m_keys[MOVEDOWN] = L"Move Down:" + m_keyBindings[MOVEDOWN];
	m_keys[MOVEUP] = L"Move up:" + m_keyBindings[MOVEUP];
	m_keys[COMBO] = L"Combo key:" + m_keyBindings[COMBO];

}
void OptionsMenu::saveSettings()
{


}

void OptionsMenu::Render()
{
	SimpleMath::Vector3 _scale{ 0.7f,0.7f,0.7f };
	SimpleMath::Vector3 _scaleKeys{ 0.4f,0.4f,0.4f};

//Get Volume and Resolution and add..
	m_spriteBatch->Begin();
	m_font->DrawString(m_spriteBatch.get(), m_volumeMusic.c_str(), m_choices[MUSICVOLUME].m_position, m_choices[MUSICVOLUME].m_color,0.f, m_choices[MUSICVOLUME].m_origin,_scale);
	m_font->DrawString(m_spriteBatch.get(), m_volumeShots.c_str(), m_choices[SHOTSVOLUME].m_position, m_choices[SHOTSVOLUME].m_color, 0.f, m_choices[SHOTSVOLUME].m_origin,_scale);
	m_font->DrawString(m_spriteBatch.get(), m_resolution.c_str(), m_choices[RESOLUTION].m_position, m_choices[RESOLUTION].m_color, 0.f, m_choices[RESOLUTION].m_origin, _scale);
	m_font->DrawString(m_spriteBatch.get(), m_keyBin.c_str(), m_choices[KEYBINDING].m_position, m_choices[KEYBINDING].m_color, 0.f, m_choices[KEYBINDING].m_origin,_scale);
	//KEYBINDINGS BIT
	if (m_unBoundKey == true)
		m_font->DrawString(m_spriteBatch.get(), m_unBound.c_str(), m_keyChoice[m_currentKeyBinding].m_position, m_keyChoice[m_currentKeyBinding].m_color, 0.0f, m_keyChoice[m_currentKeyBinding].m_origin, _scaleKeys);
	
	m_font->DrawString(m_spriteBatch.get(), m_keys[WEAPON_1].c_str(), m_keyChoice[WEAPON_1].m_position, m_keyChoice[WEAPON_1].m_color, 0.0f, m_keyChoice[WEAPON_1].m_origin, _scaleKeys);
	m_font->DrawString(m_spriteBatch.get(), m_keys[WEAPON_2].c_str(), m_keyChoice[WEAPON_2].m_position, m_keyChoice[WEAPON_2].m_color, 0.0f, m_keyChoice[WEAPON_2].m_origin, _scaleKeys);
	m_font->DrawString(m_spriteBatch.get(), m_keys[WEAPON_3].c_str(), m_keyChoice[WEAPON_3].m_position, m_keyChoice[WEAPON_3].m_color, 0.0f, m_keyChoice[WEAPON_3].m_origin, _scaleKeys);
	m_font->DrawString(m_spriteBatch.get(), m_keys[WEAPON_4].c_str(), m_keyChoice[WEAPON_4].m_position, m_keyChoice[WEAPON_4].m_color, 0.0f, m_keyChoice[WEAPON_4].m_origin, _scaleKeys);
	m_font->DrawString(m_spriteBatch.get(), m_keys[MOVELEFT ].c_str(), m_keyChoice[MOVELEFT ].m_position, m_keyChoice[MOVELEFT ].m_color, 0.0f, m_keyChoice[MOVELEFT].m_origin, _scaleKeys);
	m_font->DrawString(m_spriteBatch.get(), m_keys[MOVERIGHT].c_str(), m_keyChoice[MOVERIGHT].m_position, m_keyChoice[MOVERIGHT].m_color, 0.0f, m_keyChoice[MOVERIGHT].m_origin, _scaleKeys);
	m_font->DrawString(m_spriteBatch.get(), m_keys[MOVEDOWN].c_str(), m_keyChoice[MOVEDOWN].m_position, m_keyChoice[MOVEDOWN].m_color, 0.0f, m_keyChoice[MOVEDOWN].m_origin, _scaleKeys);
	m_font->DrawString(m_spriteBatch.get(), m_keys[MOVEUP].c_str(), m_keyChoice[MOVEUP].m_position, m_keyChoice[MOVEUP].m_color, 0.0f, m_keyChoice[MOVEUP].m_origin, _scaleKeys);
	m_font->DrawString(m_spriteBatch.get(), m_keys[COMBO].c_str(), m_keyChoice[COMBO].m_position, m_keyChoice[COMBO].m_color, 0.0f, m_keyChoice[COMBO].m_origin, _scaleKeys);
	//NOT KEYBINDINGS ANYMORE
	m_font->DrawString(m_spriteBatch.get(), m_apply.c_str(), m_choices[APPLY].m_position, m_choices[APPLY].m_color, 0.f, m_choices[APPLY].m_origin);
	m_font->DrawString(m_spriteBatch.get(), m_menu.c_str(), m_choices[MAINMENU].m_position, m_choices[MAINMENU].m_color, 0.f, m_choices[MAINMENU].m_origin);
	m_spriteBatch->End();
}

