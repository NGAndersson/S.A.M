#ifndef INPUT_H
#define INPUT_H

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>

enum InputType
{
	INPUT_DEFAULT = 0x000,
	INPUT_MOVE_LEFT = 0x001,
	INPUT_MOVE_RIGHT = 0x002,
	INPUT_MOVE_UP = 0x004,
	INPUT_MOVE_DOWN = 0x008,
	INPUT_MOUSE_LK = 0x016,
	INPUT_MOUSE_RK = 0x032,
	INPUT_ESC = 0x064
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
	InputType CheckKeyBoardInput();
	MouseClicked CheckMouseInput();

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
