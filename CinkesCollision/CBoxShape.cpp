#include "CBoxShape.h"

#include <algorithm>

#include "../CinkesMath/CTransform.h"
#include "../CinkesMath/CUtils.h"

Cinkes::CVector3 Cinkes::CBoxShape::Support(const CVector3& a_V)
{
	CScalar temp1 = CUtils::Sgn(1, a_V[0]) * (m_Dimensions[0]);
	CScalar temp2 = CUtils::Sgn(1, a_V[1]) * (m_Dimensions[1]);
	CScalar temp3 = CUtils::Sgn(1, a_V[2]) * (m_Dimensions[2]);
	return CVector3(temp1, temp2, temp3);
}

void Cinkes::CBoxShape::CreateAABB(const CMat3x3& a_Rotation, CVector3& a_Min, CVector3& a_Max)
{
	CVector3 temp_min, temp_max;
	temp_min[0] = -m_Dimensions[0];
	temp_max[0] =  m_Dimensions[0];
	temp_min[1] = -m_Dimensions[1];
	temp_max[1] =  m_Dimensions[1];
	temp_min[2] = -m_Dimensions[2];
	temp_max[2] =  m_Dimensions[2];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
		{
			CScalar a = a_Rotation[i][j] * temp_min[j];
			CScalar b = a_Rotation[i][j] * temp_max[j];
			if (a < b)

			{
				a_Min[i] += a;
				a_Max[i] += b;
			}
			else
			{
				a_Min[i] += b;
				a_Max[i] += a;
			}
		}
	}
}

Cinkes::CMat3x3 Cinkes::CBoxShape::CalculateInertiaTensor(CScalar a_Mass)
{

	CScalar lx = CScalar(2.) * (m_Dimensions[0]);
	CScalar ly = CScalar(2.) * (m_Dimensions[1]);
	CScalar lz = CScalar(2.) * (m_Dimensions[2]);
	CMat3x3 inertia;
	inertia[0][0] = a_Mass / (CScalar(12.0)) * (ly * ly + lz * lz);
	inertia[1][1] = a_Mass / (CScalar(12.0)) * (lx * lx + lz * lz);
	inertia[2][2] = a_Mass / (CScalar(12.0)) * (lx * lx + ly * ly);

	return inertia;
}
