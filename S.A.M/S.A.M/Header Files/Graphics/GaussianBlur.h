#ifndef _GAUSSIANBLUR_H
#define _GAUSSIANBLUR_H

#include <stdio.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "../Graphics/ShaderHandler.h"


using namespace std;
using namespace DirectX;
class GaussianBlur
{
private:
	
public:
	GaussianBlur(){}
	~GaussianBlur();
	GaussianBlur(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, ShaderHandler* shaderHandler, int width, int height);
	void Blur(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, UINT ShaderTarget, ID3D11ShaderResourceView* shaderResource);
private:

	ShaderHandler* m_shaderHandler;
	ID3D11UnorderedAccessView* m_unAc = nullptr;
	ID3D11UnorderedAccessView* m_unAc2 = nullptr;
	ID3D11ShaderResourceView* m_compShaderTexture1 = nullptr;
	ID3D11ShaderResourceView* m_compShaderTexture2 = nullptr;
	UINT m_shaderTarget; //Targeted place for shader

	int m_screenHeight,m_screenWidth;


};

#endif // !_GAUSSIANBLUR_H
