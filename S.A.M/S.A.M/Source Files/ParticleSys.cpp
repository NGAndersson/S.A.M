#include "ParticleSys.h"

PartSys::PartSys()
{
	m_amountOfPart = 600;
	m_partPos = new XMFLOAT4[m_amountOfPart];

	srand(int(time(0)));
	for (int i = 0; i < m_amountOfPart; i++)
	{
		m_partPos[i] = XMFLOAT4(((float(rand() % 600)) - 300.0f), float(rand() % 200) - 400, float(rand() % 900) - float(500), 1.0f);
	}
}

PartSys::~PartSys()
{
	m_vertexLayout->Release();
	m_vertexShader->Release();
	m_geometryShader->Release();
	m_pixelShader->Release();
	delete[] m_partPos;
	m_vertexBuffer->Release();
	m_partTex->Release();
}

void PartSys::updatePart(ID3D11DeviceContext* deviceContext, float time, float partSpeed)
{
	for (int i = 0; i < m_amountOfPart; i++)
	{
		if (m_partPos[i].z <= -400)
		{
			m_partPos[i] = XMFLOAT4(((float(rand() % 600)) - 300.0f), float(rand() % 200) - 400, float(rand() % 150) + float(400), 1.0f);
		}
		else
		{
			m_partPos[i] = XMFLOAT4(m_partPos[i].x, m_partPos[i].y, m_partPos[i].z - (partSpeed * time), 1.0f);
		}
	}

	D3D11_MAPPED_SUBRESOURCE mappResource;
	deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappResource);

	memcpy(mappResource.pData, &m_partPos[0], sizeof(float) * (m_amountOfPart * 4));

	deviceContext->Unmap(m_vertexBuffer, 0);

}

bool PartSys::CreateBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	D3D11_BUFFER_DESC _OBJvertexBufferDesc;

	ZeroMemory(&_OBJvertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	// description för vertex buffern
	_OBJvertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	_OBJvertexBufferDesc.ByteWidth = sizeof(float) * (m_amountOfPart * 4);
	_OBJvertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	_OBJvertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	_OBJvertexBufferDesc.MiscFlags = 0;

	// Skapar vertex buffern
	device->CreateBuffer(&_OBJvertexBufferDesc, NULL, &m_vertexBuffer);

	CreateWICTextureFromFile(device, deviceContext, L"Resources\\star2.jpeg", nullptr, &m_partTex);

	int i = 0;
	return true;
}

bool PartSys::CreateShaders(ID3D11Device* device)
{

	//create vertex shader
	ID3DBlob* pVS = nullptr;
	D3DCompileFromFile(L"Shaders\\PartVS.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS_main", "vs_5_0", 0, NULL, &pVS, nullptr);

	device->CreateVertexShader(pVS->GetBufferPointer(), pVS->GetBufferSize(), nullptr, &m_vertexShader);

	//create input layout (verified with vertex shader)
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	device->CreateInputLayout(inputDesc, ARRAYSIZE(inputDesc), pVS->GetBufferPointer(), pVS->GetBufferSize(), &m_vertexLayout);
	pVS->Release();

	ID3DBlob* pGS = nullptr;
	D3DCompileFromFile(L"Shaders\\PartGS.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "GS_main", "gs_5_0", 0, NULL, &pGS, nullptr);
	device->CreateGeometryShader(pGS->GetBufferPointer(), pGS->GetBufferSize(), nullptr, &m_geometryShader);
	pGS->Release();

	//create pixel shader
	ID3DBlob* pPS = nullptr;
	D3DCompileFromFile(L"Shaders\\PartPS.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS_main", "ps_5_0", 0, NULL, &pPS, nullptr);
	device->CreatePixelShader(pPS->GetBufferPointer(), pPS->GetBufferSize(), nullptr, &m_pixelShader);
	pPS->Release();


	return true;
}

bool PartSys::PartRend(ID3D11DeviceContext* deviceContext)
{
	deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
	deviceContext->HSSetShader(nullptr, nullptr, 0);
	deviceContext->DSSetShader(nullptr, nullptr, 0);
	deviceContext->GSSetShader(m_geometryShader, nullptr, 0);
	deviceContext->PSSetShader(m_pixelShader, nullptr, 0);

	UINT32 vertexSize = sizeof(float) * 4;
	UINT32 offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &vertexSize, &offset);

	deviceContext->PSSetShaderResources(0, 1, &m_partTex);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	deviceContext->IASetInputLayout(m_vertexLayout);

	deviceContext->Draw(m_amountOfPart, 0);

	return true;
}