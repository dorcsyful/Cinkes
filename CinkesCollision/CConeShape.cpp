#include "CConeShape.h"

#include "../CinkesMath/CTransform.h"

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

Cinkes::CVector3 Cinkes::CConeShape::Support(const CVector3& a_V, const CTransform& a_Position)
{
	CVector3 dir = a_Position.getBasis() * a_V;
	CVector3 temp = CVector3(dir[0], dir[1], 0);
	CVector3 result = (temp / temp.Length()) * m_Radius;
	CVector3 temp2 = CVector3(0, 0, m_Height);
	if(result.Dot(dir) > temp2.Dot(dir))
	{
		return a_Position.getOrigin() + result;
	} else
	{
		return a_Position.getOrigin() + temp2;
	}
}

void Cinkes::CConeShape::CreateAABB(CVector3& a_Min, CVector3& a_Max)
{
	a_Min = CVector3(m_Radius * (-1), m_Radius * (-1), m_Height * (-1));
	a_Max = CVector3(m_Radius, m_Height, m_Height);
}

std::vector<Cinkes::CVector3> Cinkes::CConeShape::SupportPointsForContact(const CVector3& a_Direction, const CTransform& a_Position)
{
	return std::vector<CVector3>();
}
