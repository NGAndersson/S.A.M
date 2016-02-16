#pragma once
#ifndef _SPACEPART_H_
#define _SPACEPART_H_
#include "Graphics\ParticleSys.h"


class SpacePart : public PartSys
{
public:
	SpacePart();
	~SpacePart();
	bool CreateBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, wstring texName);
	bool Render(ID3D11DeviceContext* deviceContext);
	void Update(ID3D11DeviceContext* deviceContext, float time, float partSpeed);
	void Update(ID3D11DeviceContext* deviceContext, float time, float partSpeed, std::vector<Entity*> entity);
	void SetBuffer(ID3D11DeviceContext* deviceContext);
	void AddPartSys(std::vector<Entity*> entity, XMFLOAT4 addPos);
private:
};



#endif