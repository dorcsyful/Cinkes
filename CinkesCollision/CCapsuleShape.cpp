#include "CCapsuleShape.h"
#include "CCapsuleShape.h"
#include "../CinkesMath/CUtils.h"


Cinkes::CVector3 Cinkes::CCapsuleShape::Support(const CVector3& a_V)
{
    CVector3 segment = CVector3(m_Height * a_V[0], 0, 0);
    return segment + (a_V * m_Radius);
}

void Cinkes::CCapsuleShape::CreateAABB(CVector3& a_Min, CVector3& a_Max)
{
    a_Min = CVector3(m_Radius * (-1), m_Radius * (-1), m_Height * (-1) - m_Radius);
    a_Max = CVector3(m_Radius, m_Height, m_Height + m_Radius);
}
