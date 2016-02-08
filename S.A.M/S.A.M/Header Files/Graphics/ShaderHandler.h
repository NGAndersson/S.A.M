#ifndef _SHADERHANDLER_H_
#define _SHADERHANDLER_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <iostream>
#include <vector>
#include <d3dcompiler.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")

using namespace std;
using namespace DirectX;

class ShaderHandler
{
public:
	ShaderHandler();
	~ShaderHandler();
	bool CreateShaders(ID3D11Device* device, string vertexFile, string geometryFile, string pixelFile);
	bool CreateShadersCompute(ID3D11Device* device, string vertexFile, string geometryFile, string pixelFile, string computeFile);
	bool SetShaders(ID3D11DeviceContext* deviceContext);

private:
	ID3D11InputLayout* m_vertexLayout;
	ID3D11VertexShader* m_vertexShader;
	ID3D11GeometryShader* m_geometryShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11ComputeShader* m_computeShader;

};

#endif