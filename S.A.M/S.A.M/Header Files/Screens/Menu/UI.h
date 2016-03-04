#ifndef _UI_H
#define _UI_H

#include "../Screen.h"
#include "../../Gamelogic/Stats.h"

enum KeyBindings { SHOT1, SHOT2, SHOT3, SHOT4 };
class UI : public Screen
{
private:
	UI(){}
	~UI();

public:
	UI(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input,Stats* stats);
	void Update(double time);
	void Render(int offset);

private:
	Stats* m_stats;
	wstring m_score;
	wstring m_livesLeft;
	wstring m_combo;
	wstring m_beats;
	Input* m_input;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_bSprite1;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_bSprite2;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_bSprite3;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_bSprite4;

	Font m_shotBinding[4];
};


#endif

