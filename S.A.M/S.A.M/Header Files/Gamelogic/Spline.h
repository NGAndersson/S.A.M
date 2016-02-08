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
	Spline(int nrPath);
	~Spline();

	void GeneratePath(int NrPoints);	
	void GeneratePath(XMFLOAT2* Points);
	void GetPathPosition();

private:
	XMFLOAT3 CalcPoint();
	float CalcT(int x,int y);

private:
	float* m_path;
	double m_pathStartTime;

};

#endif //!ENDIF SPLINE
