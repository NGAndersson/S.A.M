#ifndef _DEFERREDRENDER_H_
#define _DEFERREDRENDER_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include "WICTextureLoader.h"

using namespace std;
using namespace DirectX;

class DeferredRender
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
	};
public:
	DeferredRender();
	~DeferredRender();
	bool InitializeShader(ID3D11Device* device);
	bool InitializeBufferString(ID3D11Device* device);
	void Render(ID3D11DeviceContext* deviceContext);
private:
	ID3D11InputLayout* m_vertexLayout = nullptr;
	ID3D11VertexShader* m_vertexShader = nullptr;
	ID3D11PixelShader* m_pixelShader = nullptr;
	ID3D11Buffer *m_vertexBuffer = nullptr;
};


#endif
