#pragma once
#ifndef _FIREPART_H_
#define _FIREPART_H_
#include "Graphics\ParticleSys.h"

class FirePart : public PartSys
{
public:
	FirePart();
	FirePart(float offset, float lifeLenght);
	~FirePart();
	bool CreateBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, wstring texName);
	bool Render(ID3D11DeviceContext* deviceContext);
	void Update(ID3D11DeviceContext* deviceContext, float time, float partSpeed);
	void Update(ID3D11DeviceContext* deviceContext, float time, float partSpeed, std::vector<Entity*> entity);
	void SetBuffer(ID3D11DeviceContext* deviceContext);
	void AddPartSys(std::vector<Entity*> entity, XMFLOAT4 addPos);
private:
	XMFLOAT4 m_rocketPos[20];
};



#endif