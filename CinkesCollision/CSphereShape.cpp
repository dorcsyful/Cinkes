#include "CSphereShape.h"

void Cinkes::CSphereShape::CreateAABB(const CMat3x3& a_Rotation, CVector3& a_Min, CVector3& a_Max)
{
	a_Max = CVector3(m_Radius, m_Radius, m_Radius);
	CScalar temp = m_Radius * CScalar(-1);
	a_Min = CVector3(temp, temp, temp);
}