#ifndef _UI_H
#define _UI_H

#include "../Screen.h"
#include "../../Gamelogic/Stats.h"

class UI : public Screen
{
private:
	UI(){}
	~UI();

public:
	UI(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input,Stats* stats);
	void Update();
	void Render();

private:
	Stats* m_stats;
	wstring m_score;
	wstring m_livesLeft;
	wstring m_combo;
};


#endif

