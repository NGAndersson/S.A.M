#include "Renderer.h"

struct Vertex    //Overloaded Vertex Structure
{
	XMFLOAT3 pos;
	XMFLOAT2 tex;
	XMFLOAT3 normal;

	Vertex() {}
	Vertex(float x, float y, float z) {
		pos = XMFLOAT3(x, y, z);
		tex = XMFLOAT2(0.5f, 0.5f);
		normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
};

void Renderer::Render(ModelHandler * model, XMFLOAT3 position, XMMATRIX &rotation)
{
	//Set vertexbuffer, pixel material constant buffer and set the correct shaders
	model->SetBuffers(m_deviceContext);
	model->SetShaders(m_deviceContext);

	//Set Worldmatrix and Position(float3) as a Vertexshader constant buffer
	XMMATRIX Scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	XMMATRIX Translation = XMMatrixTranslation(position.x, position.y, position.z);
	m_worldStruct.worldMatrix = XMMatrixTranspose(Scale * rotation * Translation);

	m_deviceContext->UpdateSubresource(m_worldBuffer, 0, NULL, &m_worldStruct, 0, 0);
	m_deviceContext->VSSetConstantBuffers(0, 1, &m_worldBuffer);


	//Draw call
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_deviceContext->Draw(model->GetVertexCount(), 0);

	//Set the vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_deviceContext->IASetVertexBuffers(0, 1, &triangleVertBuffer, &stride, &offset);
	m_deviceContext->Draw(3, 0);

}

void Renderer::RenderInstanced(ModelHandler * model, XMFLOAT3 *position, XMMATRIX &rotation, int amountOfBullets)
{
	//Set vertexbuffer, pixel material constant buffer and set the correct shaders
	model->SetBuffers(m_deviceContext);
	model->SetShaders(m_deviceContext);
	XMMATRIX Translation;
	//Set Worldmatrix and Position(float3) as a Vertexshader constant buffer
	XMMATRIX Scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);

	XMFLOAT4X4 Test;

	XMFLOAT3 bulletpos[4];
	bulletpos[0] = XMFLOAT3(4, 0, 5);
	bulletpos[1] = XMFLOAT3(6, 0, 9);
	bulletpos[2] = XMFLOAT3(-9, 0, 78);
	bulletpos[3] = XMFLOAT3(56, 0, 0);

	D3D11_MAPPED_SUBRESOURCE _mappedResource;

	HRESULT hr = m_deviceContext->Map(m_worldBufferInstance, 0, D3D11_MAP_WRITE_DISCARD, 0, &_mappedResource);

	for (int i = 0; i < amountOfBullets; i++)
	{
		Translation = XMMatrixTranslation(bulletpos[i].x, bulletpos[i].y, bulletpos[i].z);
		XMStoreFloat4x4(&Test, XMMatrixTranspose(Scale * rotation * Translation));
		m_worldStructInstanced.worldMatrix[i] = Test;
	}

	memcpy(_mappedResource.pData, &m_worldStructInstanced, sizeof(WorldStructInstanced));

	m_deviceContext->Unmap(m_worldBufferInstance, 0);

	m_deviceContext->VSSetConstantBuffers(0, 1, &m_worldBufferInstance);

	//Draw call
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_deviceContext->DrawInstanced(model->GetVertexCount(), amountOfBullets, 0, 0);
}

Renderer::Renderer(ID3D11DeviceContext * deviceContext, ID3D11Device * device)
{
	m_device = device;
	m_deviceContext = deviceContext;

	m_cam.SetCameraPos(XMVectorSet(0.0f, 65.0f, 0.0f, 0.0f));
	m_cam.SetLookAtVec(XMVectorSet(0.0f, -100.0f, 0.0001f, 0.0f));
	m_cam.SetProjectionMatrix();
	m_cam.SetViewMatrix();
	m_cam.SetViewProjectionMatrix();
	m_cam.CreateBuffer(device);
	m_cam.SetConstantBuffer(deviceContext);

	D3D11_BUFFER_DESC _worldBufferDesc, _worldBufferInstanceDesc;

	//Create world constant buffer desc
	ZeroMemory(&_worldBufferDesc, sizeof(D3D11_BUFFER_DESC));

	_worldBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	_worldBufferDesc.ByteWidth = sizeof(WorldStruct);
	_worldBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_worldBufferDesc.CPUAccessFlags = 0;
	_worldBufferDesc.MiscFlags = 0;

	//Create the world constant buffer
	device->CreateBuffer(&_worldBufferDesc, NULL, &m_worldBuffer);

	//Create world constant buffer desc
	ZeroMemory(&_worldBufferInstanceDesc, sizeof(D3D11_BUFFER_DESC));

	_worldBufferInstanceDesc.Usage = D3D11_USAGE_DYNAMIC;
	_worldBufferInstanceDesc.ByteWidth = sizeof(WorldStructInstanced);
	_worldBufferInstanceDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_worldBufferInstanceDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	_worldBufferInstanceDesc.MiscFlags = 0;

	//Create the world constant buffer
	device->CreateBuffer(&_worldBufferInstanceDesc, NULL, &m_worldBufferInstance);

	//testy shit
	Vertex v[] =
	{
		Vertex(0.0f, 0.5f, 0.5f),
		Vertex(0.5f, -0.5f, 0.5f),
		Vertex(-0.5f, -0.5f, 0.5f),
	};

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * 3;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;

	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = v;
	device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &triangleVertBuffer);

	//Set the vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &triangleVertBuffer, &stride, &offset);

	//Set the Input Layout
	deviceContext->IASetInputLayout(vertLayout);
}
