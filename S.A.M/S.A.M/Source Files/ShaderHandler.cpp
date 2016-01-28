#include "ShaderHandler.h"

ShaderHandler::ShaderHandler()
{

}

ShaderHandler::~ShaderHandler()
{
	if (m_vertexLayout)
	{
		m_vertexLayout->Release();
	}
	if (m_vertexShader)
	{
		m_vertexShader->Release();
	}
	if (m_geometryShader)
	{
		m_geometryShader->Release();
	}
	if (m_pixelShader)
	{
		m_pixelShader->Release();
	}
	if (m_computeShader)
	{
		m_computeShader->Release();
	}
}

bool ShaderHandler::CreateShaders(ID3D11Device* device, string vertexFile, string geometryFile, string pixelFile)
{
	//create vertex shader
	ID3DBlob* pVS = nullptr;
	D3DCompileFromFile( (LPCWSTR)vertexFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS_main", "vs_5_0", 0, NULL, &pVS, nullptr);

	device->CreateVertexShader(pVS->GetBufferPointer(), pVS->GetBufferSize(), nullptr, &m_vertexShader);

	//create input layout (verified with vertex shader)
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	device->CreateInputLayout(inputDesc, ARRAYSIZE(inputDesc), pVS->GetBufferPointer(), pVS->GetBufferSize(), &m_vertexLayout);
	pVS->Release();

	//create geometry shader
	ID3DBlob* pGS = nullptr;
	D3DCompileFromFile((LPCWSTR)geometryFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "GS_main", "gs_5_0", 0, NULL, &pGS, nullptr);
	device->CreateGeometryShader(pGS->GetBufferPointer(), pGS->GetBufferSize(), nullptr, &m_geometryShader);
	pGS->Release();

	//create pixel shader
	ID3DBlob* pPS = nullptr;
	D3DCompileFromFile((LPCWSTR)pixelFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS_main", "ps_5_0", 0, NULL, &pPS, nullptr);
	device->CreatePixelShader(pPS->GetBufferPointer(), pPS->GetBufferSize(), nullptr, &m_pixelShader);
	pPS->Release();

	return true;
}

bool ShaderHandler::CreateShadersCompute(ID3D11Device* device, string vertexFile, string geometryFile, string pixelFile, string computeFile)
{
	//create vertex shader
	ID3DBlob* vs = nullptr;
	D3DCompileFromFile((LPCWSTR)vertexFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS_main", "vs_5_0", 0, NULL, &vs, nullptr);

	device->CreateVertexShader(vs->GetBufferPointer(), vs->GetBufferSize(), nullptr, &m_vertexShader);

	//create input layout (verified with vertex shader)
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	device->CreateInputLayout(inputDesc, ARRAYSIZE(inputDesc), vs->GetBufferPointer(), vs->GetBufferSize(), &m_vertexLayout);
	vs->Release();

	//create geometry shader
	ID3DBlob* gs = nullptr;
	D3DCompileFromFile((LPCWSTR)geometryFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "GS_main", "gs_5_0", 0, NULL, &gs, nullptr);
	device->CreateGeometryShader(gs->GetBufferPointer(), gs->GetBufferSize(), nullptr, &m_geometryShader);
	gs->Release();

	//create pixel shader
	ID3DBlob* ps = nullptr;
	D3DCompileFromFile((LPCWSTR)pixelFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS_main", "ps_5_0", 0, NULL, &ps, nullptr);
	device->CreatePixelShader(ps->GetBufferPointer(), ps->GetBufferSize(), nullptr, &m_pixelShader);
	ps->Release();

	// Create compute shader
	ID3DBlob *cs = nullptr;
	D3DCompileFromFile((LPCWSTR)computeFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "CS_main", "cs_5_0", 0, NULL, &cs, nullptr);
	device->CreateComputeShader(cs->GetBufferPointer(), cs->GetBufferSize(), nullptr, &m_computeShader);
	cs->Release();

	return true;
}

bool ShaderHandler::SetShaders(ID3D11DeviceContext* deviceContext)
{
	deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
	deviceContext->HSSetShader(nullptr, nullptr, 0);
	deviceContext->DSSetShader(nullptr, nullptr, 0);
	deviceContext->GSSetShader(m_geometryShader, nullptr, 0);
	deviceContext->PSSetShader(m_pixelShader, nullptr, 0);

	if (m_computeShader)
	{
		deviceContext->CSSetShader(m_computeShader, nullptr, 0);
	}

	deviceContext->IASetInputLayout(m_vertexLayout);

	return true;
}