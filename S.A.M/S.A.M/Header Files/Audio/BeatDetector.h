#ifndef _BEATDETECTOR_H
#define _BEATDETECTOR_H

#include "SoundManager.h"

class BeatDetector
{
public:
	BeatDetector(SoundManager* snd_mgr);
	~BeatDetector();
	void AudioProcess();

	float* GetEnergy1024();
	float* GetEnergy44100();
	float* GetEnergyPeak();
	float* GetConv();
	float* GetBeat();
	int GetTempo();

private:
	SoundManager* m_soundManager;
	int m_length;    // in PCM
	float* m_energy1024; // energy of 1024 samples computed every 1024 pcm
	float* m_energy44100; // energy of 44100 samples computed every 1024 pcm
	float* m_energyPeak; // Estimated beats
	float* m_conv; // la convolution avec un train d'impulsions  ???
	float* m_beat; // la beat line
	int m_tempo; // Tempo in BPMs

	int Energy(int* data, int offset, int window); // calcul l'energie du signal a une position et sur une largeur donnée
	void Normalize(float* signal, int size, float max_val); // reajuste les valeurs d'un signal à la valeur max souhaitée
	int SearchMax(float* signal, int pos, int window_half_size); // recherche d'un max dans les parages de pos
};

#endif
