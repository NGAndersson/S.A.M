#include "Input.h"

Input::Input()
{

}

Input::~Input()
{
	m_DirectInput->Release();
	m_Keyboard->Release();
	m_Mouse->Release();
}

void Input::Initialize(HINSTANCE hInstance,HWND& hwnd, int ScreenWidth, int ScreenHeight)
{
	HRESULT _hr;
	//Creating the DirectInput
	_hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_DirectInput, NULL);
	//Keyboard
	_hr = m_DirectInput->CreateDevice(GUID_SysKeyboard, &m_Keyboard,NULL);
	//mouse
	_hr = m_DirectInput->CreateDevice(GUID_SysMouse, &m_Mouse, NULL);
	//Setting the input data format for the keyboard as well as the mouse
	_hr = m_Keyboard->SetDataFormat(&c_dfDIKeyboard);
	_hr = m_Keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	_hr = m_Mouse->SetDataFormat(&c_dfDIMouse);
	_hr = m_Mouse->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);

	m_Hwnd = hwnd;//HWND KANSKE ÄR BAJS?

	m_ScreenHeight = ScreenHeight;
	m_ScreenWidth = ScreenWidth;
}

InputType Input::CheckKeyBoardInput()
{
	BYTE _KeyboardState[256];
	m_Keyboard->Acquire();
	InputType _ReturnType = INPUT_DEFAULT;
	m_Keyboard->GetDeviceState(sizeof(_KeyboardState), (LPVOID)&_KeyboardState);

	if (_KeyboardState[DIK_ESCAPE] & 0x80)
		_ReturnType = INPUT_ESC;

	if (_KeyboardState[DIK_LEFT] & 0x80)
		_ReturnType = _ReturnType | INPUT_MOVE_LEFT;

	if (_KeyboardState[DIK_RIGHT] &0x80)
		_ReturnType = _ReturnType | INPUT_MOVE_RIGHT;

	if (_KeyboardState[DIK_UP] & 0x80)
		_ReturnType = _ReturnType | INPUT_MOVE_UP;

	if (_KeyboardState[DIK_DOWN] & 0x80)
		_ReturnType = _ReturnType | INPUT_MOVE_DOWN;

	return _ReturnType;
}

MouseClicked Input::CheckMouseInput()
{
	m_Mouse->Acquire();

	DIMOUSESTATE _CurrMouse;
	MouseClicked _ReturnType;
	m_Mouse->GetDeviceState(sizeof(DIMOUSESTATE), &_CurrMouse);
	_ReturnType.MouseAct = INPUT_DEFAULT;

	POINT p;
	GetCursorPos(&p);
	ScreenToClient(m_Hwnd, &p);

	if (_CurrMouse.rgbButtons[0] & 0x80)
	{
		_ReturnType.MouseAct = INPUT_MOUSE_LK;
		_ReturnType.Mouse_Position_X = p.x;
		_ReturnType.Mouse_Position_Y = p.y;

	}
	return _ReturnType;
}

