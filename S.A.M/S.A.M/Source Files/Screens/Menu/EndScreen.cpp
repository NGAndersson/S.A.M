#include "Screens/Menu/EndScreen.h"
#define NAMEMAXLENGTH 10

wchar_t EndScreen::KeyToWChar(int key)
{
	wchar_t _keyChar = L'\0';
	
	switch (key) {
	case DIK_A: _keyChar = L'A'; break;
	case DIK_B: _keyChar = L'B'; break;
	case DIK_C: _keyChar = L'C'; break;
	case DIK_D: _keyChar = L'D'; break;
	case DIK_E: _keyChar = L'E'; break;
	case DIK_F: _keyChar = L'F'; break;
	case DIK_G: _keyChar = L'G'; break;
	case DIK_H: _keyChar = L'H'; break;
	case DIK_I: _keyChar = L'I'; break;
	case DIK_J: _keyChar = L'J'; break;
	case DIK_K: _keyChar = L'K'; break;
	case DIK_L: _keyChar = L'L'; break;
	case DIK_M: _keyChar = L'M'; break;
	case DIK_N: _keyChar = L'N'; break;
	case DIK_O: _keyChar = L'O'; break;
	case DIK_P: _keyChar = L'P'; break;
	case DIK_Q: _keyChar = L'Q'; break;
	case DIK_R: _keyChar = L'R'; break;
	case DIK_S: _keyChar = L'S'; break;
	case DIK_T: _keyChar = L'T'; break;
	case DIK_U: _keyChar = L'U'; break;
	case DIK_V: _keyChar = L'V'; break;
	case DIK_W: _keyChar = L'W'; break;
	case DIK_X: _keyChar = L'X'; break;
	case DIK_Y: _keyChar = L'Y'; break;
	case DIK_Z: _keyChar = L'Z'; break;
	case DIK_SPACE: _keyChar = L' '; break;
	case DIK_1: _keyChar = L'1'; break;
	case DIK_2: _keyChar = L'2'; break;
	case DIK_3: _keyChar = L'3'; break;
	case DIK_4: _keyChar = L'4'; break;
	case DIK_5: _keyChar = L'5'; break;
	case DIK_6: _keyChar = L'6'; break;
	case DIK_7: _keyChar = L'7'; break;
	case DIK_8: _keyChar = L'8'; break;
	case DIK_9: _keyChar = L'9'; break;
	case DIK_0: _keyChar = L'0'; break;
	default: _keyChar = L'\0'; break;
	}
	return _keyChar;
}

EndScreen::EndScreen(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, Stats* stats) : Screen(Device, DeviceContext, ScreenHeight, ScreenWidth, input)
{
	m_font = make_unique<SpriteFont>(Device, L"Resources/moonhouse.spritefont");
	m_stats = stats;
	m_screenHeight = ScreenHeight;
	m_screenWidth = ScreenWidth;
	m_playerName = L"";
}

void EndScreen::Update(double time)
{
	InputType _input;
	static bool _keyDown;

	if (m_input->CheckBackspace())						//Backspace
	{
		if (!_keyDown)
		{
			if (m_playerName != L"")
				m_playerName.pop_back();
			_keyDown = true;
		}
	}
	else if (m_playerName.length() < (int)NAMEMAXLENGTH) //Backspace wasn't pressed, check other buttons
	{									
		int _key = m_input->CheckInputInt();
		wchar_t _wkey = KeyToWChar(_key);

		if (_wkey != L'\0')
		{
			if (!_keyDown)
			{
				m_playerName += _wkey;
				_keyDown = true;
			}
		}
		else
			_keyDown = false;
	}
	else _keyDown = false;
}

void EndScreen::Render()
{
	wstring _scoreMessage = L"Score: " + to_wstring(m_stats->GetScore());

	m_spriteBatch->Begin();

	XMVECTOR _origin = m_font->MeasureString(L"Game Over");			//Game Over
	_origin = XMVectorSetY(_origin, 0);
	m_font->DrawString(m_spriteBatch.get(), 
		L"Game Over", 
		SimpleMath::Vector2(m_screenWidth/2, m_screenHeight/3), 
		DirectX::Colors::Crimson, 
		0.f, 
		_origin/2, 
		SimpleMath::Vector3(1.5f));

	_origin = m_font->MeasureString(_scoreMessage.c_str());			//Score amount
	_origin = XMVectorSetY(_origin, 0);
	m_font->DrawString(m_spriteBatch.get(),
		_scoreMessage.c_str(),
		SimpleMath::Vector2(m_screenWidth / 2, m_screenHeight / 3 + 60),
		DirectX::Colors::Crimson,
		0.f,
		_origin / 2);

	_origin = m_font->MeasureString(L"Input Name: ");				//"Input Name:" 
	_origin = XMVectorSetY(_origin, 0);
	m_font->DrawString(m_spriteBatch.get(),
		L"Input Name: ",
		SimpleMath::Vector2(m_screenWidth / 2, m_screenHeight / 2),
		DirectX::Colors::Crimson,
		0.f,
		_origin);

	m_font->DrawString(m_spriteBatch.get(),
		m_playerName.c_str(),
		SimpleMath::Vector2(m_screenWidth / 2, m_screenHeight / 2),
		DirectX::Colors::Crimson,
		0.f,
		SimpleMath::Vector2(0.f));
	

	m_spriteBatch->End();
}
