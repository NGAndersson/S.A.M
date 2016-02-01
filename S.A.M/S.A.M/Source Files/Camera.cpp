#include "Camera.h"


Camera::Camera()
{
	m_cameraPos = XMVectorSet(0, 0, 0, 0);
}

Camera::~Camera()
{

}

XMVECTOR Camera::GetCameraPos()
{
	return m_cameraPos;
}

XMVECTOR Camera::GetLookAtVec()
{
	return m_lookAtVec;
}

XMMATRIX Camera::GetViewMatrix()
{
	return m_view;
}

XMMATRIX Camera::GetProjectionMatrix()
{
	return m_projection;
}

XMMATRIX Camera::GetViewProjectionMatrix()
{
	return m_viewProjection;
}

void Camera::SetViewMatrix()
{
	m_view = XMMatrixLookAtLH(m_cameraPos, m_lookAtVec, XMVectorSet(0, 1, 0, 0));
}

void Camera::SetProjectionMatrix()
{
	m_projection = XMMatrixPerspectiveFovLH(XM_PI *0.45f, 640 / 480, 0.5f, 150);
}

void Camera::SetViewProjectionMatrix()
{
	 m_viewProjection = m_view * m_projection;
}

void Camera::SetCameraPos(XMVECTOR NewCameraPosition)
{
	m_cameraPos = NewCameraPosition;
}

void Camera::SetLookAtVec(XMVECTOR PositionLookingAt)
{
	m_lookAtVec = m_cameraPos + XMVector3Normalize(PositionLookingAt);
}

void Camera::SetConstantBuffer(ID3D11DeviceContext* gDeviceContext)
{
	D3D11_MAPPED_SUBRESOURCE _mappedResource;

	HRESULT hr = gDeviceContext->Map(m_constCameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &_mappedResource);
	m_constCamera = (CameraType*)_mappedResource.pData;
	m_constCamera->CameraPos = XMFLOAT4(XMVectorGetByIndex(m_cameraPos, 0), XMVectorGetByIndex(m_cameraPos, 1), XMVectorGetByIndex(m_cameraPos, 2), 0);
	XMStoreFloat4x4(&m_constCamera->ViewProjection, XMMatrixTranspose(m_viewProjection));

	gDeviceContext->Unmap(m_constCameraBuffer, 0);

	gDeviceContext->GSSetConstantBuffers(0, 1, &m_constCameraBuffer);
}