#include "SoundManager.h"
#include <iostream>	//Not needed

SoundManager sm;


int main() {
	sm.LoadSound("Resources/wave.mp3", "wave", LOAD_MEMORY);
	sm.PlayOneShotSound("wave");

	std::cin.ignore();
	return 0;
}