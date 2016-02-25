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

void Shootingpatterns::AddShot(vector<Entity*>* Bullet, SoundManager * SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health, XMFLOAT3 Color, int Index)
{
	if (m_nrOfPatterns[Index] > 0)
	{
		for (auto i = 0; i < m_patterns[Index][m_bulletIndex[Index]]->m_vector.size(); i++)
		{
			(*Bullet).push_back(new Bullet_e(SoundManager, MapWidth, MapLength, Position, Scale, Health, Color, m_patterns[Index][m_bulletIndex[Index]]->m_vector[i]));
		}
		m_bulletIndex[Index]++;
		if (m_bulletIndex[Index] > m_nrOfPatterns[Index] - 1)
		{
			m_bulletIndex[Index] = 0;
		}
	}
	else
	{
		(*Bullet).push_back(new Bullet_e(SoundManager, MapWidth, MapLength, Position, Scale, Health, Color, XMFLOAT3(0, 0, -1)));
	}
}

void Shootingpatterns::LoadPatterns(const string &filename)
{
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
			m_bulletIndex[k] = 0;
		}
	}
	int _index = 0;
	ifstream _fileIn;

	_fileIn.open(filename, ifstream::in);

	bool _loop = true;
	char _input;

	if (_fileIn.is_open())
	{
		_input = _fileIn.get();
		while (_loop && !_fileIn.eof())
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
						_index = _input - 48;
						m_patterns[_index].push_back(new Pattern());
						m_nrOfPatterns[_index]++;
					}
				}
				break;
			/*case 'N':
				_input = _fileIn.get();
				if (_input == 'a')
				{
					string _name;
					while (_input != '\n')
					{
						_name += _input;
						_fileIn.get(_input);
					}
					m_patterns[m_nrOfPatterns - 1]->m_name = _name;
					m_patterns.push_back(new Pattern());
					m_nrOfPatterns++;
				}
				break;*/
			case 'V':	
				_input = _fileIn.get();
				if (_input == 'p')
				{
					XMFLOAT3 _Vec;
					_fileIn >> _Vec.x >> _Vec.y >> _Vec.z;
					m_patterns[_index][m_nrOfPatterns[_index] - 1]->m_vector.push_back(SPNormalizeFloat3(_Vec));
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