#include "SoundManager.h"
#include <iostream>	//Not needed

SoundManager sm;


int main() {
	sm.LoadSound("Resources/wave.mp3", "wave", LOAD_STREAM);
	sm.PlayOneShotSound("wave", 0.5f);
	std::cin.ignore();
	return 0;
}