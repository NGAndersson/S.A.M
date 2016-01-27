#ifndef INPUT_H
#define INPUT_H

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>

enum InputType
{
	MOVE_LEFT = 0x001,
	MOVE_RIGHT = 0x002,
	MOVE_UP = 0x004,
	MOVE_DOWN = 0x008,
	MOUSE_LK = 0x016,
	MOUSE_RK = 0x032,
};

struct MouseKlicked
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
	InputType CheckKeyBoardInput(double time);
	MouseKlicked CheckMouseInput(double time);

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
