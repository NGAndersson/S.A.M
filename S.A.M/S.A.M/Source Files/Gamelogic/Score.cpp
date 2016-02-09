#include "..\..\Header Files\Gamelogic\Score.h"


Score::Score()
{
	m_score = 0;
}

Score::~Score()
{
}

void Score::AddScore(int add)
{
	m_score += add;
}

void Score::ResetScore()
{
	m_score = 0;
}

bool Score::SaveScore(std::string filename, std::string playername)
{
	std::fstream _file;
	std::string _filepath = "score/" + filename;		//Opens a file in a folder called score
	_file.open(_filepath);
	if(!_file.is_open())		//If file failed to open, return false
		return false;

	if (_file.peek() == std::fstream::traits_type::eof()) //If file is empty to begin with, just write down our new score
	{
		_file << "1|" << playername.c_str() << "|" << m_score << std::endl;
		return true;
	}
	
	_file.close();
	LoadScore(filename);
	_file.open(_filepath);

	bool _placed = false;
	std::pair<std::string, int> _outData[10] = { { "", 0 } };
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

bool Score::LoadScore(std::string filename)
{
	std::fstream _file;
	std::string _filepath = "score/" + filename;
	_file.open(_filepath);

	// If file is not empty, read all so we can sort them
	std::pair<std::string, int> _inData[10] = { { "", 0 } };

	char _tempChars[100];
	std::string _tempLine;
	int i = 0;
	while (getline(_file, _tempLine))				//Format:		1|Name|1000			Position|Name|Score
	{
		
		std::istringstream _ss(_tempLine);
		_ss.get(_tempChars, 100, '|');			//Throw away position and delim
		_ss.ignore();

		_ss.get(_tempChars, 100, '|');		//Read name
		_inData[i].first = _tempChars;
		_ss.ignore();

		_ss.get(_tempChars, 100, '|');		//Get Score
		_inData[i].second = std::atoi(_tempChars);
		i++;
	}

	for (i = 0; i < 10 && _inData[i].second > 0; i++)
		m_highScores[i] = _inData[i];

	_file.close();

	//DO MORE SHIT WHEN WE KNOW WHAT MORE SHIT IS
	return true;
}
