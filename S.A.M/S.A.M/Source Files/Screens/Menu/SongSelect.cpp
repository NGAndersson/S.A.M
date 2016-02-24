#include "../../../Header Files/Screens/Menu/SongSelect.h" 


vector<string> GetAllFilesNamesWithinFolder(string folder)
{
	vector<string> _names;
	char _searchPath[200];
	sprintf_s(_searchPath, "%s/*.txt", folder.c_str());
	WIN32_FIND_DATA _fd;
	HANDLE _hFind = ::FindFirstFile(_searchPath, &_fd);
	if (_hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(_fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				_names.push_back(_fd.cFileName);
			}
		} while (::FindNextFile(_hFind, &_fd));
		::FindClose(_hFind);
	}
	return _names;
}

SongSelect::SongSelect(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, Stats* stats, SoundManager* soundManager) : Screen(Device, DeviceContext, ScreenHeight, ScreenWidth, input)
{
	m_font = make_unique<SpriteFont>(Device, L"Resources/moonhouse.spritefont");
	
	//Set soundmanager
	m_soundManager = soundManager;

	m_input = input;
	m_screenHeight = ScreenHeight;
	m_screenWidth = ScreenWidth;

	//Get filenames for all songtxts
	vector<string> _allSongFileNames = GetAllFilesNamesWithinFolder("Resources/Songs");

	//Make a SongElement for each song
	for (int i = 0; i < _allSongFileNames.size(); i++)
	{
		SongElement* _tempElement = new SongElement(_allSongFileNames[i], Device, DeviceContext, m_soundManager);
		m_songElements.push_back(_tempElement);
	}

	//Position the visible songs
	for (int i = -2; i < 3; i++)
	{
		int _visibleIndex = m_selection + i;	//visible songs are around the current selected song
		if (_visibleIndex < 0)					//Wrap around on negative indexes
			_visibleIndex += m_songElements.size();
		if (_visibleIndex >= m_songElements.size())	//Wrap around on indexes above max
			_visibleIndex -= m_songElements.size();
		m_visibleElements[i + 2] = m_songElements[_visibleIndex];
	}
}

SongSelect::~SongSelect()
{
	for (int i = 0; i < m_songElements.size(); i++)
		delete m_songElements[i];
}

void SongSelect::Update(double time)
{
	static bool _movingUp = false;	 //For animations when switching song
	static bool _movingDown = false;

	//Position the visible songs
	for (int i = -2; i < 3; i++)
	{
		int _visibleIndex = m_selection + i;	//visible songs are around the current selected song
		if (_visibleIndex < 0)					//Wrap around on negative indexes
			_visibleIndex += m_songElements.size();
		if (_visibleIndex >= m_songElements.size())	//Wrap around on indexes above max
			_visibleIndex -= m_songElements.size();
		m_visibleElements[i + 2] = m_songElements[_visibleIndex];
	}

	static bool _keyDown = false;
	InputType _keyPressed = m_input->CheckKeyBoardInput();
	switch(_keyPressed) {
	case(INPUT_MOVE_DOWN) :
		if (_keyDown == false)
		{
			_movingUp = true, _movingDown = false;
			m_soundManager->StopMusic();	//Stop music if it's playing from another song
			m_selection++;
			if (m_selection >= m_songElements.size())
				m_selection = 0;
			_keyDown = true;
		}
		break;
	case(INPUT_MOVE_UP) :
		if (_keyDown == false)
		{
			_movingUp = false, _movingDown = true;
			m_soundManager->StopMusic();	//Stop music if it's playing from another song
			m_selection--;
			if (m_selection < 0)
				m_selection = m_songElements.size() - 1;
			_keyDown = true;
		}
		break;
	case (INPUT_MOVE_RIGHT) :
		m_soundManager->LoadMusic(m_songElements[m_selection]->GetFile());
		m_soundManager->PlayMusic(0.5f);
		break;
	default:
		_keyDown = false;
	}

	if (_movingUp == true)	//Selection is moving down, so choices are moving up
	{

	}

}

void SongSelect::Render()
{
	for (int i = 0; i < 5; i++)
	{
		int _xpos = 400;
		if (i == 2)
			_xpos = 100;
		m_visibleElements[i]->Render(_xpos, i * 100 + m_screenHeight/2 - 250);		//Get it centered, y-wise

	}
}
