#pragma once
#ifndef _EXPLOSIONPART_H_
#define _EXPLOSIONPART_H_
#include "Graphics\ParticleSys.h"

class ExplosionPart : public PartSys
{
private:
	struct VertexInput
	{
		XMFLOAT4 Pos;
		XMFLOAT4 Source;
	};
public:
	ExplosionPart();
	ExplosionPart(float offset, float lifeLenght);
	~ExplosionPart();
	bool CreateBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, wstring texName);
	bool Render(ID3D11DeviceContext* deviceContext);
	void Update(ID3D11DeviceContext* deviceContext, float time, float partSpeed);
	void Update(ID3D11DeviceContext* deviceContext, float time, float partSpeed, std::vector<Entity*> entity);
	void SetBuffer(ID3D11DeviceContext* deviceContext);
	void AddPartSys(std::vector<Entity*> entity, XMFLOAT4 addPos);
private:
	XMFLOAT4 m_ExplosionPos;
	XMFLOAT3 *m_movementVec;
	ID3D11Buffer* m_lightShiftPartBuffer;
	XMFLOAT4 m_lightShift;
	XMFLOAT4* m_sourcePos;
	VertexInput* m_inputData;
};



#endif