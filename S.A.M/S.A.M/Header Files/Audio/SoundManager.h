#ifndef _SOUNDMANAGER_H_
#define _SOUNDMANAGER_H_
#include "fmod.hpp"
#include "fmod_errors.h"
#include <vector>

//Cool as fuck flags for the loadfunction
enum SoundFlags
{
	LOAD_MEMORY = 0x01,
	LOAD_STREAM = 0x02,
	LOAD_SOFTWARE = 0x04
};

inline SoundFlags operator|(SoundFlags a, SoundFlags b)
{
	return static_cast<SoundFlags>(static_cast<int>(a) | static_cast<int>(b));
}

class SoundManager 
{
	//Functions
	private:
		void InitFMOD();									//For intializing FMOD stuff
		void FMODErrorCheck(FMOD_RESULT result);			//For checking the results of FMOD functions
		void MessageBoxAndShutDown(std::stringstream* _ss); //Called if something went wrong so the program needs to shut down
		void FindSoundIndex(char* soundName, int &groupIndex, int &soundIndex);	//Finds the sound and group index of a sound name
		int FindGroupIndex(char* groupName);	//Same as FindSoundIndex() but only looks for matching groups
	public:
		SoundManager(float musicVol, float effectvol);
		~SoundManager();
		void LoadSound(char* fileName, char* soundName, char* groupName, SoundFlags flags);	//Loads sound into array 
		void PlayOneShotSound(char* soundName, float volume);				//Plays a sound with a specific name, at volume 0.0-1.0
		void PauseSound(char* soundName);
		void LoadMusic(char* fileName);
		void PlayMusic(float volume);
		void StopMusic() { m_musicChannel->stop(); }
		void PauseMusic();
		void Update();
		float* SpectrumAnalysis(char* soundName);
		int* GetLeftData() { return m_dataLeftChannel; }
		int* GetRightData() { return m_dataRightChannel; }
		unsigned int GetLength() { return m_musicLength; }
		unsigned int GetLengthMS() { unsigned int l; m_musicSound->getLength(&l, FMOD_TIMEUNIT_MS); return l;}
		int GetCurrentMusicTimePCM();
		void SetMusicVolume(float in) { m_musicVolume = in; }
		void SetEffectVolume(float in) { m_effectVolume = in; }
		float GetMusicVolume() { return m_musicVolume; }
		float GetEffectVolume() {return m_effectVolume; }
		void Reset() { m_sounds.clear(); m_soundIndexes.clear(); m_soundChannels.clear(); m_soundGroupIndexes.clear(); }

	//Variables
	private:
		FMOD::System* m_system;				//Core of FMOD
		FMOD_RESULT m_result;				//Result from FMOD functions
		unsigned int m_version;				//Users FMOD version
		int m_numDrivers;					//Number of user soundcards
		FMOD_SPEAKERMODE m_speakerMode;		//User speakermode
		FMOD_CAPS m_caps;					//??? Soundcard capabilities ???
		char m_name[256];					//Name of sound driver
		float m_musicVolume =0.5,m_effectVolume = 0.5;//Volume

		std::vector<std::vector<FMOD::Sound*>> m_sounds;	//Groups of sounds (for variation of the same kind of sound)
		std::vector<std::vector<char*>> m_soundIndexes;		//Indexes of groups based on name
		std::vector<std::vector<FMOD::Channel*>> m_soundChannels;	//Channel groups for the sounds
		std::vector<char*> m_soundGroupIndexes;

		//Music specific things for beat detection
		FMOD::Sound* m_musicSound;
		FMOD::Channel* m_musicChannel;
		unsigned int m_musicLength;
		int* m_dataLeftChannel = nullptr;
		int* m_dataRightChannel = nullptr;
};

#endif // !_SOUNDMANAGER_H_

