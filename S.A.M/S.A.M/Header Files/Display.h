#ifndef DISPLAY_H
#define DISPLAY_H
#include <Windows.h>
#include <windowsx.h>

// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")

class Display
{
private:
	// the handle for the window, filled by a function
	HWND hWnd;
protected:
public:
	Display();
	~Display();
	Display(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	HWND GethWnd();
	void InitD3D(HWND hWnd);
	void CleanD3D(void);
	void BeginFrame(void);
	void EndFrame(void);
};

#endif DISPLAY_H