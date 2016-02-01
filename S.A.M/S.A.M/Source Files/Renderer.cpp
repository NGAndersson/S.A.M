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

void Renderer::Render(ModelHandler * model, XMFLOAT3 position, XMMATRIX* rotation)
{
	//Set vertexbuffer, pixel material constant buffer and set the correct shaders
	model->SetBuffers(m_deviceContext);
	model->SetShaders(m_deviceContext);

	//Set Worldmatrix and Position(float3) as a Vertexshader constant buffer
	XMMATRIX Scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	XMMATRIX Translation = XMMatrixTranslation(0.0f, 0.0f, -10.0f);
	//m_worldStruct.worldMatrix = XMMatrixTranslation(position.x, position.y, position.z);// **rotation);
	//m_worldStruct.worldPos = position;
	//m_worldStruct.worldMatrix = XMMatrixIdentity();
	m_worldStruct.worldMatrix = XMMatrixTranspose(Scale * Translation);
	
	m_deviceContext->UpdateSubresource(m_worldBuffer, 0, NULL, &m_worldStruct, 0, 0);
	m_deviceContext->VSSetConstantBuffers(0, 1, &m_worldBuffer);

	
	/*
	//Set CameraPos(float3) and ViewProjectionMatrix as Geometryshader constant buffer
	XMVECTOR _cameraPosVec = m_cam.GetCameraPos();
	m_camStruct.camPos = XMFLOAT4(XMVectorGetByIndex(_cameraPosVec, 0), XMVectorGetByIndex(_cameraPosVec, 1), XMVectorGetByIndex(_cameraPosVec, 2), 0);
	//m_camStruct.viewProjection = m_cam.GetViewProjectionMatrix();
	m_camStruct.viewProjection = XMMatrixTranspose(m_cam.GetViewProjectionMatrix());
	m_deviceContext->UpdateSubresource(m_camBuffer, 0, NULL, &m_camStruct, 0, 0);
	m_deviceContext->VSSetConstantBuffers(1, 1, &m_camBuffer);
	*/

	//Testy shit

	

	//Draw call
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_deviceContext->Draw(model->GetVertexCount()/3, 0);

	//Set the vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_deviceContext->IASetVertexBuffers(0, 1, &triangleVertBuffer, &stride, &offset);
	m_deviceContext->Draw(3, 0);

}

Renderer::Renderer(ID3D11DeviceContext * deviceContext, ID3D11Device * device)
{
	m_device = device;
	m_deviceContext = deviceContext;

	m_cam.SetCameraPos(XMVectorSet(0.0f, 0.0f, -30.0f, 0.0f));
	m_cam.SetLookAtVec(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f));
	m_cam.SetProjectionMatrix();
	m_cam.SetViewMatrix();
	m_cam.SetViewProjectionMatrix();
	m_cam.CreateBuffer(device);
	m_cam.SetConstantBuffer(deviceContext);

	D3D11_BUFFER_DESC _worldBufferDesc, _camBufferDesc;
	
	//Create world constant buffer desc
	ZeroMemory(&_worldBufferDesc, sizeof(D3D11_BUFFER_DESC));

	_worldBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	_worldBufferDesc.ByteWidth = sizeof(WorldStruct);
	_worldBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_worldBufferDesc.CPUAccessFlags = 0;
	_worldBufferDesc.MiscFlags = 0;

	//Create the world constant buffer
	device->CreateBuffer(&_worldBufferDesc, NULL, &m_worldBuffer);
		
	/*
	//Create camera constant buffer desc
	ZeroMemory(&_camBufferDesc, sizeof(D3D11_BUFFER_DESC));

	_camBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	_camBufferDesc.ByteWidth = sizeof(CamStruct);
	_camBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_camBufferDesc.CPUAccessFlags = 0;
	_camBufferDesc.MiscFlags = 0;

	//Create the camera constant buffer
	device->CreateBuffer(&_camBufferDesc, NULL, &m_camBuffer);
	*/

	
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
