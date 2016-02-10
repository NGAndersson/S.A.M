#include "Graphics/DeferredRender.h"

DeferredRender::DeferredRender()
{

}

DeferredRender::~DeferredRender()
{
	m_vertexLayout->Release();
	m_vertexShader->Release();
	m_pixelShader->Release();
	m_vertexBuffer->Release();
}

bool DeferredRender::InitializeShader(ID3D11Device* gDevice)
{
	//create vertex shader
	ID3DBlob* pVS = nullptr;
	D3DCompileFromFile(L"Shaders/DeferredVS.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS_main", "vs_5_0", 0, NULL, &pVS, nullptr);

	gDevice->CreateVertexShader(pVS->GetBufferPointer(), pVS->GetBufferSize(), nullptr, &m_vertexShader);

	//create input layout (verified with vertex shader)
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	gDevice->CreateInputLayout(inputDesc, ARRAYSIZE(inputDesc), pVS->GetBufferPointer(), pVS->GetBufferSize(), &m_vertexLayout);
	pVS->Release();

	//create pixel shader
	ID3DBlob* pPS = nullptr;
	D3DCompileFromFile(L"Shaders/DeferredPS.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS_main", "ps_5_0", 0, NULL, &pPS, nullptr);
	gDevice->CreatePixelShader(pPS->GetBufferPointer(), pPS->GetBufferSize(), nullptr, &m_pixelShader);
	pPS->Release();

	return true;
}

bool DeferredRender::InitializeBufferString(ID3D11Device* gDevice)
{
	VertexType* _vertices = new VertexType[4];
	D3D11_BUFFER_DESC _vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA _vertexData;
	HRESULT _result;

	_vertices[0].position = XMFLOAT3(-1, 1, 0);

	_vertices[1].position = XMFLOAT3(1, 1, 0);

	_vertices[2].position = XMFLOAT3(-1, -1, 0);

	_vertices[3].position = XMFLOAT3(1, -1, 0);

	// description för vertex buffern
	_vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	_vertexBufferDesc.ByteWidth = sizeof(VertexType) * 4;
	_vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	_vertexBufferDesc.CPUAccessFlags = 0;
	_vertexBufferDesc.MiscFlags = 0;
	_vertexBufferDesc.StructureByteStride = 0;


	_vertexData.pSysMem = _vertices;
	_vertexData.SysMemPitch = 0;
	_vertexData.SysMemSlicePitch = 0;

	// Skapar vertex buffern
	_result = gDevice->CreateBuffer(&_vertexBufferDesc, &_vertexData, &m_vertexBuffer);

	delete[] _vertices;

	if (FAILED(_result))
	{
		return false;
	}
	return true;
}

void DeferredRender::Render(ID3D11DeviceContext* gDeviceContext)
{
	gDeviceContext->VSSetShader(m_vertexShader, nullptr, 0);
	gDeviceContext->HSSetShader(nullptr, nullptr, 0);
	gDeviceContext->DSSetShader(nullptr, nullptr, 0);
	gDeviceContext->GSSetShader(nullptr, nullptr, 0);
	gDeviceContext->PSSetShader(m_pixelShader, nullptr, 0);

	UINT32 vertexSize = sizeof(float) * 3;
	UINT32 offset = 0;
	gDeviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &vertexSize, &offset);

	gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	gDeviceContext->IASetInputLayout(m_vertexLayout);

	gDeviceContext->Draw(4, 0);
}