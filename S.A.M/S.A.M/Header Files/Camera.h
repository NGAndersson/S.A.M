#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "OBJloader.h"
#include "ShaderHandler.h"



class Camera
{
private:
	struct CameraType
	{
		XMFLOAT4 CameraPos;
		XMFLOAT4X4 ViewProjection;
	};
public:
	Camera();
	~Camera();
	XMVECTOR GetCameraPos();
	XMVECTOR GetLookAtVec();
	XMMATRIX GetViewMatrix();
	XMMATRIX GetProjectionMatrix();
	XMMATRIX GetViewProjectionMatrix();
	void SetViewMatrix();
	void SetProjectionMatrix();
	void SetViewProjectionMatrix();
	void SetCameraPos(XMVECTOR NewCameraPosition);
	void SetLookAtVec(XMVECTOR PositionLookingAt);

	void SetConstantBuffer(ID3D11DeviceContext* gDeviceContext);

	

private:
	XMVECTOR m_cameraPos, m_lookAtVec;
	XMMATRIX m_view, m_projection, m_viewProjection;
	ID3D11Buffer* m_constCameraBuffer;
	CameraType* m_constCamera;
	
};

#endif