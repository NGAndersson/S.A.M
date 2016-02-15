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
	~PartSys();
	bool CreateBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const wstring &texName);
	bool CreateRocketBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const wstring &texName);
	bool PartRend(ID3D11DeviceContext*);
	bool InstancePartRend(ID3D11DeviceContext* deviceContext);
	void BackGroundUpdatePart(ID3D11DeviceContext* deviceContext, float time, float partSpeed);
	void BackGround();
	void RocketPartSys(float offset, float lifeLenght);
	void UpdateRocketPartSys(ID3D11DeviceContext* deviceContext, float time, float partSpeed);
	void SetRocketBuffer(ID3D11DeviceContext* deviceContext);
	void AddRocketPartSys(std::vector<Entity*> entity, const XMFLOAT4 &addPos);
private:
	ID3D11ShaderResourceView* m_partTex = nullptr;
	int m_amountOfPart, m_nrOfPositions = 0;
	XMFLOAT4* m_partPos;
	ID3D11Buffer *m_vertexBuffer = nullptr, *m_instancePartBuffer = nullptr;
	XMFLOAT4 m_rocketPos[20];
	float* m_timeToLive, m_partLifeLenght, m_partOffset;
};



#endif