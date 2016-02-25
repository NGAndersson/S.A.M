#ifndef INPUT_H
#define INPUT_H

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
enum SamKeyBindings {WEAPON_1,WEAPON_2,WEAPON_3,WEAPON_4,MOVELEFT,MOVERIGHT,MOVEUP,MOVEDOWN,COMBO};
enum InputType
{
	INPUT_DEFAULT,
	INPUT_MOVE_LEFT,
	INPUT_MOVE_RIGHT,
	INPUT_MOVE_UP,
	INPUT_MOVE_DOWN,
	INPUT_MOUSE_LK,
	INPUT_MOUSE_RK,
	INPUT_ENTER,
	INPUT_ESC
};

enum BulletType
{
	INPUT_DEFAULT_BULLET,
	INPUT_BULLET2,
	INPUT_BULLET3,
	INPUT_BULLET4,
	INPUT_BULLET5
};

struct MouseClicked
{
	InputType MouseAct;
	int Mouse_Position_X;
	int Mouse_Position_Y;
};

inline InputType operator|(InputType a, InputType b)
{
	return static_cast<InputType>(static_cast<int>(a) | static_cast<int>(b));
}

class Input
{
	//----------------------------Functions----------------------------------------
public:
	Input();
	~Input();

	void Initialize(HINSTANCE hInstance, HWND& hwnd,int ScreenWidth,int ScreenHeight);
	wstring GetKeyBinding(int key) {
		for (int i = 0; i < 51; i++)
		{
			if (key == m_dikToString[i].first)
				return m_dikToString[i].second;
		}
		return L"Faulty Key";
	}

	int GetKeyBiningArray(int i) { return m_keyBindings[i]; }
	void SetKeyBindings(int newKeyBindings[9])
	{
		for (int i = 0; i < 9;i++)
			m_keyBindings[i] = newKeyBindings[i];
	}
	bool CheckIfInput();
	int CheckInputInt();
	wstring CheckInputWString();
	void CheckKeyBoardInput(InputType* returnput);
	InputType CheckKeyBoardInput();
	BulletType CheckBullet();
	void Update();
	bool CheckReturn();
	bool CheckEsc();
	//bool IsNewButtonPressed(BulletType& checkAgainst);
	bool IsNewButtonPressed(bool& checkAgainst);
	void ReadInputKeyBindings();
	void SaveInputKeyBindings();
	void PairKeys();
	std::pair<int, std::wstring> m_dikToString[51];
	//----------------------------Attributes----------------------------------------
private:

	IDirectInput8* m_DirectInput;

	IDirectInputDevice8* m_Keyboard;

	int m_keyBindings[9];
	int m_ScreenHeight;
	int m_ScreenWidth;
	BYTE m_keyBoardState[256];
	HWND m_Hwnd;

};

#endif
