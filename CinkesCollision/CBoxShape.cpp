#include "CBoxShape.h"
#include "../CinkesMath/CUtils.h"


Cinkes::CVector3 Cinkes::CBoxShape::Support(const CVector3& a_V)
{
	CVector3 result;
	result[0] = CUtils::Sgn(1, a_V[0]) * (m_Dimensions[0] / 2);
	result[1] = CUtils::Sgn(1, a_V[1]) * (m_Dimensions[1] / 2);
	result[2] = CUtils::Sgn(1, a_V[2]) * (m_Dimensions[2] / 2);
	return result;
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
