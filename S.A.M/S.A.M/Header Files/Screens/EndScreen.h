#ifndef ENDSCREEN_H
#define ENDSCREEN_H
#include "Screen.h"
#include "Gamelogic/Stats.h"

class EndScreen : public Screen
{
	//Functions
private:
protected:
public:
	EndScreen() {};
	~EndScreen() {};

	EndScreen(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, Stats* stats);
	void Update();
	void Render();

	//Attributes
private:
	const wchar_t* m_highScore = L"High Score";
	const wchar_t* m_menu = L"Return to Menu";
	const wchar_t* m_message1 = L"Congratulations!";
	const wchar_t* m_message2 = L"You have been killed!";
	const wchar_t* m_message3 = L"Score: 6";

	bool m_keyDown = false;
	Font m_choices[2];
	Font m_texts[3];

	int m_currentFont;

	Stats* m_stats;
protected:
public:

};

#endif ENDSCREEN_H