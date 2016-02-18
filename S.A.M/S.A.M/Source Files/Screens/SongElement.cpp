#include "..\..\Header Files\Screens\SongElement.h"

SongElement::SongElement(std::string filename, ID3D11Device* device, int ScreenHeight, int ScreenWidth)
{
	m_font = std::make_unique<DirectX::SpriteFont>(device, L"Resources/moonhouse.spritefont");


	//Load meta-data
	std::wfstream _file;
	_file.open("Resources/Songs/"+filename);

	wchar_t _key[100];
	wchar_t _value[100];
	std::wstring _tempLine;
	while (getline(_file, _tempLine))
	{
		std::wstringstream _ss(_tempLine);

		_ss.get(_key, 100, '=');		//Get field name
		_ss.ignore();
		if (_key[0] != '#') {				//Skip comment lines
			_ss.get(_value, 100, '=');		//Get value
			if (std::wstring(_key) == L"songname")
				m_songName = _value;		
			if (std::wstring(_key) == L"artist")
				m_artist = _value;		
			if (std::wstring(_key) == L"arr")
				m_arranger = _value;		
			if (std::wstring(_key) == L"music")
				m_file = _value;
		}
	}
	//---------------
	
	DirectX::CreateWICTextureFromFile(device, L"Resources/SongElement.png", nullptr, m_backGround.ReleaseAndGetAddressOf());
}

SongElement::~SongElement()
{
}

void SongElement::Render(int offsetX, int offsetZ)
{
	DirectX::SimpleMath::Vector2 _namePos, _artistPos, _arrPos, _lengthPos, _bpmPos;
	_namePos.x = 0, _namePos.y = 0;
	_artistPos.x = 0, _artistPos.y = 70;
	_arrPos.x = 400, _arrPos.y = 0;
	_lengthPos.x = 500, _lengthPos.y = 70;
	_bpmPos.x = 550, _bpmPos.y = 70;

	

	/*
	SimpleMath::Vector2 _scorePos, _livesPos, _comboPos;
	_scorePos.x = m_screenWidth / 2;
	_scorePos.y = 40;
	_livesPos.x = 100;
	_livesPos.y = m_screenHeight - 40;
	_comboPos.x = m_screenWidth - 150, _comboPos.y = m_screenHeight - 40;

	wstring _tempHighScore = L"High Score: " + m_score;
	wstring _tempLives = L"Lives: " + m_livesLeft;
	wstring _tempCombo = L"Combo: " + m_combo;
	m_spriteBatch->Begin();
	m_font->DrawString(m_spriteBatch.get(), _tempHighScore.c_str(), _scorePos, Colors::Crimson, 0.f, m_font->MeasureString(_tempHighScore.c_str()) / 2.f);
	m_font->DrawString(m_spriteBatch.get(), _tempLives.c_str(), _livesPos, Colors::Crimson, 0.f, m_font->MeasureString(_tempLives.c_str()) / 2.f);
	m_font->DrawString(m_spriteBatch.get(), _tempCombo.c_str(), _comboPos, Colors::Crimson, 0.f, m_font->MeasureString(_tempCombo.c_str()) / 2.f);
	m_spriteBatch->End();
	*/
}
