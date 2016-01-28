#ifndef _RENDERER_H_
#define _RENDERER_H_
//#include "ModelHandler.h"
#include <DirectXMath.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib");

class Renderer
{
//Functions
private:

public:
	void Render(ModelHandler* model, XMFLOAT3 position, XMMATRIX rotation);

//Variables
private:

public:

};

#endif
