#pragma once
#ifndef _PLAYERPART_H_
#define _PLAYERPART_H_
#include "Graphics\ParticleSys.h"



class PlayerPart : public PartSys
{
private:
	struct VertexInput
	{
		XMFLOAT4 Pos;
		XMFLOAT4 Source;
	};
public:
	PlayerPart();
	PlayerPart(float offset, float lifeLenght, std::vector<Entity*> entity);
	~PlayerPart();
	bool CreateBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, wstring texName);
	bool Render(ID3D11DeviceContext* deviceContext);
	void Update(ID3D11DeviceContext* deviceContext, float time, float partSpeed);
	void Update(ID3D11DeviceContext* deviceContext, float time, float partSpeed, std::vector<Entity*> entity);
	void SetBuffer(ID3D11DeviceContext* deviceContext);
	void AddPartSys(std::vector<Entity*> entity, XMFLOAT4 addPos);
private:
	XMFLOAT4* m_sourcePos;
	VertexInput* m_inputData;
	XMFLOAT4 m_rocketPos[20];
};



#endif
