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
	};

	//World buffer for VS
	struct WorldStructInstanced {
		XMFLOAT4X4 worldMatrix[100];
	};

//Functions
private:

public:
	~Renderer();
	void Render(ModelHandler* model, XMFLOAT3 position, XMMATRIX &rotation, XMFLOAT3 scale);
	void RenderInstanced(ModelHandler * model, vector<XMFLOAT3> position, XMMATRIX &rotation, int amountOfBullets, XMFLOAT3 scale);
	Renderer(ID3D11DeviceContext* deviceContext, ID3D11Device* device);

//Variables
private:
	ID3D11DeviceContext* m_deviceContext;
	ID3D11Device* m_device;

	CamStruct m_camStruct;
	ID3D11Buffer* m_camBuffer;
	WorldStruct m_worldStruct;
	WorldStructInstanced m_worldStructInstanced;
	ID3D11Buffer* m_worldBuffer, *m_worldBufferInstance;
	Camera m_cam;

public:

};

#endif
