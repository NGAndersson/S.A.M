#include "..\..\Header Files\Gamelogic\Stats.h"


Stats::Stats()
{
	m_score = 0;
}

Stats::~Stats()
{
}

void Stats::AddScore(int add)
{
	m_score += add;
}

void Stats::ResetScore()
{
	m_score = 0;
}

bool Stats::SaveScore(std::wstring playername)
{
	std::wfstream _file;
	_file.open(m_filename);
	if(!_file.is_open())		//If file failed to open, return false
		return false;

	if (_file.peek() == std::fstream::traits_type::eof()) //If file is empty to begin with, just write down our new score
	{
		_file << "1|" << playername.c_str() << "|" << m_score << std::endl;
		return true;
	}
	
	_file.close();
	LoadScore();
	_file.open(m_filename);

	bool _placed = false;
	std::pair<std::wstring, int> _outData[10] = { { L"", 0 } };
	for (int i = 0, j = 0; i < 10; i++, j++)
	{
		if (m_score > m_highScores[i].second && !_placed)		//current score is bigger than score at pos i
		{
			_outData[i].first = playername;
			_outData[i].second = m_score;
			i++;
			_placed = true;
		}

		if (i != 10) {									//Add in existing score
			_outData[i] = m_highScores[j];
		}
	}
	
	//Clear and write file
	_file.clear();
	for (int i = 0; i < 10; i++) {
		_file << i+1 << '|' << _outData[i].first << '|' << _outData[i].second << std::endl;
	}
	_file.close();
}

bool Stats::LoadScore()
{
	std::wfstream _file;
	_file.open(m_filename);

	// If file is not empty, read all so we can sort them
	std::pair<std::wstring, int> _inData[10] = { { L"", 0 } };

	wchar_t _tempChars[100];
	std::wstring _tempLine;
	int i = 0;
	while (getline(_file, _tempLine))				//Format:		1|Name|1000			Position|Name|Score
	{
		if (_tempLine != L"")
		{
			std::wistringstream _ss(_tempLine);
			_ss.get(_tempChars, 100, '|');			//Throw away position and delim
			_ss.ignore();

			_ss.get(_tempChars, 100, '|');		//Read name
			_inData[i].first = _tempChars;
			_ss.ignore();

			_ss.get(_tempChars, 100, '|');		//Get Score
			_inData[i].second = _wtoi(_tempChars);
			i++;
		}
	}

	for (i = 0; i < 10; i++)
		m_highScores[i] = _inData[i];

	_file.close();

	return true;
}
