#ifndef _HIGHSCOREMENU_H
#define _HIGHSCOREMENU_H

#include "../Screen.h"
#include "../../Gamelogic/Stats.h"
#include <CommonStates.h>

class HighScoreMenu : public Screen
{
private:
public:
	HighScoreMenu() {}

	~HighScoreMenu() {}
	HighScoreMenu(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, Stats* stats);
	void Update(double time);
	void Render();

private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_background;
	Stats* m_stats;
	string m_scorePath;
	std::pair<std::wstring, int>* m_highscore;
};


#endif
