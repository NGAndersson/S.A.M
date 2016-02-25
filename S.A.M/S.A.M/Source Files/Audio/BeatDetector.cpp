#include "Audio\BeatDetector.h"

#include <cmath>
#include <vector>

#define K_ENERGIE_RATIO  1.3 // le ratio entre les energie1024 et energie44100 pour la détection des peak d'energie
#define K_TRAIN_DIMP_SIZE 108 // la taille du train d'impulsions pour la convolution (en pack de 1024 (430=10sec))

using namespace std;

BeatDetector::BeatDetector(SoundManager* snd_mgr)
{
	this->m_soundManager = snd_mgr;
	m_length = snd_mgr->GetLength();
	m_energy1024 = new float[m_length / 1024];
	m_energy44100 = new float[m_length / 1024];
	m_conv = new float[m_length / 1024];
	m_beat = new float[m_length / 1024];
	m_energyPeak = new float[m_length / 1024 + 21];
	for (int i = 0; i<m_length / 1024 + 21; i++) m_energyPeak[i] = 0;
}

BeatDetector::~BeatDetector()
{
	delete[] m_energy1024;
	delete[] m_energy44100;
	delete[] m_conv;
	delete[] m_beat;
	delete[] m_energyPeak;
}

int BeatDetector::Energy(int* data, int offset, int window)
{
	float _energy = 0.f;
	for (int i = offset; (i<offset + window) && (i<m_length); i++)
	{
		_energy = _energy + data[i] * data[i] / window;
	}
	return (int)_energy;
}

void BeatDetector::Normalize(float* signal, int size, float max_val)
{
	
	// recherche de la valeur max du signal
	float _max = 0.f;
	for (int i = 0; i<size; i++)
	{
		if (abs(signal[i])>_max) _max = abs(signal[i]);
	}
	// ajustage du signal
	float _ratio = max_val / _max;
	for (int i = 0; i<size; i++)
	{
		signal[i] = signal[i] * _ratio;
	}

	int k = 0;
}

int BeatDetector::SearchMax(float* signal, int pos, int window_half_size)
{
	float _max = 0.f;
	int _maxPos = pos;
	for (int i = pos - window_half_size; i <= pos + window_half_size; i++)
	{
		if (signal[i]>_max)
		{
			_max = signal[i];
			_maxPos = i;
		}
	}
	return _maxPos;
}

void BeatDetector::AudioProcess(void)
{
	// recupere les données de la musique
	// ----------------------------------
	// le canal gauche
	int* data = m_soundManager->GetLeftData();

	// calcul des energies instantannées
	// ---------------------------------
	for (int i = 0; i<m_length / 1024; i++)
	{
		m_energy1024[i] = Energy(data, 1024 * i, 4096); // 4096 pour lisser un peu la courbe
	}
	// calcul des energies moyennes sur 1 seconde
	// ------------------------------------------
	m_energy44100[0] = 0;
	// la moyenne des 43 premiers energies1024 donne l'energie44100 de la premiere seconde
	float _sum = 0.f;
	for (int i = 0; i<43; i++)
	{
		_sum = _sum + m_energy1024[i];
	}
	m_energy44100[0] = _sum / 43;

	// pour toutes les autres, ...
	for (int i = 1; i<m_length / 1024; i++)
	{
		_sum = _sum - m_energy1024[i - 1] + m_energy1024[i + 42];
		m_energy44100[i] = _sum / 43;
	}

	// Ratio energie1024/energie44100
	// ------------------------------
	for (int i = 21; i<m_length / 1024; i++)
	{
		// -21 pour centrer le energie1024 sur la seconde du energie44100
		if (m_energy1024[i]>K_ENERGIE_RATIO*m_energy44100[i - 21])
		{
			m_energyPeak[i] = 1;
		}
	}

	// Calculating BPMs
	// ---------------
	// calcul des laps de temps entre chaque energie_peak
	vector<int> _T;
	int _iPrec = 0;
	for (int i = 1; i<m_length / 1024; i++)
	{
		if ((m_energyPeak[i] == 1) && (m_energyPeak[i - 1] == 0))
		{
			int _di = i - _iPrec;
			if (_di>5) // rien pour les parasites
			{
				_T.push_back(_di);
				_iPrec = i;
			}
		}
	}
	// le tableau T contient tous les laps de temps
	// fait des stats pour savoir quel est le plus fréquent
	int _TOccMax = 0;
	float _TOccMoy = 0.f;

	// compte les occurence de chaque laps de temps
	int _occurencesT[86]; // max 2 paquets de 43 d'écart (2sec)
	for (int i = 0; i<86; i++) _occurencesT[i] = 0;
	for (int i = 1; i<_T.size(); i++)
	{
		if (_T[i] <= 86) _occurencesT[_T[i]]++;
	}
	int _occMax = 0;
	for (int i = 1; i<86; i++)
	{
		if (_occurencesT[i]>_occMax)
		{
			_TOccMax = i;
			_occMax = _occurencesT[i];
		}
	}
	// on fait la moyenne du max + son max de voisin pour + de précision
	int _voisin = _TOccMax - 1;
	if (_occurencesT[_TOccMax + 1]>_occurencesT[_voisin]) _voisin = _TOccMax + 1;
	float _div = _occurencesT[_TOccMax] + _occurencesT[_voisin];

	if (_div == 0) _TOccMoy = 0;
	else _TOccMoy = (float)(_TOccMax*_occurencesT[_TOccMax] + (_voisin)*_occurencesT[_voisin]) / _div;

	// clacul du tempo en BPMs
	m_tempo = (int)60.f / (_TOccMoy*(1024.f / 44100.f));

	// Calcul de la Beat line
	// ----------------------
	// création d'un train d'impulsions (doit valoir 1 tous les T_occ_moy et 0 ailleurs)
	float _trainDimp[K_TRAIN_DIMP_SIZE];
	float _espace = 0.f;
	_trainDimp[0] = 1.f;
	for (int i = 1; i<K_TRAIN_DIMP_SIZE; i++)
	{
		if (_espace >= _TOccMoy)
		{
			_trainDimp[i] = 1;
			_espace = _espace - _TOccMoy; // on garde le depassement
		}
		else _trainDimp[i] = 0;
		_espace += 1.f;
	}

	// convolution avec l'énergir instantannée de la music
	for (int i = 0; i<m_length / 1024 - K_TRAIN_DIMP_SIZE; i++)
	{
		for (int j = 0; j<K_TRAIN_DIMP_SIZE; j++)
		{
			m_conv[i] = m_conv[i] + m_energy1024[i + j] * _trainDimp[j];
		}

	}
	Normalize(m_conv, m_length / 1024, 1.f);

	// recherche des peak de la conv
	// le max (c'est la plupart du temps un beat (pas tout le temps ...))
	for (int i = 1; i<m_length / 1024; i++)
		m_beat[i] = 0;

	float _maxConv = 0.f;
	int _maxConvPos = 0;
	for (int i = 1; i<m_length / 1024; i++)
	{
		if (m_conv[i]>_maxConv)
		{
			_maxConv = m_conv[i];
			_maxConvPos = i;
		}
	}
	m_beat[_maxConvPos] = 1.f;

	// les suivants
	// vers la droite
	int i = _maxConvPos + _TOccMax;
	while ((i<m_length / 1024)/* && (m_conv[i]>0.f)*/)
	{
		// on cherche un max dans les parages
		int conv_max_pos_loc = SearchMax(m_conv, i, 2);
		m_beat[conv_max_pos_loc] = 1.f;
		i = conv_max_pos_loc + _TOccMax;
	}
	// vers la gauche
	i = _maxConvPos - _TOccMax;
	while (i>0)
	{
		// on cherche un max dans les parages
		int _convMaxPosLoc = SearchMax(m_conv, i, 2);
		m_beat[_convMaxPosLoc] = 1.f;
		i = _convMaxPosLoc - _TOccMax;
	}
	float tempp[9000];
	for (int i = 0; i < m_length / 1024; i++)
		tempp[i] = m_beat[i];

	int l = 0;

}

float* BeatDetector::GetEnergy1024(void)
{
	return m_energy1024;
}

float* BeatDetector::GetEnergy44100(void)
{
	return m_energy44100;
}

float* BeatDetector::GetEnergyPeak(void)
{
	return m_energyPeak;
}

float* BeatDetector::GetConv()
{
	return m_conv;
}

float* BeatDetector::GetBeat()
{
	return m_beat;
}

int BeatDetector::GetTempo(void)
{
	return m_tempo;
}
