#ifndef _SOUNDMANAGER_H_
#define _SOUNDMANAGER_H_
#include "fmod.hpp"
#include "fmod_errors.h"
#include <vector>

//Cool as fuck flags for the loadfunction
enum SoundFlags
{
	LOAD_MEMORY = 0x01,
	LOAD_STREAM = 0x02
};

inline SoundFlags operator|(SoundFlags a, SoundFlags b)
{
	return static_cast<SoundFlags>(static_cast<int>(a) | static_cast<int>(b));
}

class SoundManager {
	//Functions
	private:
		void InitFMOD();									//For intializing FMOD stuff
		void FMODErrorCheck(FMOD_RESULT result);			//For checking the results of FMOD functions
		void MessageBoxAndShutDown(std::stringstream* _ss); //Called if something went wrong so the program needs to shut down
	public:
		SoundManager();
		void LoadSound(char* fileName, char* soundName, SoundFlags flags);	//Loads sound into array 
		void PlayOneShotSound(char* soundName);								//Plays a sound with a specific name
	//Variables
	private:
		FMOD::System* m_system;				//Core of FMOD
		FMOD_RESULT m_result;				//Result from FMOD functions
		unsigned int m_version;				//Users FMOD version
		int m_numDrivers;					//Number of user soundcards
		FMOD_SPEAKERMODE m_speakerMode;		//User speakermode
		FMOD_CAPS m_caps;					//??? Soundcard capabilities ???
		char m_name[256];					//Name of sound driver

		std::vector<FMOD::Sound*> m_sounds;	//All the sounds
		std::vector<char*> m_soundIndex;	//Soundnames, where soundname index is the corresponding index of m_sounds
};

#endif // !_SOUNDMANAGER_H_

