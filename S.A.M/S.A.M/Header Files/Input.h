#ifndef INPUT_H
#define INPUT_H

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>

enum InputType
{
	INPUT_DEFAULT,
	INPUT_MOVE_LEFT,
	INPUT_MOVE_RIGHT,
	INPUT_MOVE_UP,
	INPUT_MOVE_DOWN,
	INPUT_MOUSE_LK,
	INPUT_MOUSE_RK,
	INPUT_ESC
};

enum BulletType
{
	INPUT_DEFAULT,
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
	void CheckKeyBoardInput(InputType* returnput);
	BulletType CheckBullet();
	MouseClicked CheckMouseInput();
	bool CheckEsc();

	//----------------------------Attributes----------------------------------------
private:

	IDirectInput8* m_DirectInput;

	IDirectInputDevice8* m_Keyboard;
	IDirectInputDevice8* m_Mouse;

	DIMOUSESTATE m_LastState;

	int m_ScreenHeight;
	int m_ScreenWidth;

	HWND m_Hwnd;

};

#endif
