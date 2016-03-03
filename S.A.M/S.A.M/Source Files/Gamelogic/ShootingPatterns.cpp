#include "Gamelogic/ShootingPatterns.h"

XMFLOAT3 SPNormalizeFloat3(XMFLOAT3 pos)
{
	float _divider = sqrt((pos.x * pos.x) + (pos.y * pos.y) + (pos.z * pos.z));
	XMFLOAT3 _normalized = XMFLOAT3(pos.x / _divider, pos.y / _divider, pos.z / _divider);

	return _normalized;
}

Shootingpatterns::Shootingpatterns()
{
	m_nrOfPatterns[0] = 0;
	m_nrOfPatterns[1] = 0;
	m_nrOfPatterns[2] = 0;
	m_nrOfPatterns[3] = 0;
}

Shootingpatterns::~Shootingpatterns()
{

}

int Shootingpatterns::AddShot(vector<Entity*>* Bullet, SoundManager * SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health, XMFLOAT3 Color, int Index, int ShootNr)
{
	if (m_nrOfPatterns[Index] > 0)	//if there is a pattern for this entity
	{
		for (auto i = 0; i < m_patterns[Index][ShootNr]->m_vector.size(); i++)
		{
			if ((*Bullet).size() < 100)	//makes sure that there can't be more then 100 enemy bullets
			{
				(*Bullet).push_back(new Bullet_e(SoundManager, MapWidth, MapLength, Position, Scale, Health, Color, m_patterns[Index][ShootNr]->m_vector[i]));	//adds bullet
			}
		}
		if (ShootNr < m_nrOfPatterns[Index] - 1)
			return ShootNr + 1;
		else
			return 0;
	}
	else  //stright shoot down
	{
		if ((*Bullet).size() < 100)	//makes sure that there can't be more then 100 enemy bullets
		{
			(*Bullet).push_back(new Bullet_e(SoundManager, MapWidth, MapLength, Position, Scale, Health, Color, XMFLOAT3(0, 0, -1)));	//adds bullet
		}
		return 0;
	}
}

void Shootingpatterns::LoadPatterns(const string &filename)
{
	//resets values if already set
	for (auto k = 0; k < 4; k++)
	{
		if (m_nrOfPatterns[k] != 0)
		{
			vector<Pattern*> _tempVec = m_patterns[k];
			for (auto i = 0; i < _tempVec.size(); i++)
			{
				delete _tempVec[i];
				_tempVec.erase(_tempVec.begin() + i);
			}
			m_patterns[k] = _tempVec;
			m_nrOfPatterns[k] = 0;
		}
	}
	int _index = 0;
	ifstream _fileIn;

	//opens file by filename
	_fileIn.open(filename, ifstream::in);

	bool _loop = true;
	char _input;

	if (_fileIn.is_open())
	{
		_input = _fileIn.get();
		while (_loop && !_fileIn.eof())	//loops until end of file or error reading file
		{
			switch (_input)
			{

			case 'P':
				_input = _fileIn.get();
				if (_input == 'a')
				{
					_input = _fileIn.get();
					if (_input == ' ')
					{
						_input = _fileIn.get();
						_index = _input - 48 - 1;	//reads in the index number -48 becuase of ascii, -1 because enemytypes are 1-4 in file not 0-3
						m_patterns[_index].push_back(new Pattern());
						m_nrOfPatterns[_index]++;	//adds to number of patterns
					}
				}
				break;
			case 'V':	
				_input = _fileIn.get();
				if (_input == 'p')
				{
					_input = _fileIn.get();
					if (_input == ' ')
					{
						XMFLOAT3 _Vec;
						_Vec.y = 0.0f;
						_fileIn >> _Vec.x >> _Vec.z;	//reads the vector
						m_patterns[_index][m_nrOfPatterns[_index] - 1]->m_vector.push_back(SPNormalizeFloat3(_Vec));	//saves the vector to the patter vector
					}
				}
				break;
			}
			if (_fileIn.fail())
			{
				_loop = false;
			}
			_input = _fileIn.get();
		}

		_fileIn.close();
	}
}

int Shootingpatterns::GetNrOfPatterns(int index)
{
	return m_nrOfPatterns[index];
}