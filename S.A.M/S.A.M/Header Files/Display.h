#ifndef DISPLAY_H
#define DISPLAY_H
#include <Windows.h>
#include <windowsx.h>

class Display
{
private:
	// the handle for the window, filled by a function
	HWND hWnd;
protected:
public:
	Display();
	~Display();
	Display(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, int width, int height);
	HWND GethWnd();
};

#endif DISPLAY_H