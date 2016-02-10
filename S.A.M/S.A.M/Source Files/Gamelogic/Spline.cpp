#include "..\..\Header Files\Gamelogic\Spline.h"

Spline::Spline()
{

}

Spline::~Spline()
{

}

Spline::Spline(vector<XMFLOAT3> PathPositions)
{
	m_pathPositions = PathPositions;
	m_pathStartPoint = 1;
}

XMFLOAT3 Spline::GetPathPosition(float t)
{

	XMFLOAT3 _pathPos[4];

	_pathPos[0] = m_pathPositions[(m_pathStartPoint - 1+m_pathPositions.size()) % m_pathPositions.size()];
	_pathPos[1] = m_pathPositions[m_pathStartPoint  % m_pathPositions.size()];
	_pathPos[2] = m_pathPositions[(m_pathStartPoint + 1+m_pathPositions.size()) % m_pathPositions.size()];
	_pathPos[3] = m_pathPositions[(m_pathStartPoint + 2+m_pathPositions.size()) % m_pathPositions.size()];

	float _p1x = 0, _p2x = 0, _p3x = 0, _p4x = 0;
	_p1x = 2 * _pathPos[1].x;
	_p2x = (-1.0 * _pathPos[0].x + _pathPos[2].x);
	_p3x = 2 * _pathPos[0].x - 5 * _pathPos[1].x + 4 * _pathPos[2].x - _pathPos[3].x;
	_p4x = -_pathPos[0].x + 3 * _pathPos[1].x - 3 * _pathPos[2].x + _pathPos[3].x;
	float _p1z = 0, _p2z = 0, _p3z = 0, _p4z = 0;
	_p1z = 2 * _pathPos[1].z;
	_p2z = (-1.0 * _pathPos[0].z + _pathPos[2].z);
	_p3z = 2 * _pathPos[0].z - 5 * _pathPos[1].z + 4 * _pathPos[2].z - _pathPos[3].z;
	_p4z = -_pathPos[0].z + 3 * _pathPos[1].z - 3 * _pathPos[2].z + _pathPos[3].z;

	float _returnX = 0, _returnZ = 0;
	_returnX = 0.5 * ((_p1x) + t*_p2x + t*t*_p3x + t*t*t*_p4x);
	_returnZ = 0.5 * ((_p1z) + t*_p2z + t*t*_p3z + t*t*t*_p4z);
	return XMFLOAT3(_returnX, 0, _returnZ);
}


