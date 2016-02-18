#include "Gamelogic/Input.h"

Input::Input()
{

}

Input::~Input()
{

	if (m_Keyboard)
	{
		m_Keyboard->Unacquire();
		m_Keyboard->Release();
		m_Keyboard = 0;
	}

	if (m_Mouse)
	{
		m_Mouse->Unacquire();
		m_Mouse->Release();
		m_Mouse = 0;
	}

	if (m_DirectInput)
	{
		m_DirectInput->Release();
		m_DirectInput = 0;
	}

}

void Input::Update()
{
	m_Keyboard->Acquire();

	ZeroMemory(&m_keyBoardState, sizeof(m_keyBoardState));
	m_Keyboard->GetDeviceState(sizeof(m_keyBoardState), (LPVOID)&m_keyBoardState);

	m_Mouse->Acquire();
	m_Mouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrMouse);

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
	
	BulletType _returnType = INPUT_DEFAULT_BULLET;

	if (m_keyBoardState[DIK_Q] & 0x80)
		return	_returnType = INPUT_BULLET2;

	if (m_keyBoardState[DIK_W] & 0x80)
		return	_returnType = INPUT_BULLET3;

	if (m_keyBoardState[DIK_E] & 0x80)
		return	_returnType = INPUT_BULLET4;

	if (m_keyBoardState[DIK_R] & 0x80)
		return	_returnType = INPUT_BULLET5;

	return _returnType;

}
InputType Input::CheckKeyBoardInput()
{
	if (m_keyBoardState[DIK_LEFT] & 0x80)
		return INPUT_MOVE_LEFT;

	else if (m_keyBoardState[DIK_RIGHT] & 0x80)
		return INPUT_MOVE_RIGHT;

	else if (m_keyBoardState[DIK_UP] & 0x80)
		return INPUT_MOVE_UP;

	else if (m_keyBoardState[DIK_DOWN] & 0x80)
		return INPUT_MOVE_DOWN;

	return INPUT_DEFAULT;

}

bool Input::CheckReturn()
{
	if (m_keyBoardState[DIK_RETURN] & 0x80)
		return true;
	
	return false;
}

void Input::CheckKeyBoardInput(InputType* returnput)
{
	if (m_keyBoardState[DIK_LEFT] & 0x80)
		returnput[0] = INPUT_MOVE_LEFT;

	if (m_keyBoardState[DIK_RIGHT] &0x80)
		returnput[1] = INPUT_MOVE_RIGHT;

	if (m_keyBoardState[DIK_UP] & 0x80)
		returnput[2] = INPUT_MOVE_UP;

	if (m_keyBoardState[DIK_DOWN] & 0x80)
		returnput[3] = INPUT_MOVE_DOWN;


}

MouseClicked Input::CheckMouseInput()
{

	MouseClicked _ReturnType;
	_ReturnType.MouseAct = INPUT_DEFAULT;

	POINT _p;
	GetCursorPos(&_p);
	ScreenToClient(m_Hwnd, &_p);

	if (m_CurrMouse.rgbButtons[0] & 0x80)
	{
		_ReturnType.MouseAct = INPUT_MOUSE_LK;
		_ReturnType.Mouse_Position_X = _p.x;
		_ReturnType.Mouse_Position_Y = _p.y;

	}

	return _ReturnType;
}

bool Input::CheckEsc()
{
	BYTE m_keyBoardState[256];
	ZeroMemory(&m_keyBoardState, sizeof(m_keyBoardState));

	m_Keyboard->GetDeviceState(sizeof(m_keyBoardState), (LPVOID)&m_keyBoardState);

	if (m_keyBoardState[DIK_ESCAPE] & 0x80)
		return true;

	return false;
}

//Return true if a new button is being pressed, not if a button is released
//bool Input::IsNewButtonPressed(BulletType& checkAgainst)
//{
//	BulletType _current = CheckBullet();
//	
//	if ((_current == INPUT_BULLET2 && checkAgainst != INPUT_BULLET2)
//		|| (_current == INPUT_BULLET3 && checkAgainst != INPUT_BULLET3)
//		|| (_current == INPUT_BULLET4 && checkAgainst != INPUT_BULLET4)
//		|| (_current == INPUT_BULLET5 && checkAgainst != INPUT_BULLET5))
//	{
//		checkAgainst = _current;
//		return true;
//	}
//	checkAgainst = _current;
//	return false;
//}

bool Input::IsNewButtonPressed(bool& checkAgainst)
{
	if (m_keyBoardState[DIK_SPACE] & 0x80)
	{
		if (checkAgainst == true)
			return false;
		else {
			checkAgainst = true;
			return true;
		}
	}
	else {
		checkAgainst = false;
		return false;
	}
}