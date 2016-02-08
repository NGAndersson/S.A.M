#include "Gamelogic/Input.h"

Input::Input()
{

}

Input::~Input()
{

	m_Keyboard->Unacquire();
	m_Mouse->Unacquire();

	if(m_DirectInput)
		m_DirectInput->Release();
	
	if(m_Keyboard)
		m_Keyboard->Release();
	if(m_Mouse)
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
	_hr = m_Mouse->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);


	m_Hwnd = hwnd;

	m_ScreenHeight = ScreenHeight;
	m_ScreenWidth = ScreenWidth;


}

BulletType Input::CheckBullet()
{
	m_Keyboard->Acquire();
	BYTE _KeyboardState[256];
	
	BulletType _returnType = INPUT_DEFAULT_BULLET;

	ZeroMemory(&_KeyboardState, sizeof(_KeyboardState));
	m_Keyboard->GetDeviceState(sizeof(_KeyboardState), (LPVOID)&_KeyboardState);

	if (_KeyboardState[DIK_Q] & 0x80)
		return	_returnType = INPUT_BULLET2;

	if (_KeyboardState[DIK_W] & 0x80)
		return	_returnType = INPUT_BULLET3;

	if (_KeyboardState[DIK_E] & 0x80)
		return	_returnType = INPUT_BULLET4;

	if (_KeyboardState[DIK_R] & 0x80)
		return	_returnType = INPUT_BULLET5;

	return _returnType;

}

void Input::CheckKeyBoardInput(InputType* returnput)
{
	m_Keyboard->Acquire();
	BYTE _KeyboardState[256];
	ZeroMemory(&_KeyboardState, sizeof(_KeyboardState));

	m_Keyboard->GetDeviceState(sizeof(_KeyboardState), (LPVOID)&_KeyboardState);

	if (_KeyboardState[DIK_LEFT] & 0x80)
		returnput[0] = INPUT_MOVE_LEFT;

	if (_KeyboardState[DIK_RIGHT] &0x80)
		returnput[1] = INPUT_MOVE_RIGHT;

	if (_KeyboardState[DIK_UP] & 0x80)
		returnput[2] = INPUT_MOVE_UP;

	if (_KeyboardState[DIK_DOWN] & 0x80)
		returnput[3] = INPUT_MOVE_DOWN;


}

MouseClicked Input::CheckMouseInput()
{

	m_Mouse->Acquire();
	DIMOUSESTATE _CurrMouse;
	MouseClicked _ReturnType;
	m_Mouse->GetDeviceState(sizeof(DIMOUSESTATE), &_CurrMouse);
	_ReturnType.MouseAct = INPUT_DEFAULT;

	POINT _p;
	GetCursorPos(&_p);
	ScreenToClient(m_Hwnd, &_p);

	if (_CurrMouse.rgbButtons[0] & 0x80)
	{
		_ReturnType.MouseAct = INPUT_MOUSE_LK;
		_ReturnType.Mouse_Position_X = _p.x;
		_ReturnType.Mouse_Position_Y = _p.y;

	}

	return _ReturnType;
}

bool Input::CheckEsc()
{
	BYTE _KeyboardState[256];
	ZeroMemory(&_KeyboardState, sizeof(_KeyboardState));

	m_Keyboard->GetDeviceState(sizeof(_KeyboardState), (LPVOID)&_KeyboardState);

	if (_KeyboardState[DIK_ESCAPE] & 0x80)
		return true;

	return false;
}

