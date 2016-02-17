#ifndef _SONGSELECT_H
#define _SONGSELECT_H

#include "../Screen.h"
#include "../../Gamelogic/Stats.h"

class SongSelect : public Screen
{
private:
	SongSelect() {}
	~SongSelect();

public:
	SongSelect(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input);
	void Update(double time);
	void Render();

private:
};


#endif

