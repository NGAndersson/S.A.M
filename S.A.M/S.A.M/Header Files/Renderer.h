#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "ModelHandler.h"
#include <DirectXMath.h>
#include <d3d11.h>

#include "ModelHandler.h"
#include "Camera.h"

class Renderer
{
	//Cam buffer for GS
	struct CamStruct {
		XMFLOAT4 camPos;
		XMMATRIX viewProjection;
	};

	//World buffer for VS
	struct WorldStruct {
		XMMATRIX worldMatrix;
		XMFLOAT3 worldPos;
	};

//Functions
private:

public:
	void Render(ModelHandler* model, XMFLOAT3 position, XMMATRIX* rotation);
	Renderer(ID3D11DeviceContext* deviceContext, ID3D11Device* device);

//Variables
private:
	ID3D11DeviceContext* m_deviceContext;
	ID3D11Device* m_device;

	CamStruct m_camStruct;
	ID3D11Buffer* m_camBuffer;
	WorldStruct m_worldStruct;
	ID3D11Buffer* m_worldBuffer;
	Camera m_cam;

	ID3D11Buffer* triangleVertBuffer;
	ID3D11InputLayout* vertLayout;

public:

};

#endif
