#include "CVector3.h"
#include <cmath>
#include "CUtils.h"
using namespace Cinkes;

CVector3::CVector3() : m_Values{0,0,0}
{

}

Cinkes::CVector3::CVector3(CScalar a_X, CScalar a_Y, CScalar a_Z) : m_Values{a_X, a_Y, a_Z}
{

}

Cinkes::CVector3::CVector3(const CVector3& a_Vector) : m_Values{a_Vector.m_Values[0], a_Vector.m_Values[1], a_Vector.m_Values[2]}
{
}

Cinkes::CVector3::CVector3(CVector3&& a_Vector) noexcept
{
	m_Values[0] = a_Vector.m_Values[0];
	m_Values[1] = a_Vector.m_Values[1];
	m_Values[2] = a_Vector.m_Values[2];

}

CVector3& Cinkes::CVector3::operator=(CVector3&& a_Rhs) noexcept
{
	m_Values[0] = a_Rhs[0];
	m_Values[1] = a_Rhs[1];
	m_Values[2] = a_Rhs[2];
	return *this;
}

CScalar Cinkes::CVector3::getX()
{
	return m_Values[0];
}

CScalar Cinkes::CVector3::getX() const
{
	return m_Values[0];
}

CScalar Cinkes::CVector3::getY()
{
	return m_Values[1];
}

CScalar Cinkes::CVector3::getY() const
{
	return m_Values[1];
}

CScalar Cinkes::CVector3::getZ()
{
	return m_Values[2];
}

CScalar Cinkes::CVector3::getZ() const
{
	return m_Values[2];
}

void Cinkes::CVector3::setX(CScalar a_New)
{
	m_Values[0] = a_New;
}

void Cinkes::CVector3::setY(CScalar a_New)
{
	m_Values[1] = a_New;
}

void Cinkes::CVector3::setZ(CScalar a_New)
{
	m_Values[2] = a_New;
}

CVector3& CVector3::operator=(const CVector3& a_Rhs)
{
	if(this == &a_Rhs)
	{
		return *this;
	}
	m_Values[0] = a_Rhs[0];
	m_Values[1] = a_Rhs[1];
	m_Values[2] = a_Rhs[2];

	return *this;

}

void Cinkes::CVector3::operator+=(const CVector3& a_Rhs)
{
	m_Values[0] += a_Rhs.m_Values[0];
	m_Values[1] += a_Rhs.m_Values[1];
	m_Values[2] += a_Rhs.m_Values[2];
}

void Cinkes::CVector3::operator-=(const CVector3& a_Rhs)
{
	m_Values[0] -= a_Rhs.m_Values[0];
	m_Values[1] -= a_Rhs.m_Values[1];
	m_Values[2] -= a_Rhs.m_Values[2];
}

void Cinkes::CVector3::operator*=(const CVector3& a_Rhs)
{
	m_Values[0] *= a_Rhs.m_Values[0];
	m_Values[1] *= a_Rhs.m_Values[1];
	m_Values[2] *= a_Rhs.m_Values[2];
}

void Cinkes::CVector3::operator/=(const CVector3& a_Rhs)
{
	m_Values[0] /= a_Rhs.m_Values[0];
	m_Values[1] /= a_Rhs.m_Values[1];
	m_Values[2] /= a_Rhs.m_Values[2];
}

void CVector3::operator+=(CScalar a_Rhs)
{
	m_Values[0] += a_Rhs;
	m_Values[1] += a_Rhs;
	m_Values[2] += a_Rhs;
}

void CVector3::operator-=(CScalar a_Rhs)
{
	m_Values[0] -= a_Rhs;
	m_Values[1] -= a_Rhs;
	m_Values[2] -= a_Rhs;
}

void CVector3::operator*=(CScalar a_Rhs)
{
	m_Values[0] *= a_Rhs;
	m_Values[1] *= a_Rhs;
	m_Values[2] *= a_Rhs;
}

void CVector3::operator/=(CScalar a_Rhs)
{
	m_Values[0] /= a_Rhs;
	m_Values[1] /= a_Rhs;
	m_Values[2] /= a_Rhs;
}

const CVector3 Cinkes::CVector3::operator+(const CVector3& a_Rhs) const
{
	return CVector3(m_Values[0] - a_Rhs.m_Values[0], m_Values[1] - a_Rhs.m_Values[1], m_Values[2] - a_Rhs.m_Values[2]);
}

CVector3 Cinkes::CVector3::operator+(const CVector3& a_Rhs)
{
	return CVector3(m_Values[0] + a_Rhs.m_Values[0], m_Values[1] + a_Rhs.m_Values[1], m_Values[2] + a_Rhs.m_Values[2]);
}

CVector3 Cinkes::CVector3::operator-(const CVector3& a_Rhs)
{
	return CVector3(m_Values[0] - a_Rhs.m_Values[0], m_Values[1] - a_Rhs.m_Values[1], m_Values[2] - a_Rhs.m_Values[2]);
}

CVector3 Cinkes::CVector3::operator-(const CVector3& a_Rhs) const
{
	return CVector3(m_Values[0] - a_Rhs.m_Values[0], m_Values[1] - a_Rhs.m_Values[1], m_Values[2] - a_Rhs.m_Values[2]);
}

CVector3 Cinkes::CVector3::operator*(const CVector3& a_Rhs)
{
	return CVector3(m_Values[0] * a_Rhs.m_Values[0], m_Values[1] * a_Rhs.m_Values[1], m_Values[2] * a_Rhs.m_Values[2]);
}

CVector3 Cinkes::CVector3::operator*(const CVector3& a_Rhs) const
{
	return CVector3(m_Values[0] * a_Rhs.m_Values[0], m_Values[1] * a_Rhs.m_Values[1], m_Values[2] * a_Rhs.m_Values[2]);
}

CVector3 Cinkes::CVector3::operator/(const CVector3& a_Rhs)
{
	return CVector3(m_Values[0] / a_Rhs.m_Values[0], m_Values[1] / a_Rhs.m_Values[1], m_Values[2] / a_Rhs.m_Values[2]);
}

CVector3 Cinkes::CVector3::operator+(CScalar a_Rhs) const
{
	return CVector3(m_Values[0] + a_Rhs, m_Values[1] + a_Rhs, m_Values[2] + a_Rhs);
}

CVector3 CVector3::operator+(CScalar a_Rhs)
{
	return CVector3(m_Values[0] + a_Rhs, m_Values[1] + a_Rhs, m_Values[2] + a_Rhs);
}

CVector3 CVector3::operator-(CScalar a_Rhs)
{
	return CVector3(m_Values[0] - a_Rhs, m_Values[1] - a_Rhs, m_Values[2] - a_Rhs);
}

CVector3 Cinkes::CVector3::operator*(CScalar a_Rhs) const
{
	return CVector3(m_Values[0] * a_Rhs, m_Values[1] * a_Rhs, m_Values[2] * a_Rhs);
}

CVector3 CVector3::operator*(CScalar a_Rhs)
{
	return CVector3(m_Values[0] * a_Rhs, m_Values[1] * a_Rhs, m_Values[2] * a_Rhs);
}

CVector3 CVector3::operator/(CScalar a_Rhs)
{
	return CVector3(m_Values[0] / a_Rhs, m_Values[1] / a_Rhs, m_Values[2] / a_Rhs);
}

CScalar& Cinkes::CVector3::operator[](unsigned a_Rhs)
{
	return m_Values[a_Rhs];
}

float CVector3::operator[](unsigned a_Rhs) const
{
	return m_Values[a_Rhs];
}

bool Cinkes::CVector3::operator==(const CVector3& a_Rhs) const
{
	return (CUtils::Abs(m_Values[0] - a_Rhs.m_Values[0]) < CEPSILON) && 
			(CUtils::Abs(m_Values[1] - a_Rhs.m_Values[1]) < CEPSILON) &&
			(CUtils::Abs(m_Values[2] - a_Rhs.m_Values[2]) < CEPSILON);
}

bool Cinkes::CVector3::operator!=(const CVector3& a_Rhs) const
{
	return m_Values[0] != a_Rhs.m_Values[0] || m_Values[1] != a_Rhs.m_Values[1] || m_Values[2] != a_Rhs.m_Values[2];
}

CScalar Cinkes::CVector3::Length2()
{
	return CScalar(m_Values[0] * m_Values[0] + m_Values[1] * m_Values[1] + m_Values[2] * m_Values[2]);
}

CScalar Cinkes::CVector3::Length()
{
#if USE_DOUBLE == true
	return std::sqrt(Length2());
#else
	return std::sqrtf(Length2());
#endif
}

void Cinkes::CVector3::Normalize()
{
	CScalar length = Length();
	if (length != CScalar(0)) {
		m_Values[0] /= length;
		m_Values[1] /= length;
		m_Values[2] /= length;
	}
}

CScalar Cinkes::CVector3::Dot(const CVector3 & a_Rhs)
{
	return m_Values[0] * a_Rhs.m_Values[0] + m_Values[1] * a_Rhs.m_Values[1] + m_Values[2] * a_Rhs.m_Values[2];
}

CScalar Cinkes::CVector3::Dot(const CVector3& a_Rhs) const
{
	return m_Values[0] * a_Rhs.m_Values[0] + m_Values[1] * a_Rhs.m_Values[1] + m_Values[2] * a_Rhs.m_Values[2];
}

CVector3 CVector3::Dot3(const CVector3& a_V0, const CVector3& a_V1, const CVector3& a_V2)
{
	return CVector3(Dot(a_V0), Dot(a_V1), Dot(a_V2));
}

CVector3 CVector3::Cross(const CVector3& a_Rhs)
{
	CVector3 result;
	result[0] = m_Values[1] * a_Rhs[2] - m_Values[2] * a_Rhs[1];
	result[1] = m_Values[2] * a_Rhs[0] - m_Values[0] * a_Rhs[2];
	result[2] = m_Values[0] * a_Rhs[1] - m_Values[1] * a_Rhs[0];

	if((result - CScalar(0.0001)).Length() < 0)
	{
		return a_Rhs;
	}
	return result;
}

CVector3 Cinkes::CVector3::Cross(const CVector3& a_Rhs) const
{
	CVector3 result;
	result[0] = m_Values[1] * a_Rhs[2] - m_Values[2] * a_Rhs[1];
	result[1] = m_Values[2] * a_Rhs[0] - m_Values[0] * a_Rhs[2];
	result[2] = m_Values[0] * a_Rhs[1] - m_Values[1] * a_Rhs[0];

	if ((result - CScalar(0.0001)).Length() < 0)
	{
		return a_Rhs;
	}
	return result;
}

CVector3 CVector3::Lerp(const CVector3& a_Other, CScalar a_T)
{
	return CVector3(m_Values[0] + (a_Other.m_Values[0] - m_Values[0]) * a_T,
					m_Values[1] + (a_Other.m_Values[1] - m_Values[1]) * a_T,
					m_Values[2] + (a_Other.m_Values[2] - m_Values[2]) * a_T);
}
