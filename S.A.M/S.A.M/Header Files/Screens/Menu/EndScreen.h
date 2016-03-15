#ifndef ENDSCREEN_H
#define ENDSCREEN_H
#include "../Screen.h"
#include "Gamelogic/Stats.h"

class EndScreen : public Screen
{
	//Functions
private:
	wchar_t KeyToWChar(int key);
protected:
public:
	EndScreen() {}
	~EndScreen() {}

	EndScreen(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, Stats* stats);
	void Update(double time);
	void UpdateOP(double time);
	void Render();
	wstring GetPlayerName() { return m_playerName; }

	//Attributes
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_background;
	Stats* m_stats;
	wstring m_playerName;
	bool m_state = false;
protected:
public:

};

#endif ENDSCREEN_H