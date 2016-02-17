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
	EndScreen() {}
	~EndScreen() { m_font.release(); }

	EndScreen(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, Stats* stats);
	void Update();
	void Render();

	virtual MenuScreens GetTargetMenu() {
		switch (m_currentFont)
		{
		case 0:
			return HIGHSCORE;
			break;
		case 1:
			return MENU;
			break;
		}
	}

	//Attributes
private:
	const wchar_t* m_highScore;
	const wchar_t* m_menu;
	const wchar_t* m_message1;
	const wchar_t* m_message2;
	const wchar_t* m_message3;

	bool m_keyDown = false;
	Font m_choices[2];
	Font m_texts[3];

	int m_currentFont;

	Stats* m_stats;
protected:
public:

};

#endif ENDSCREEN_H