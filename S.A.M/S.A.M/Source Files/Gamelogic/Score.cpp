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
		
	// If file is not empty, read all so we can sort them
	std::pair<std::string, int> _inData[10] = { {"", 0} };
	
	std::string _tempLine;
	int i = 0;
	while (getline(_file, _tempLine))				//Format:		1|Name|1000			Position|Name|Score
	{
		char* _tempChars = "";
		std::istringstream _ss(_tempLine);
		_ss.get(NULL, 100, '|');			//Throw away position and delim (Assume they are in order to begin with

		_ss.get(_tempChars, 100, '|');		//Read name
		_inData[i].first = _tempChars;

		_ss.get(_tempChars, 100, '|');		//Get Score
		_inData[i].second = std::atoi(_tempChars);
		i++;
	}

	bool _placed = false;
	std::pair<std::string, int> _outData[10] = { { "", 0 } };
	for (int i = 0, j = 0; i < 10; i++, j++)
	{
		if (m_score > _inData[i].second && !_placed)		//current score is bigger than score at pos i
		{
			_outData[i].first = playername;
			_outData[i].second = m_score;
			i++;
			_placed = true;
		}

		if (i != 10) {									//Add in existing score
			_outData[i] = _inData[j];
		}
	}
	
	//Clear and write file
	_file.clear();
	for (i = 0; i < 10; i++) {
		_file << i << '|' << _outData[i].first << '|' << _outData[i].second << std::endl;
	}
	_file.close();
}

bool Score::LoadScore(std::string filename)
{
	std::ifstream _file;
	std::string _filepath = "score/" + filename;

	// If file is not empty, read all so we can sort them
	std::pair<std::string, int> _inData[10] = { { "", 0 } };

	std::string _tempLine;
	int i = 0;
	while (getline(_file, _tempLine))				//Format:		1|Name|1000			Position|Name|Score
	{
		char* _tempChars = "";
		std::istringstream _ss(_tempLine);
		_ss.get(NULL, 100, '|');			//Throw away position and delim (Assume they are in order to begin with

		_ss.get(_tempChars, 100, '|');		//Read name
		_inData[i].first = _tempChars;

		_ss.get(_tempChars, 100, '|');		//Get Score
		_inData[i].second = std::atoi(_tempChars);
		i++;
	}

	//DO MORE SHIT WHEN WE KNOW WHAT MORE SHIT IS
	return false;
}
