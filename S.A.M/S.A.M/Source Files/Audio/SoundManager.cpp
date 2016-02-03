#include "Audio/SoundManager.h"
#include "Windows.h"
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <algorithm>

SoundManager::SoundManager() 
{
	InitFMOD();
}

SoundManager::~SoundManager()
{
	//Release the resources
	m_system->release();
	for (int i = 0; i < (int)m_sounds.size(); i++)
	{
		for (int j = 0; j < (int)m_sounds[i].size(); j++)
			m_sounds[i][j]->release();
	}
}

void SoundManager::MessageBoxAndShutDown(std::stringstream* _ss) {
	std::string _boxStringS(_ss->str());
	const char* _boxStringLPCSTR = _boxStringS.c_str();

	//Displays error box and quits the game
	MessageBox(NULL,
		_boxStringLPCSTR,
		"Sound Error",
		MB_ICONERROR | MB_OK);
	exit(-1);
}


void SoundManager::FindSoundIndex(char* soundName, int &groupIndex, int &soundIndex)
{
	//Go through EVERY index vector in to find sound name
	for (int i = 0; i < (int)m_soundGroupIndexes.size(); i++)
	{
		//Check if we're looking for a whole group or a specific sound
		if (m_soundGroupIndexes[i] == soundName)
		{
			groupIndex = i;
			soundIndex = -1;
			return;
		}

		//Go through the index vector in the group to find index of correct sound
		for (int j = 0; j < (int)m_soundIndexes[i].size(); j++)
		{
			if (m_soundIndexes[i][j] == soundName)
			{
				soundIndex = j;
				groupIndex = i;
				return;
			}
		}
	}
	groupIndex = -1;
	soundIndex = -1;
}

int SoundManager::FindGroupIndex(char * groupName)
{
	//Go through EVERY index vector in to find sound name
	for (int i = 0; i < (int)m_soundGroupIndexes.size(); i++)
	{
		//Check if we're looking for a whole group or a specific sound
		if (m_soundGroupIndexes[i] == groupName)
		{
			return i;
		}
	}
	return -1;
}

void SoundManager::LoadSound(char* fileName, char* soundName, char* groupName, SoundFlags flags)
{
	FMOD::Sound* audio;

	//Either load into memory or as a stream
	if (flags & LOAD_MEMORY) {
		if (flags & LOAD_SOFTWARE)
			m_result = m_system->createSound(fileName, FMOD_SOFTWARE, 0, &audio);
		else
			m_result = m_system->createSound(fileName, FMOD_DEFAULT, 0, &audio);
	}
	else if (flags & LOAD_STREAM)
		if (flags & LOAD_SOFTWARE)
			m_result = m_system->createStream(fileName, FMOD_SOFTWARE, 0, &audio);
		else
			m_result = m_system->createStream(fileName, FMOD_DEFAULT, 0, &audio);
	else	//No mode set
	{
		MessageBox(NULL, "No Loadmode Set", "Sound Loading Error", MB_ICONERROR | MB_OK);
		exit(-1);
	}
	
	
	FMODErrorCheck(m_result);

	//Add audio, sound name and channel to their vectors
	FMOD::Channel* channel;
	int _groupIndex = FindGroupIndex(groupName);

	if (_groupIndex != -1)
	{
		m_soundChannels[_groupIndex].push_back(channel);
		m_sounds[_groupIndex].push_back(audio);
		m_soundIndexes[_groupIndex].push_back(soundName);
	}
	else {
		std::vector<FMOD::Channel*> _newChannelVec;
		std::vector<FMOD::Sound*> _newSoundVec;
		std::vector<char*> _newIndexVec;

		_newChannelVec.push_back(channel);
		_newSoundVec.push_back(audio);
		_newIndexVec.push_back(soundName);

		m_soundChannels.push_back(_newChannelVec);
		m_sounds.push_back(_newSoundVec);
		m_soundIndexes.push_back(_newIndexVec);
		m_soundGroupIndexes.push_back(groupName);		
	}
}

void SoundManager::PauseSound(char* soundName)
{
	int _groupIndex, _soundIndex;
	FindSoundIndex(soundName, _groupIndex, _soundIndex);

	if (_groupIndex != -1 && _soundIndex != -1)
	{
		bool isPaused;
		m_soundChannels[_groupIndex][_soundIndex]->getPaused(&isPaused);
		m_soundChannels[_groupIndex][_soundIndex]->setPaused(!isPaused);
	}
	else if (_groupIndex != -1)
	{
		for (int i = 0; i < m_soundChannels[_groupIndex].size(); i++) 
		{
			bool _paused;
			m_soundChannels[_groupIndex][i]->getPaused(&_paused);
			if (_paused == false)
				m_soundChannels[_groupIndex][i]->setPaused(true);
		}
	}
	else {
		MessageBox(NULL, "Couldn't find sound name handle", "Sound Pausing Error", MB_ICONERROR | MB_OK);
		exit(-1);
	}
}

void SoundManager::Update()
{
	m_system->update();
}

float* SoundManager::SpectrumAnalysis(char* soundName)
{
	int _groupIndex = -1, _soundIndex = -1;
	FindSoundIndex(soundName, _groupIndex, _soundIndex);
	//If only groupindex was found, pick a random sound (good for music where there should only be one sound)
	if (_groupIndex != -1 && _soundIndex == -1) {
		//Play random sound from the group
		srand(time(NULL));
		_soundIndex = rand() % m_sounds[_groupIndex].size();
	}
	else if (_groupIndex == -1 && _soundIndex == -1) {
		MessageBox(NULL, "Couldn't find sound name handle", "Spectrum Analysis Error", MB_ICONERROR | MB_OK);
		exit(-1);
	}


	int _sampleSize = 124;

	//Get the volume of the left and right channel (0-1)
	float *_specLeft, *_specRight;
	_specLeft = new float[_sampleSize];
	_specRight = new float[_sampleSize];
	m_soundChannels[_groupIndex][_soundIndex]->getSpectrum(_specLeft, _sampleSize, 0, FMOD_DSP_FFT_WINDOW_RECT);
	m_soundChannels[_groupIndex][_soundIndex]->getSpectrum(_specRight, _sampleSize, 1, FMOD_DSP_FFT_WINDOW_RECT);

	//Take the average of the left and right volume (0-1)
	float* _spec;
	_spec = new float[_sampleSize];
	for (int i = 0; i < _sampleSize; i++)
		_spec[i] = (_specLeft[i] + _specRight[i]) / 2;

	//Find max volume
	auto _maxIterator = std::max_element(&_spec[0], &_spec[_sampleSize]);
	float _maxVol = *_maxIterator;

	//Normalize
	if (_maxVol != 0)
		std::transform(&_spec[0], &_spec[_sampleSize], &_spec[0], [_maxVol](float dB) -> float {return dB / _maxVol; });
	
	delete[] _specLeft;
	delete[] _specRight;
	return _spec;
}

int SoundManager::GetCurrentMusicTimePCM()
{
	unsigned int _pos = 0;
	m_musicChannel->getPosition(&_pos, FMOD_TIMEUNIT_PCM);
	return _pos;
}

//Plays a sound once at a specific volume
void SoundManager::PlayOneShotSound(char* soundName, float volume)
{
	int _groupIndex = -1, _soundIndex = -1;
	FindSoundIndex(soundName, _groupIndex, _soundIndex);
	
	//If the sound was found, play it!
	if (_groupIndex != -1 && _soundIndex != -1) 
	{
		m_result = m_system->playSound(FMOD_CHANNEL_FREE, m_sounds[_groupIndex][_soundIndex], false, &m_soundChannels[_groupIndex][_soundIndex]);
		m_soundChannels[_groupIndex][_soundIndex]->setVolume(volume);
		FMODErrorCheck(m_result);
	}
	else if (_groupIndex != -1) {
		//Play random sound from the group
		srand(time(NULL));
		int _randomInt = rand() % m_sounds[_groupIndex].size();

		m_result = m_system->playSound(FMOD_CHANNEL_FREE, m_sounds[_groupIndex][_randomInt], false, &m_soundChannels[_groupIndex][_randomInt]);
		m_soundChannels[_groupIndex][_randomInt]->setVolume(volume);
		FMODErrorCheck(m_result);
	}

	else {
		MessageBox(NULL, "Couldn't find sound name handle", "Sound Playing Error", MB_ICONERROR | MB_OK);
		exit(-1);
	}
}

void SoundManager::LoadMusic(char * fileName)
{
	m_result = m_system->createSound(fileName, FMOD_SOFTWARE, 0, &m_musicSound);

	FMODErrorCheck(m_result);
	m_musicSound->getLength(&m_musicLength, FMOD_TIMEUNIT_PCM);

	//Weird stuff from french code	https://www.youtube.com/watch?v=jZoQ1S73Bac
	void* _ptr1;
	void* _ptr2;
	unsigned int _length1;
	unsigned int _length2;
	m_dataLeftChannel = new int[m_musicLength];
	m_dataRightChannel = new int[m_musicLength];
	m_musicSound->lock(0, m_musicLength, &_ptr1, &_ptr2, &_length1, &_length2);
	for (int i = 0; i < m_musicLength; i++)
	{
		m_dataLeftChannel[i] = ((int*)_ptr1)[i] >> 16;
		m_dataRightChannel[i] = (((int*)_ptr1)[i] << 16) >> 16;
	}

	m_musicSound->unlock(&_ptr1, &_ptr2, _length1, _length2);
}

void SoundManager::PlayMusic(float volume)
{
	m_result = m_system->playSound(FMOD_CHANNEL_FREE, m_musicSound, false, &m_musicChannel);
	m_musicChannel->setVolume(volume);
}

void SoundManager::PauseMusic()
{
	bool _paused;
	m_musicChannel->getPaused(&_paused);
	m_musicChannel->setPaused(!_paused);
}

//For errorchecking the results of FMOD functions
void SoundManager::FMODErrorCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		//Makes an stringstream with error message and send to messagebox function
		std::stringstream _ss;
		_ss << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << "\nGame Shutting Down";
		MessageBoxAndShutDown(&_ss);
	}
}

//Initializes FMOD and makes the system handle
void SoundManager::InitFMOD()
{
	//Create FMOD Interface Object
	m_result = FMOD::System_Create(&m_system);
	FMODErrorCheck(m_result);

	//Check version
	m_result = m_system->getVersion(&m_version);
	FMODErrorCheck(m_result);

	//If the user has an old version of FMOD, shut the program down
	if (m_version < FMOD_VERSION)
	{
		//Makes an stringstream with error message and send to messagebox function
		std::stringstream _ss;
		_ss << "Error! You are using an old version of FMOD " << m_version << ". This program requires " << FMOD_VERSION << "\nGame Shutting Down";
		MessageBoxAndShutDown(&_ss);
	}

	//Get number of sound cards
	m_result = m_system->getNumDrivers(&m_numDrivers);
	FMODErrorCheck(m_result);

	//If no sound cards, disable sound
	if(m_numDrivers == 0)
	{
		m_result = m_system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		FMODErrorCheck(m_result);
	}
	else	//If at least one sound card
	{ 
		//Get the capabilities of the default (0) sound card   (stereo, 5.1, 7.1 etc)
		m_result = m_system->getDriverCaps(0, &m_caps, 0, &m_speakerMode);
		FMODErrorCheck(m_result);

		//Set the speaker mode to match that in Control Panel
		m_result = m_system->setSpeakerMode(m_speakerMode);
		FMODErrorCheck(m_result);

		//Increase the buffer size if user has hardware acceleration disabled to guard agains skipping and stuttering
		if (m_caps & FMOD_CAPS_HARDWARE_EMULATED)
		{
			m_result = m_system->setDSPBufferSize(1024, 10);
			FMODErrorCheck(m_result);
		}

		//Get name of driver
		m_result = m_system->getDriverInfo(0, m_name, 256, 0);
		FMODErrorCheck(m_result);

		// SigmaTel sound devices crackle for some reason if the format is PCM 16-bit.
		// PCM floating point output seems to solve it.
		if (strstr(m_name, "SigmaTel"))
		{
			m_result = m_system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
			FMODErrorCheck(m_result);
		}
	}

	//Actually initialize the FMOD system
	m_result = m_system->init(100, FMOD_INIT_NORMAL, 0);	//100 is number of virtual channel, won't probably use more than 5

	//If the selected speaker mode isn't supported by this sound card, switch it back to stereo
	if (m_result == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		m_result = m_system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		FMODErrorCheck(m_result);

		m_result = m_system->init(100, FMOD_INIT_NORMAL, 0);
	}
	FMODErrorCheck(m_result);
}


