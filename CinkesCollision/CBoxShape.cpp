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

Cinkes::CLine Cinkes::CBoxShape::GetEdge(int a_Axis, const CVector3& a_Direction)
{
	int signX = CUtils::Sgn(a_Direction.getX(),1);
	int signY = CUtils::Sgn(a_Direction.getY(), 1);
	int signZ = CUtils::Sgn(a_Direction.getZ(), 1);

	CVector3 start = CVector3(signX * m_Dimensions[0], signY * m_Dimensions[1], signZ * m_Dimensions[2]);
	CVector3 end = start;

	switch (a_Axis)
	{
	case 0:  end[0] = -end[0]; break;
	case 1:  end[1] = -end[1]; break;
	default: end[2] = -end[2]; break;
	}

	return CLine(start, end);
}

void Cinkes::CBoxShape::CreateAABB(CVector3& a_Min, CVector3& a_Max)
{
	if(m_Dimensions[0] > static_cast<CScalar>(1))
	{
		a_Min[0] = m_Dimensions[0] * static_cast<CScalar>(-0.5);
		a_Max[0] = m_Dimensions[0] * static_cast<CScalar>(0.5);
	}
	else
	{
		a_Min[0] = -1;
		a_Max[0] = 1;
	}
	if(m_Dimensions[1] > static_cast<CScalar>(1))
	{
		a_Min[1] = m_Dimensions[1] * static_cast<CScalar>(-0.5);
		a_Max[1] = m_Dimensions[1] * static_cast<CScalar>(0.5);
	}
	else
	{
		a_Min[1] = -1;
		a_Max[1] = 1;
	}
	if (m_Dimensions[2] > static_cast<CScalar>(1))
	{
		a_Min[2] = m_Dimensions[2] * static_cast<CScalar>(-0.5);
		a_Max[2] = m_Dimensions[2] * static_cast<CScalar>(0.5);
	}
	else
	{
		a_Min[2] = -1;
		a_Max[2] = 1;
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
