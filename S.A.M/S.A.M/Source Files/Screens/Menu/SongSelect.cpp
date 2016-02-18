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

	//Get filenames for all songtxts
	vector<string> _allSongFileNames = GetAllFilesNamesWithinFolder("Songs");

	//Make a SongElement for each song
	for (int i = 0; i < _allSongFileNames.size(); i++)
	{
		SongElement* _tempElement = new SongElement(_allSongFileNames[i], Device, ScreenHeight, ScreenWidth);
		m_songElements.push_back(_tempElement);
	}


}

SongSelect::~SongSelect()
{
	for (int i = 0; i < m_songElements.size(); i++)
		delete m_songElements[i];
}

void SongSelect::Update(double time)
{

}

void SongSelect::Render()
{

}

