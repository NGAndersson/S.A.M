#pragma once
#ifndef _PARTICLESYS_H_
#define _PARTICLESYS_H_

#include <d3d11.h>
#include "Entities\Entity.h"
#include <DirectXMath.h>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <iostream>
#include <vector>
#include <d3dcompiler.h>
#include <cstdlib>
#include <ctime>
#include "WICTextureLoader.h"
using namespace std;
using namespace DirectX;

class PartSys
{
public:
	PartSys();
	PartSys(float offset, float lifeLenght);
	/*~PartSys();*/
	virtual bool CreateBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, wstring texName) = 0;
	virtual bool Render(ID3D11DeviceContext* deviceContext) = 0;
	virtual void Update(ID3D11DeviceContext* deviceContext, float time, float partSpeed) = 0;
	virtual void Update(ID3D11DeviceContext* deviceContext, float time, float partSpeed, std::vector<Entity*> entity) = 0;
	virtual void SetBuffer(ID3D11DeviceContext* deviceContext) = 0;
	virtual void AddPartSys(std::vector<Entity*> entity, XMFLOAT4 addPos) = 0;
	virtual float* GetTimeToLive() { return m_timeToLive; }
protected:
	ID3D11ShaderResourceView* m_partTex = nullptr;
	int m_amountOfPart, m_nrOfPositions = 0;
	XMFLOAT4* m_partPos;
	ID3D11Buffer *m_vertexBuffer = nullptr, *m_instancePartBuffer = nullptr;
	float* m_timeToLive, m_partLifeLenght, m_partOffset;
};



#endif