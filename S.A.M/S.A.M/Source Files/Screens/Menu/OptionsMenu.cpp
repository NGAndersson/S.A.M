#include "../../../Header Files/Screens/Menu/OptionsMenu.h" 

OptionsMenu::OptionsMenu(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, SoundManager* SoundManager) : Screen(Device, DeviceContext, ScreenHeight, ScreenWidth, input)
{
	m_font = make_unique<SpriteFont>(Device, L"Resources/moonhouse.spritefont");
	ReadSetttings();

	SimpleMath::Vector2 _offsetV,_originV;
	_offsetV.x = 0.0f;
	_offsetV.y = 50.f;
	_originV.x = 0;
	_originV.y = 0;
	m_soundManager = SoundManager;
	for (int i = 0; i < 10; i++)
	{
		m_volym[i] = i;
	}

	for (int i = 0; i < 9; i++)
	{
		if (0.1f*m_volym[i] == m_soundManager->GetMusicVolume())
			m_currentMVol = i;

		if (0.1f*m_volym[i] == m_soundManager->GetEffectVolume())
			m_currentSVol = i;
	}


	m_volumeMusic = L"Music Volume: ";
	m_choices[MUSICVOLUME].m_position.y = m_screenHeight*1/10;
	m_choices[MUSICVOLUME].m_origin = _originV;
	m_choices[MUSICVOLUME].m_position.x = m_choices[MUSICVOLUME].m_origin.x;
	m_choices[MUSICVOLUME].m_color = Colors::White;

	m_volumeEffect = L"Shots Volume: ";
	m_choices[SHOTSVOLUME].m_position.y = m_screenHeight*2/10;
	m_choices[SHOTSVOLUME].m_origin = _originV;
	m_choices[SHOTSVOLUME].m_position.x = m_choices[SHOTSVOLUME].m_origin.x;
	m_choices[SHOTSVOLUME].m_color = Colors::Crimson;

	m_resolution = L"Resolution: " + to_wstring(m_screenHeight) + L" x " + to_wstring(m_screenWidth);
	m_choices[RESOLUTION].m_position.y = m_screenHeight*3/10;
	m_choices[RESOLUTION].m_origin = _originV;
	m_choices[RESOLUTION].m_position.x = m_choices[RESOLUTION].m_origin.x;
	m_choices[RESOLUTION].m_color = Colors::Crimson;

	m_keyBin = L"KeyBindings:";
	m_choices[KEYBINDING].m_position.y = m_screenHeight *4/10;
	m_choices[KEYBINDING].m_origin = _originV;
	m_choices[KEYBINDING].m_position.x = m_choices[KEYBINDING].m_origin.x;
	m_choices[KEYBINDING].m_color = Colors::Crimson;

	m_apply = L"Apply";
	m_choices[APPLY].m_position.y = m_screenHeight* 8/10;
	m_choices[APPLY].m_origin = m_font->MeasureString(m_apply.c_str()) / 2.f;
	m_choices[APPLY].m_position.x = m_screenWidth / 2.f;
	m_choices[APPLY].m_color = Colors::Crimson;

	m_pause = L"Back";
	m_menu = L"Return to Main Menu";
	m_choices[MAINMENU].m_position.y = m_screenHeight*9/10 ;
	m_choices[MAINMENU].m_origin = m_font->MeasureString(m_menu.c_str()) / 2.f;
	m_choices[MAINMENU].m_position.x = m_screenWidth / 2.f;
	m_choices[MAINMENU].m_color = Colors::Crimson;
	//The different Resolutions.

	m_unBound = L"Press a Key";
	
	for (int i = 0; i < 9; i++)
		m_keyBindings[i] = m_input->GetKeyBiningArray(i);
	
	m_res[0].first = 480;
	m_res[1].first = 720;
	m_res[2].first = 793;
	m_res[3].first = 1058;

	m_res[0].second = L"480 x 653 ";
	m_res[1].second = L"720 x 980 ";
	m_res[2].second = L"793 x 1080 ";
	m_res[3].second = L"1058 x 1440";

	m_resolutions[0].first = 480;
	m_resolutions[1].first = 720;
	m_resolutions[2].first = 793;
	m_resolutions[3].first = 1058;
	m_resolutions[0].second = 653;
	m_resolutions[1].second = 980;
	m_resolutions[2].second = 1080;
	m_resolutions[3].second = 1440;


	float _tempSy =  m_resolutions[m_defRes].second/10.f;
	float _tempSx = m_resolutions[m_defRes].first/4.f;

	m_scaleMenu = SimpleMath::Vector3(0.7f,0.7f, 1.0f);

	for (int i = 0; i < 4; i++)
	{
		if (m_res[i].first == m_screenWidth)
			m_currentRes = i;
	}
	m_defRes = m_currentRes;

	//Keybindings
	m_keys[WEAPON_1] = L"Weapon 1:"   ;
	m_keys[WEAPON_2] = L"Weapon 2:"   ;
	m_keys[WEAPON_3] = L"Weapon 3:"   ;
	m_keys[WEAPON_4] = L"Weapon 4:"   ;
	m_keys[MOVELEFT] = L"Move Left:"  ;
	m_keys[MOVERIGHT] = L"Move Right:";
	m_keys[MOVEDOWN] = L"Move Down:"  ;
	m_keys[MOVEUP] = L"Move up:"      ;
	m_keys[COMBO] = L"Combo key:"	  ;

	m_boundKeys[WEAPON_1 ] = m_input->GetKeyBinding(     m_keyBindings[WEAPON_1]);
	m_boundKeys[WEAPON_2 ] = m_input->GetKeyBinding(   m_keyBindings[WEAPON_2]);
	m_boundKeys[WEAPON_3 ] = m_input->GetKeyBinding(   m_keyBindings[WEAPON_3]);
	m_boundKeys[WEAPON_4 ] = m_input->GetKeyBinding(   m_keyBindings[WEAPON_4]);
	m_boundKeys[MOVELEFT ] = m_input->GetKeyBinding(  m_keyBindings[MOVELEFT]);
	m_boundKeys[MOVERIGHT] = m_input->GetKeyBinding(m_keyBindings[MOVERIGHT]);
	m_boundKeys[MOVEDOWN ] = m_input->GetKeyBinding(  m_keyBindings[MOVEDOWN]);
	m_boundKeys[MOVEUP   ] = m_input->GetKeyBinding(      m_keyBindings[MOVEUP]);
	m_boundKeys[COMBO    ] = m_input->GetKeyBinding(     m_keyBindings[COMBO]);


	SimpleMath::Vector2 _origin(0.0, 0.0);

	m_keyChoice[WEAPON_1].m_color = Colors::Crimson;
	m_keyChoice[WEAPON_1].m_length = m_font->MeasureString(m_keys[WEAPON_1].c_str());


	m_keyChoice[WEAPON_2].m_color = Colors::Crimson;
	m_keyChoice[WEAPON_2].m_length = m_font->MeasureString(m_keys[WEAPON_2].c_str());


	m_keyChoice[WEAPON_3].m_color = Colors::Crimson;
	m_keyChoice[WEAPON_3].m_length = m_font->MeasureString(m_keys[WEAPON_3].c_str());

	m_keyChoice[WEAPON_4].m_color = Colors::Crimson;
	m_keyChoice[WEAPON_4].m_length = m_font->MeasureString(m_keys[WEAPON_4].c_str());



	m_keyChoice[MOVELEFT].m_color = Colors::Crimson;
	m_keyChoice[MOVELEFT].m_length = m_font->MeasureString(m_keys[MOVELEFT].c_str());

	m_keyChoice[MOVERIGHT].m_color = Colors::Crimson;
	m_keyChoice[MOVERIGHT].m_length = m_font->MeasureString(m_keys[MOVERIGHT].c_str());


	m_keyChoice[MOVEUP].m_color = Colors::Crimson;
	m_keyChoice[MOVEUP].m_length = m_font->MeasureString(m_keys[MOVEUP].c_str());


	m_keyChoice[MOVEDOWN].m_color = Colors::Crimson;
	m_keyChoice[MOVEDOWN].m_length = m_font->MeasureString(m_keys[MOVEDOWN].c_str());


	m_keyChoice[COMBO].m_color = Colors::Crimson;
	m_keyChoice[COMBO].m_length = m_font->MeasureString(m_keys[COMBO].c_str());

	float _tempScale = (m_resolutions[m_defRes].first / (2*(m_keyChoice[WEAPON_1].m_length.x + m_keyChoice[WEAPON_2].m_length.x + m_keyChoice[WEAPON_3].m_length.x + m_keyChoice[WEAPON_4].m_length.x)));

	m_scaleKey = SimpleMath::Vector3(_tempScale, _tempScale,1.0f);

	float _offset[4];

	for (auto i = 0; i < 4; i++)
		_offset[i] = i*(m_resolutions[m_defRes].first / 4);

	m_keyChoice[WEAPON_1].m_position = SimpleMath::Vector2(_offset[0], m_screenHeight *5/10 );
	m_keyChoice[WEAPON_2].m_position = SimpleMath::Vector2(_offset[1], m_screenHeight *5/10 );
	m_keyChoice[WEAPON_3].m_position = SimpleMath::Vector2(_offset[2], m_screenHeight *5/10 );
	m_keyChoice[WEAPON_4].m_position = SimpleMath::Vector2(_offset[3], m_screenHeight *5/10 );

	m_keyChoice[MOVELEFT].m_position = SimpleMath::Vector2(_offset[0], m_screenHeight *6/10 );
	m_keyChoice[MOVERIGHT].m_position = SimpleMath::Vector2(_offset[1],m_screenHeight *6/10 );
	m_keyChoice[MOVEUP].m_position = SimpleMath::Vector2(_offset[2],   m_screenHeight *6/10 );
	m_keyChoice[MOVEDOWN].m_position = SimpleMath::Vector2(_offset[3], m_screenHeight *6/10 );

	m_keyChoice[COMBO].m_position = SimpleMath::Vector2(_offset[0],    m_screenHeight *7/10);

	m_boundKeyPos[WEAPON_1] = m_keyChoice[WEAPON_1].m_position + m_keyChoice[WEAPON_1].m_length*m_scaleKey.x;
	m_boundKeyPos[WEAPON_1].y = m_keyChoice[WEAPON_1].m_position.y;

	m_boundKeyPos[WEAPON_2] = m_keyChoice[WEAPON_2].m_position + m_keyChoice[WEAPON_2].m_length*m_scaleKey.x;
	m_boundKeyPos[WEAPON_2].y = m_keyChoice[WEAPON_2].m_position.y;

	m_boundKeyPos[WEAPON_3] = m_keyChoice[WEAPON_3].m_position + m_keyChoice[WEAPON_3].m_length*m_scaleKey.x;
	m_boundKeyPos[WEAPON_3].y = m_keyChoice[WEAPON_3].m_position.y;

	m_boundKeyPos[WEAPON_4] = m_keyChoice[WEAPON_4].m_position + m_keyChoice[WEAPON_4].m_length*m_scaleKey.x;
	m_boundKeyPos[WEAPON_4].y = m_keyChoice[WEAPON_4].m_position.y;

	m_boundKeyPos[MOVELEFT] = m_keyChoice[MOVELEFT].m_position + m_keyChoice[MOVELEFT].m_length*m_scaleKey.x;
	m_boundKeyPos[MOVELEFT].y = m_keyChoice[MOVELEFT].m_position.y;

	m_boundKeyPos[MOVERIGHT] = m_keyChoice[MOVERIGHT].m_position + m_keyChoice[MOVERIGHT].m_length*m_scaleKey.x;
	m_boundKeyPos[MOVERIGHT].y = m_keyChoice[MOVERIGHT].m_position.y;

	m_boundKeyPos[MOVEUP] = m_keyChoice[MOVEUP].m_position + m_keyChoice[MOVEUP].m_length*m_scaleKey.x;
	m_boundKeyPos[MOVEUP].y = m_keyChoice[MOVEUP].m_position.y;

	m_boundKeyPos[MOVEDOWN] = m_keyChoice[MOVEDOWN].m_position + m_keyChoice[MOVEDOWN].m_length*m_scaleKey.x;
	m_boundKeyPos[MOVEDOWN].y = m_keyChoice[MOVEDOWN].m_position.y;

	m_boundKeyPos[COMBO] = m_keyChoice[COMBO].m_position + m_keyChoice[COMBO].m_length*m_scaleKey.x;
	m_boundKeyPos[COMBO].y = m_keyChoice[COMBO].m_position.y;

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

	m_ifKey = NOT_KEY;
	m_currentTargetMenu = OPTION;

}

void OptionsMenu::Update(double time)
{
	m_state = false;
	switch (m_currentRes)
	{
	case 0:
		m_resolution = L"Resolution: " + m_res[0].second;
		break;
	case 1:
		m_resolution = L"Resolution: " + m_res[1].second;
		break;
	case 2:
		m_resolution = L"Resolution: " + m_res[2].second;
		break;
	case 3:
		m_resolution = L"Resolution: " + m_res[3].second;
		break;
	default:
		break;
	}

	m_volumeMusic = L"Music Volume: " + to_wstring(m_volym[m_currentMVol]);
	m_volumeEffect = L"Shot Volume: " + to_wstring(m_volym[m_currentSVol]);

	if (m_unBoundKey&&!m_keyDown&&m_input->CheckIfInput())
	{
		int _tempNewKey = m_input->CheckInputInt();
		switch (m_currentKeyBinding)//Check what key the player want to unbind
		{
		case WEAPON_1:
			m_keyBindings[WEAPON_1] = _tempNewKey;
			break;
		case WEAPON_2:
			m_keyBindings[WEAPON_2] = _tempNewKey;
			break;
		case WEAPON_3:
			m_keyBindings[WEAPON_3] = _tempNewKey;
			break;
		case WEAPON_4:
			m_keyBindings[WEAPON_4] = _tempNewKey;
			break;
		case MOVELEFT:
			m_keyBindings[MOVELEFT] = _tempNewKey;
			break;
		case MOVERIGHT:
			m_keyBindings[MOVERIGHT] = _tempNewKey;
			break;
		case MOVEUP:
			m_keyBindings[MOVEUP] = _tempNewKey;
			break;
		case MOVEDOWN:
			m_keyBindings[MOVEDOWN] = _tempNewKey;
			break;
		case COMBO:
			m_keyBindings[COMBO] = _tempNewKey;
			break;

		default:
			break;
		}
		_tempNewKey = 0;
		setUpdateKeys();
		m_unBoundKey = false;
		m_keyDown = true;
	}
	 
	if (m_input->CheckReturn() && !m_keyDown)
	{
		if (m_ifKey == NOT_KEY)
		{
			if (m_currentFont == MAINMENU)
			{
				m_currentTargetMenu = MENU;
				m_doneOption = true;
				m_keyDown = true;
				m_choices[MAINMENU].m_color = Colors::Crimson;
				m_currentFont = MUSICVOLUME;
				m_choices[m_currentFont].m_color = Colors::White;

				for (int i = 0; i < 9; i++)
					m_keyBindings[i] = m_input->GetKeyBiningArray(i);

				for (int i = 0; i < 9; i++)
				{
					if (0.1f*m_volym[i] == m_soundManager->GetMusicVolume())
						m_currentMVol = i;

					if (0.1f*m_volym[i] == m_soundManager->GetEffectVolume())
						m_currentSVol = i;
				}
				m_currentRes = m_defRes;
				setUpdateKeys();
			}
			else if (m_currentFont == KEYBINDING)
			{
				m_currentKeyBinding = WEAPON_1;
				m_keyChoice[m_currentKeyBinding].m_color = Colors::White;
				m_keyDown = true;
				m_ifKey = IN_KEY;
			}
			else if (m_currentFont == APPLY)
			{
				m_currentTargetMenu = MENU;
				m_doneOption = true;
				m_keyDown = true;
				m_choices[MAINMENU].m_color = Colors::Crimson;
				m_currentFont = MUSICVOLUME;
				m_choices[m_currentFont].m_color = Colors::White;

				m_input->SetKeyBindings(m_keyBindings);
				m_soundManager->SetMusicVolume(1.f/m_volym[m_currentMVol]);
				m_soundManager->SetEffectVolume(1.f/m_volym[m_currentSVol]);
				//Fix resolutions here laaaaaaater
				
				if (m_res[m_currentRes].first != m_screenWidth)
					m_currentTargetMenu = NEWRES;

				saveSettings();
				m_defRes = m_currentRes;
			}
		}
		else if (m_ifKey == IN_KEY && m_currentFont == KEYBINDING && !m_keyDown)
		{

			m_unBoundKey = true;
			m_keyDown = true;
		}
	}
	int _tempd;//used to reset m_currentKeyBindong if its < 0
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
			_tempd = m_currentKeyBinding;
			m_currentKeyBinding=(m_currentKeyBinding - 4) % 9;
			if (m_currentKeyBinding < 0)
				m_currentKeyBinding =_tempd;

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

	if (m_input->CheckEsc() && !m_keyDown)
	{
		switch (m_ifKey)
		{
		case NOT_KEY:
			m_currentTargetMenu = MENU;
			break;
		case IN_KEY:
			m_keyChoice[m_currentKeyBinding].m_color = Colors::Crimson;
			Reset();
			m_ifKey = NOT_KEY;
			break;
		default:
			break;
		}
	}
}

void OptionsMenu::UpdateOP(double time)
{
	m_state = true;
	switch (m_currentRes)
	{
	case 0:
		m_resolution = L"Resolution: " + m_res[0].second;
		break;
	case 1:
		m_resolution = L"Resolution: " + m_res[1].second;
		break;
	case 2:
		m_resolution = L"Resolution: " + m_res[2].second;
		break;
	case 3:
		m_resolution = L"Resolution: " + m_res[3].second;
		break;
	default:
		break;
	}

	m_volumeMusic = L"Music Volume: " + to_wstring(m_volym[m_currentMVol]);
	m_volumeEffect = L"Shot Volume: " + to_wstring(m_volym[m_currentSVol]);

	if (m_unBoundKey&&!m_keyDown&&m_input->CheckIfInput())
	{
		int _tempNewKey = m_input->CheckInputInt();
		switch (m_currentKeyBinding)//Check what key the player want to unbind
		{
		case WEAPON_1:
			m_keyBindings[WEAPON_1] = _tempNewKey;
			break;
		case WEAPON_2:
			m_keyBindings[WEAPON_2] = _tempNewKey;
			break;
		case WEAPON_3:
			m_keyBindings[WEAPON_3] = _tempNewKey;
			break;
		case WEAPON_4:
			m_keyBindings[WEAPON_4] = _tempNewKey;
			break;
		case MOVELEFT:
			m_keyBindings[MOVELEFT] = _tempNewKey;
			break;
		case MOVERIGHT:
			m_keyBindings[MOVERIGHT] = _tempNewKey;
			break;
		case MOVEUP:
			m_keyBindings[MOVEUP] = _tempNewKey;
			break;
		case MOVEDOWN:
			m_keyBindings[MOVEDOWN] = _tempNewKey;
			break;
		case COMBO:
			m_keyBindings[COMBO] = _tempNewKey;
			break;

		default:
			break;
		}
		_tempNewKey = 0;
		setUpdateKeys();
		m_unBoundKey = false;
		m_keyDown = true;
	}

	if (m_input->CheckReturn() && !m_keyDown)
	{
		if (m_ifKey == NOT_KEY)
		{
			if (m_currentFont == MAINMENU)
			{
				if (m_state == false)
					m_currentTargetMenu = MENU;
				else if (m_state == true)
					m_currentTargetMenu = PAUSE;
				m_doneOption = true;
				m_keyDown = true;
				m_choices[MAINMENU].m_color = Colors::Crimson;
				m_currentFont = MUSICVOLUME;
				m_choices[m_currentFont].m_color = Colors::White;

				for (int i = 0; i < 9; i++)
					m_keyBindings[i] = m_input->GetKeyBiningArray(i);

				for (int i = 0; i < 9; i++)
				{
					if (0.1f*m_volym[i] == m_soundManager->GetMusicVolume())
						m_currentMVol = i;

					if (0.1f*m_volym[i] == m_soundManager->GetEffectVolume())
						m_currentSVol = i;
				}
				m_currentRes = m_defRes;
				setUpdateKeys();
			}
			else if (m_currentFont == KEYBINDING)
			{
				m_currentKeyBinding = WEAPON_1;
				m_keyChoice[m_currentKeyBinding].m_color = Colors::White;
				m_keyDown = true;
				m_ifKey = IN_KEY;
			}
			else if (m_currentFont == APPLY)
			{
				if (m_state == false)
					m_currentTargetMenu = MENU;
				else if (m_state == true)
					m_currentTargetMenu = PAUSE;
				m_doneOption = true;
				m_keyDown = true;
				m_choices[MAINMENU].m_color = Colors::Crimson;
				m_currentFont = MUSICVOLUME;
				m_choices[m_currentFont].m_color = Colors::White;

				m_input->SetKeyBindings(m_keyBindings);
				m_soundManager->SetMusicVolume(1.f / m_volym[m_currentMVol]);
				m_soundManager->SetEffectVolume(1.f / m_volym[m_currentSVol]);
				//Fix resolutions here laaaaaaater

				if (m_res[m_currentRes].first != m_screenWidth)
					m_currentTargetMenu = NEWRES;

				saveSettings();
				m_defRes = m_currentRes;
			}
		}
		else if (m_ifKey == IN_KEY && m_currentFont == KEYBINDING && !m_keyDown)
		{

			m_unBoundKey = true;
			m_keyDown = true;
		}
	}
	int _tempd;//used to reset m_currentKeyBindong if its < 0
	InputType _inputReturn;
	_inputReturn = m_input->CheckKeyBoardInput();
	if (_inputReturn == INPUT_MOVE_DOWN&&!m_keyDown)
	{
		switch (m_ifKey)
		{
		case NOT_KEY:
			m_choices[m_currentFont].m_color = Colors::Crimson;
			m_currentFont = (m_currentFont + 1) % 6;
			if (m_state == true && m_currentFont == 2)
				m_currentFont = (m_currentFont + 1) % 6;
			m_choices[m_currentFont].m_color = Colors::White;
			m_keyDown = true;
			break;
		case IN_KEY:
			m_keyChoice[m_currentKeyBinding].m_color = Colors::Crimson;
			m_currentKeyBinding = (m_currentKeyBinding + 4) % 9;
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
			if (m_state == true && m_currentFont == 2)
				m_currentFont = (m_currentFont - 1) % 6;
			if (m_currentFont == -1)
				m_currentFont = 5;

			m_choices[m_currentFont].m_color = Colors::White;
			m_keyDown = true;
			break;
		case IN_KEY:
			m_keyChoice[m_currentKeyBinding].m_color = Colors::Crimson;
			_tempd = m_currentKeyBinding;
			m_currentKeyBinding = (m_currentKeyBinding - 4) % 9;
			if (m_currentKeyBinding < 0)
				m_currentKeyBinding = _tempd;

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

	if (m_input->CheckEsc() && !m_keyDown)
	{
		switch (m_ifKey)
		{
		case NOT_KEY:
			if (m_state == false)
				m_currentTargetMenu = MENU;
			else if (m_state == true)
				m_currentTargetMenu = PAUSE;
			break;
		case IN_KEY:
			m_keyChoice[m_currentKeyBinding].m_color = Colors::Crimson;
			Reset();
			m_ifKey = NOT_KEY;
			break;
		default:
			break;
		}
	}
}

void OptionsMenu::setUpdateKeys()
{
	//for (int i = 0; i < 9; i++)
	//	m_keyBindings[i] = m_input->GetKeyBiningArray(i);

	//Keybindings
	m_boundKeys[WEAPON_1] = m_input->GetKeyBinding(m_keyBindings[WEAPON_1]);
	m_boundKeys[WEAPON_2] = m_input->GetKeyBinding(m_keyBindings[WEAPON_2]);
	m_boundKeys[WEAPON_3] = m_input->GetKeyBinding(m_keyBindings[WEAPON_3]);
	m_boundKeys[WEAPON_4] = m_input->GetKeyBinding(m_keyBindings[WEAPON_4]);
	m_boundKeys[MOVELEFT] = m_input->GetKeyBinding(m_keyBindings[MOVELEFT]);
	m_boundKeys[MOVERIGHT] = m_input->GetKeyBinding(m_keyBindings[MOVERIGHT]);
	m_boundKeys[MOVEDOWN] = m_input->GetKeyBinding(m_keyBindings[MOVEDOWN]);
	m_boundKeys[MOVEUP] = m_input->GetKeyBinding(m_keyBindings[MOVEUP]);
	m_boundKeys[COMBO] = m_input->GetKeyBinding(m_keyBindings[COMBO]);


}

void OptionsMenu::saveSettings()
{
	std::fstream _file;
	_file.open("Options/Settings.txt");

	_file << "### Settings\n" << std::endl;
	_file << "ScreenHeight|" << m_resolutions[m_currentRes].second << std::endl;
	_file << "ScreenWidth|" << m_resolutions[m_currentRes].first << std::endl;
	_file << "MusicVolume|" << m_currentMVol << std::endl;
	_file << "EffectVolume|" << m_currentSVol << std::endl;
	_file.close();
}

void OptionsMenu::ReadSetttings()
{
	std::fstream _file;
	_file.open("Options/Settings.txt");
	std::string _tempLine;
	char _key[100];
	char _value[100];
	if (_file.is_open())
	{
		while (getline(_file, _tempLine))
		{
			std::istringstream _ss(_tempLine);
			_ss.get(_key, 100, '|');
			_ss.ignore();
			if (_key[0] != '#')
			{
				_ss.get(_value, 100, '|');
				if (std::string(_key) == "ScreenHeight")
					m_screenHeight = atoi(_value);

				else if (std::string(_key) == "ScreenWidth")
					m_screenWidth = atoi(_value);

				else if (std::string(_key) == "MusicVolume")
					m_currentMVol = atoi(_value);

				else if (std::string(_key) == "EffectVolume")
					m_currentSVol = atoi(_value);
			}
		}
		_file.close();
	}
}

void OptionsMenu::Render()
{

//Get Volume and Resolution and add..
	m_spriteBatch->Begin();
	m_font->DrawString(m_spriteBatch.get(), m_volumeMusic.c_str(), m_choices[MUSICVOLUME].m_position, m_choices[MUSICVOLUME].m_color,0.f, m_choices[MUSICVOLUME].m_origin,m_scaleMenu);
	m_font->DrawString(m_spriteBatch.get(), m_volumeEffect.c_str(), m_choices[SHOTSVOLUME].m_position, m_choices[SHOTSVOLUME].m_color, 0.f, m_choices[SHOTSVOLUME].m_origin,m_scaleMenu);
	if (m_state == false)	//only shows the resolution if not in game
	{
		m_font->DrawString(m_spriteBatch.get(), m_resolution.c_str(), m_choices[RESOLUTION].m_position, m_choices[RESOLUTION].m_color, 0.f, m_choices[RESOLUTION].m_origin, m_scaleMenu);
	}	
	m_font->DrawString(m_spriteBatch.get(), m_keyBin.c_str(), m_choices[KEYBINDING].m_position, m_choices[KEYBINDING].m_color, 0.f, m_choices[KEYBINDING].m_origin,m_scaleMenu);
	//KEYBINDINGS BIT
	if (m_unBoundKey == true && !m_keyDown)
		m_font->DrawString(m_spriteBatch.get(),m_unBound.c_str(),SimpleMath::Vector2(m_screenWidth/2.0,m_screenHeight/2.0f), Colors::Gold, 0.0f, m_font->MeasureString(m_unBound.c_str())/2.f);
	
	m_font->DrawString(m_spriteBatch.get(), m_keys[WEAPON_1].c_str(), m_keyChoice[WEAPON_1].m_position, m_keyChoice[WEAPON_1].m_color, 0.0f, m_keyChoice[WEAPON_1].m_origin, m_scaleKey);
	m_font->DrawString(m_spriteBatch.get(), m_keys[WEAPON_2].c_str(), m_keyChoice[WEAPON_2].m_position, m_keyChoice[WEAPON_2].m_color, 0.0f, m_keyChoice[WEAPON_2].m_origin, m_scaleKey);
	m_font->DrawString(m_spriteBatch.get(), m_keys[WEAPON_3].c_str(), m_keyChoice[WEAPON_3].m_position, m_keyChoice[WEAPON_3].m_color, 0.0f, m_keyChoice[WEAPON_3].m_origin, m_scaleKey);
	m_font->DrawString(m_spriteBatch.get(), m_keys[WEAPON_4].c_str(), m_keyChoice[WEAPON_4].m_position, m_keyChoice[WEAPON_4].m_color, 0.0f, m_keyChoice[WEAPON_4].m_origin, m_scaleKey);
	m_font->DrawString(m_spriteBatch.get(), m_keys[MOVELEFT ].c_str(), m_keyChoice[MOVELEFT ].m_position, m_keyChoice[MOVELEFT ].m_color, 0.0f, m_keyChoice[MOVELEFT].m_origin, m_scaleKey);
	m_font->DrawString(m_spriteBatch.get(), m_keys[MOVERIGHT].c_str(), m_keyChoice[MOVERIGHT].m_position, m_keyChoice[MOVERIGHT].m_color, 0.0f, m_keyChoice[MOVERIGHT].m_origin,m_scaleKey);
	m_font->DrawString(m_spriteBatch.get(), m_keys[MOVEDOWN].c_str(), m_keyChoice[MOVEDOWN].m_position, m_keyChoice[MOVEDOWN].m_color, 0.0f, m_keyChoice[MOVEDOWN].m_origin, m_scaleKey);
	m_font->DrawString(m_spriteBatch.get(), m_keys[MOVEUP].c_str(), m_keyChoice[MOVEUP].m_position, m_keyChoice[MOVEUP].m_color, 0.0f, m_keyChoice[MOVEUP].m_origin,m_scaleKey);
	m_font->DrawString(m_spriteBatch.get(), m_keys[COMBO].c_str(), m_keyChoice[COMBO].m_position, m_keyChoice[COMBO].m_color, 0.0f, m_keyChoice[COMBO].m_origin, m_scaleKey);
	
	// THE BOUND KEYS HEEERERERE
	m_font->DrawString(m_spriteBatch.get(), m_boundKeys[WEAPON_1].c_str(), m_boundKeyPos[WEAPON_1], Colors::BlueViolet, 0.0f,SimpleMath::Vector2(0.0f,0.0f),m_scaleKey);
	m_font->DrawString(m_spriteBatch.get(), m_boundKeys[WEAPON_2].c_str(), m_boundKeyPos[WEAPON_2], Colors::BlueViolet, 0.0f,SimpleMath::Vector2(0.0f,0.0f),m_scaleKey);
	m_font->DrawString(m_spriteBatch.get(), m_boundKeys[WEAPON_3].c_str(), m_boundKeyPos[WEAPON_3], Colors::BlueViolet, 0.0f,SimpleMath::Vector2(0.0f,0.0f),m_scaleKey);
	m_font->DrawString(m_spriteBatch.get(), m_boundKeys[WEAPON_4].c_str(), m_boundKeyPos[WEAPON_4], Colors::BlueViolet, 0.0f,SimpleMath::Vector2(0.0f,0.0f),m_scaleKey);
	m_font->DrawString(m_spriteBatch.get(), m_boundKeys[MOVELEFT].c_str(), m_boundKeyPos[MOVELEFT], Colors::BlueViolet, 0.0f,SimpleMath::Vector2(0.0f,0.0f),m_scaleKey);
	m_font->DrawString(m_spriteBatch.get(), m_boundKeys[MOVERIGHT].c_str(),m_boundKeyPos[MOVERIGHT],Colors::BlueViolet, 0.0f,SimpleMath::Vector2(0.0f,0.0f),m_scaleKey);
	m_font->DrawString(m_spriteBatch.get(), m_boundKeys[MOVEDOWN].c_str(), m_boundKeyPos[MOVEDOWN], Colors::BlueViolet, 0.0f,SimpleMath::Vector2(0.0f,0.0f),m_scaleKey);
	m_font->DrawString(m_spriteBatch.get(), m_boundKeys[MOVEUP].c_str(),   m_boundKeyPos[MOVEUP],   Colors::BlueViolet, 0.0f,SimpleMath::Vector2(0.0f,0.0f),m_scaleKey);
	m_font->DrawString(m_spriteBatch.get(), m_boundKeys[COMBO].c_str(),    m_boundKeyPos[COMBO],    Colors::BlueViolet, 0.0f,SimpleMath::Vector2(0.0f,0.0f),m_scaleKey);

	//NOT KEYBINDINGS ANYMORE
	m_font->DrawString(m_spriteBatch.get(), m_apply.c_str(), m_choices[APPLY].m_position, m_choices[APPLY].m_color, 0.f, m_choices[APPLY].m_origin);
	if (m_state == false)
		m_font->DrawString(m_spriteBatch.get(), m_menu.c_str(), m_choices[MAINMENU].m_position, m_choices[MAINMENU].m_color, 0.f, m_choices[MAINMENU].m_origin);
	else
		m_font->DrawString(m_spriteBatch.get(), m_pause.c_str(), m_choices[MAINMENU].m_position, m_choices[MAINMENU].m_color, 0.f, m_choices[APPLY].m_origin);
	m_spriteBatch->End();
}