#include "CCapsuleShape.h"
#include "CCapsuleShape.h"

#include "../CinkesMath/CTransform.h"
#include "../CinkesMath/CUtils.h"


Cinkes::CVector3 Cinkes::CCapsuleShape::Support(const CVector3& a_V, const CTransform& a_Position)
{
    CVector3 dir = a_Position.getBasis() * a_V;
    CVector3 segment = CVector3(m_Height * dir[0], 0, 0);
    return a_Position.getOrigin() + segment + (dir * m_Radius);
}

void Cinkes::CCapsuleShape::CreateAABB(CVector3& a_Min, CVector3& a_Max)
{
    a_Min = CVector3(m_Radius * (-1), m_Radius * (-1), m_Height * (-1) - m_Radius);
    a_Max = CVector3(m_Radius, m_Height, m_Height + m_Radius);
}

std::vector<Cinkes::CVector3> Cinkes::CCapsuleShape::SupportPointsForContact(const CVector3& a_Direction, const CTransform& a_Position)
{
    return std::vector<CVector3>();
}
