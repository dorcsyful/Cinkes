#include "CCylinder.h"

#include "../CinkesMath/CTransform.h"

Cinkes::CCylinder& Cinkes::CCylinder::operator=(CCylinder&& a_Rhs) noexcept
{
    m_Radius = a_Rhs.m_Radius;
    m_Height = a_Rhs.m_Height;
    return *this;
}

Cinkes::CCylinder& Cinkes::CCylinder::operator=(const CCylinder& a_Rhs) noexcept
{
    m_Radius = a_Rhs.m_Radius;
    m_Height = a_Rhs.m_Height;
    return *this;
}

Cinkes::CVector3 Cinkes::CCylinder::Support(const CVector3& a_V)
{
    const CVector3& dir = a_V;
    CVector3 segment = CVector3(m_Height * dir[0], 0, 0);
    CVector3 disc = (CVector3(m_Radius, m_Radius, 0) / CVector3(m_Radius, m_Radius, 0).Length()) * m_Radius;
    return segment + disc;
}

void Cinkes::CCylinder::CreateAABB(CVector3& a_Min, CVector3& a_Max)
{
    a_Min = CVector3(m_Radius * (-1), m_Radius * (-1), m_Height * (-1));
    a_Max = CVector3(m_Radius, m_Height, m_Height);
}

std::vector<Cinkes::CVector3> Cinkes::CCylinder::SupportPointsForContact(const CVector3& a_Direction, const CTransform& a_Position)
{
    return std::vector<CVector3>();
}
