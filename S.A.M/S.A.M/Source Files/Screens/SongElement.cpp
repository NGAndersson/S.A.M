#include "..\..\Header Files\Screens\SongElement.h"

SongElement::SongElement(std::string filename, ID3D11Device* device, ID3D11DeviceContext* DeviceContext, SoundManager* soundManager)
{
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(DeviceContext);
	m_font = std::make_unique<DirectX::SpriteFont>(device, L"Resources/moonhouse.spritefont");
	m_soundManager = soundManager;
	std::wstring _filePath;
	std::wstring _scorePath;
	m_dataFile = "Resources/Songs/" + filename;

	//Load meta-data
	std::wfstream _file;
	_file.open(m_dataFile);

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
				_filePath = _value;
			if (std::wstring(_key) == L"score")
				_scorePath = _value;
		}
	}
	_file.close();

	size_t _numcharbullshit;
	wcstombs_s(&_numcharbullshit, m_file, (size_t)200, _filePath.c_str(), (size_t)200);
	wcstombs_s(&_numcharbullshit, m_scoreFile, (size_t)200, _scorePath.c_str(), (size_t)200);
	m_soundManager->LoadMusic(m_file);
	BeatDetector _beatDetector(m_soundManager);
	_beatDetector.AudioProcess();
	
	m_bpm = std::to_wstring(_beatDetector.GetTempo());

	int _lengthMS = m_soundManager->GetLengthMS();
	int _seconds = _lengthMS / 1000;
	int _minutes = _seconds / 60;
	_seconds = _seconds % 60;
	std::wstring _secString;
	if (_seconds < 10)
		_secString = L"0" + std::to_wstring(_seconds);
	else
		_secString = std::to_wstring(_seconds);

	m_length = std::to_wstring(_minutes) + L":" + _secString;

	//---------------
	
	Microsoft::WRL::ComPtr<ID3D11Resource> _resource;
	DirectX::CreateWICTextureFromFile(device, L"Resources/Sprites/SongElement.png", _resource.GetAddressOf(), m_backGround.ReleaseAndGetAddressOf());
	
	Microsoft::WRL::ComPtr<ID3D11Texture2D> _bg;
	_resource.As(&_bg);

	CD3D11_TEXTURE2D_DESC _bgDesc;
	_bg->GetDesc(&_bgDesc);
	
	m_states = std::make_unique<DirectX::CommonStates>(device);


}

SongElement::~SongElement()
{
	m_backGround.Reset();
	m_states.reset();
}

void SongElement::Render(int offsetX, int offsetZ)
{
	DirectX::SimpleMath::Vector2 _bgPos, _songNamePos, _artistPos, _arrangerPos, _lengthAndBPMPos;
	_bgPos.x = offsetX, _bgPos.y = offsetZ;
	_songNamePos.x = 0 + offsetX, _songNamePos.y = 20 + offsetZ;
	_artistPos.x = 0 + offsetX, _artistPos.y = 70 + offsetZ;
	_arrangerPos.x = 600 + offsetX, _arrangerPos.y = 20 + offsetZ;
	_lengthAndBPMPos.x = 600 + offsetX, _lengthAndBPMPos.y = 70 + offsetZ;
	std::wstring _lengthAndBPM = m_length + L" " + m_bpm + L" BPM";
	
	DirectX::XMVECTOR _lengthAndBPMOrigin = m_font->MeasureString(_lengthAndBPM.c_str());
	_lengthAndBPMOrigin = DirectX::XMVectorSetIntY(_lengthAndBPMOrigin, 0);

	DirectX::XMVECTOR _arrangerOrigin = m_font->MeasureString(m_arranger.c_str());
	_arrangerOrigin = DirectX::XMVectorSetIntY(_arrangerOrigin, 0);

	DirectX::SimpleMath::Vector3 _scale;
	_scale.x = 0.5f, _scale.y = 0.5f, _scale.z = 0.5f;

	m_spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, m_states->NonPremultiplied());
	m_spriteBatch->Draw(m_backGround.Get(), _bgPos, nullptr, DirectX::Colors::White, 0.f);
	m_font->DrawString(m_spriteBatch.get(), m_songName.c_str(), _songNamePos, DirectX::Colors::White, 0.f);
	m_font->DrawString(m_spriteBatch.get(), m_artist.c_str(), _artistPos, DirectX::Colors::White, 0.f, DirectX::g_XMZero, _scale);
	m_font->DrawString(m_spriteBatch.get(), m_arranger.c_str(), _arrangerPos, DirectX::Colors::White, 0.f, _arrangerOrigin, _scale);
	m_font->DrawString(m_spriteBatch.get(), _lengthAndBPM.c_str(), _lengthAndBPMPos, DirectX::Colors::White, 0.f, _lengthAndBPMOrigin, _scale);
	m_spriteBatch->End();
}
