#include "CConeShape.h"

Cinkes::CConeShape::CConeShape(CScalar a_Radius, CScalar a_Height)
{
	m_Height = a_Height;
	m_Radius = a_Radius;
	CScalar hypotenuse = CUtils::Sqrt((a_Radius * a_Radius) + (a_Height * a_Height));
	m_SinOfAngle = CUtils::Sin(m_Height / hypotenuse);
}

Cinkes::CConeShape::CConeShape(const CConeShape& a_Rhs)
{
	m_Height = a_Rhs.m_Height;
	m_Radius = a_Rhs.m_Radius;
	m_SinOfAngle = a_Rhs.m_SinOfAngle;
}

Cinkes::CConeShape::CConeShape(CConeShape&& a_Rhs) noexcept 
{
	m_Height = a_Rhs.m_Height;
	m_Radius = a_Rhs.m_Radius;
	m_SinOfAngle = a_Rhs.m_SinOfAngle;
}

Cinkes::CConeShape& Cinkes::CConeShape::operator=(CConeShape&& a_Rhs) noexcept
{
	m_Height = a_Rhs.m_Height;
	m_Radius = a_Rhs.m_Radius;
	m_SinOfAngle = a_Rhs.m_SinOfAngle;

	return *this;
}

Cinkes::CConeShape& Cinkes::CConeShape::operator=(const CConeShape& a_Rhs) noexcept
{
	m_Height = a_Rhs.m_Height;
	m_Radius = a_Rhs.m_Radius;
	m_SinOfAngle = a_Rhs.m_SinOfAngle;

	return *this;
}

void Cinkes::CConeShape::setRadius(CScalar a_New)
{
	m_Radius = a_New;
	CScalar hypotenuse = CUtils::Sqrt((m_Radius * m_Radius) + (m_Height * m_Height));
	m_SinOfAngle = CUtils::Sin(m_Height / hypotenuse);
}

void Cinkes::CConeShape::setHeight(CScalar a_New)
{
	m_Height = a_New;
	CScalar hypotenuse = CUtils::Sqrt((m_Radius * m_Radius) + (m_Height * m_Height));
	m_SinOfAngle = CUtils::Sin(m_Height / hypotenuse);
}

Cinkes::CVector3 Cinkes::CConeShape::Support(const CVector3& a_V)
{
	CVector3 temp = CVector3(a_V[0], a_V[1], 0);
	CVector3 result = (temp / temp.Length()) * m_Radius;
	CVector3 temp2 = CVector3(0, 0, m_Height);
	if(result.Dot(a_V) > temp2.Dot(a_V))
	{
		return result;
	} else
	{
		return temp2;
	}
}
