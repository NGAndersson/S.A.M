#ifndef _SOUNDMANAGER_H_
#define _SOUNDMANAGER_H_
#include "fmod.hpp"
#include "fmod_errors.h"

class SoundManager {
	//Functions
	private:
		void InitFMOD();									//For intializing FMOD stuff
		void FMODErrorCheck(FMOD_RESULT result);			//For checking the results of FMOD functions
		void MessageBoxAndShutDown(std::stringstream* _ss); //Called if something went wrong so the program needs to shut down
	public:

	//Variables
	private:
		FMOD::System* m_system;				//Core of FMOD
		FMOD_RESULT m_result;				//Result from FMOD functions
		unsigned int m_version;				//Users FMOD version
		int m_numDrivers;					//Number of user soundcards
		FMOD_SPEAKERMODE m_speakerMode;		//User speakermode
		FMOD_CAPS m_caps;					//??? Soundcard capabilities ???
		char m_name[256];					//Name of sound driver

};

#endif // !_SOUNDMANAGER_H_

