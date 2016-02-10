#ifndef _SPLINE_H
#define _SPLINE_H

#include <DirectXMath.h>
#include <iostream>
#include <vector>
#include <stdio.h>

using namespace DirectX;
using namespace std;
class Spline
{
public:
	Spline();
	Spline(vector<XMFLOAT3> PathPositions);
	~Spline();
	XMFLOAT3 GetPathPosition(float t);
	int GetCurrPathNode() { return m_pathStartPoint; }
	void SetCurrPathNode(int PathNode) { m_pathStartPoint = PathNode; }
private:


private:
	vector<XMFLOAT3> m_pathPositions;
	int m_pathStartPoint = 0;
};

#endif //!ENDIF SPLINE
