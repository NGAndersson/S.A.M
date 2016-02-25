#ifndef ENDSCREEN_H
#define ENDSCREEN_H
#include "../Screen.h"
#include "Gamelogic/Stats.h"

class EndScreen : public Screen
{
	//Functions
private:
protected:
public:
	EndScreen() {}
	~EndScreen() {}

	EndScreen(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, Stats* stats);
	void Update(double time);
	void Render();

	//Attributes
private:
	Stats* m_stats;
	int m_screenWidth, m_screenHeight;
protected:
public:

};

#endif ENDSCREEN_H