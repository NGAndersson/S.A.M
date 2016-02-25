#pragma once
#ifndef _SHOOTINGPATTERNS_H
#define _SHOOTINGPATTERNS_H

#include <DirectXMath.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include "Entities\Bullets\Bullet_e.h"
#include <cstdlib>
#include <ctime>
#include <fstream>

struct Pattern
{
	string m_name;
	vector<XMFLOAT3> m_vector;
};

using namespace DirectX;
using namespace std;
class Shootingpatterns
{
private:
	

public:
	Shootingpatterns();
	~Shootingpatterns();
	void AddShot(vector<Entity*>* Bullet, SoundManager * SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health, XMFLOAT3 Color, int Index);
	void LoadPatterns(const string &filename);

private:
	int m_nrOfPatterns[4];
	int m_bulletIndex[4];
	vector<Pattern*> m_patterns[4];
};

#endif