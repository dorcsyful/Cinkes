#include "CCylinder.h"

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
    CVector3 segment = CVector3(m_Height * a_V[0], 0, 0);
    CVector3 disc = (CVector3(m_Radius, m_Radius, 0) / CVector3(m_Radius, m_Radius, 0).Length()) * m_Radius;
    return segment + disc;
}
