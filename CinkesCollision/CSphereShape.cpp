#include "CSphereShape.h"

void Cinkes::CSphereShape::CreateAABB(CVector3& a_Min, CVector3& a_Max)
{
	a_Max = CVector3(m_Radius, m_Radius, m_Radius);
	CScalar temp = m_Radius * CScalar(-1);
	a_Min = CVector3(temp, temp, temp);
}

std::vector<Cinkes::CVector3> Cinkes::CSphereShape::SupportPointsForContact(const CVector3& a_Direction, const CVector3& a_Position)
{
	return std::vector<CVector3>();
}
