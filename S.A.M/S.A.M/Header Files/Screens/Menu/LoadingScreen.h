#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include "../Screen.h"

class LoadingScreen : public Screen
{
	//Functions
private:
	LoadingScreen();
protected:
public:
	LoadingScreen(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input);
	~LoadingScreen();
	void Render();

	//Attributes
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_background;

	Font m_Hints[2];
	wstring m_dyk;
protected:
public:
};

#endif