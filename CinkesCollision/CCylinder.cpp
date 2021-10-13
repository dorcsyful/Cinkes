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
