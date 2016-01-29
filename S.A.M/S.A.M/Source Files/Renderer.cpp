#include "Renderer.h"

void Renderer::Render(ModelHandler * model, XMFLOAT3 position, XMMATRIX* rotation)
{
	//Set vertexbuffer, pixel material constant buffer and set the correct shaders
	model->SetBuffers(m_deviceContext);
	model->SetShaders(m_deviceContext);

	//Set Worldmatrix and Position(float3) as a Vertexshader constant buffer
	m_worldStruct.worldMatrix = XMMatrixTranspose(XMMatrixTranslation(position.x, position.y, position.z));// **rotation);
	m_worldStruct.worldPos = position;
	m_deviceContext->VSSetConstantBuffers(0, 1, &m_worldBuffer);

	//Set CameraPos(float3) and ViewProjectionMatrix as Geometryshader constant buffer
	XMVECTOR _cameraPosVec = m_cam.GetCameraPos();
	m_camStruct.camPos = XMFLOAT4(XMVectorGetByIndex(_cameraPosVec, 0), XMVectorGetByIndex(_cameraPosVec, 1), XMVectorGetByIndex(_cameraPosVec, 2), 0);
	//m_camStruct.viewProjection = m_cam.GetViewProjectionMatrix();
	m_camStruct.viewProjection = XMMatrixTranspose(m_cam.GetViewProjectionMatrix());
	m_deviceContext->GSSetConstantBuffers(0, 1, &m_camBuffer);

	//Draw call
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_deviceContext->Draw(model->GetVertexCount(), 0);
}

Renderer::Renderer(ID3D11DeviceContext * deviceContext, ID3D11Device * device)
{
	m_device = device;
	m_deviceContext = deviceContext;

	m_cam.SetCameraPos(XMVectorSet(0.0f, 10.0f, 0.0f, 0.0f));
	m_cam.SetLookAtVec(XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f));
	m_cam.SetProjectionMatrix();
	m_cam.SetViewMatrix();
	m_cam.SetViewProjectionMatrix();

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

	//Create camera constant buffer desc
	ZeroMemory(&_camBufferDesc, sizeof(D3D11_BUFFER_DESC));

	_camBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	_camBufferDesc.ByteWidth = sizeof(CamStruct);
	_camBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_camBufferDesc.CPUAccessFlags = 0;
	_camBufferDesc.MiscFlags = 0;

	//Create the camera constant buffer
	device->CreateBuffer(&_camBufferDesc, NULL, &m_camBuffer);
}
