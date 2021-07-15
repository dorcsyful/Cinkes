#include "CVector3.h"
#include <cmath>
using namespace Cinkes;

Cinkes::CVector3::CVector3()
{
	values[0] = 0;
	values[1] = 0;
	m_Z = 0;
}

Cinkes::CVector3::CVector3(CScalar a_X, CScalar a_Y, CScalar a_Z)
{
	values[0] = a_X;
	m_Y = a_Y;
	m_Z = a_Z;
}

Cinkes::CVector3::CVector3(const CVector3& a_Vector)
{
	values[0] = a_Vector.values[0];
	m_Y = a_Vector.m_Y;
	m_Z = a_Vector.m_Z;
}

CScalar Cinkes::CVector3::getX()
{
	return values[0];
}

CScalar Cinkes::CVector3::getY()
{
	return m_Y;
}

CScalar Cinkes::CVector3::getZ()
{
	return m_Z;
}

void Cinkes::CVector3::setX(CScalar a_New)
{
	values[0] = a_New;
}

void Cinkes::CVector3::setY(CScalar a_New)
{
	m_Y = a_New;
}

void Cinkes::CVector3::setZ(CScalar a_New)
{
	m_Z = a_New;
}

void Cinkes::CVector3::operator+=(const CVector3& a_Rhs)
{
	values[0] += a_Rhs.values[0];
	m_Y += a_Rhs.m_Y;
	m_Z += a_Rhs.m_Z;
}

void Cinkes::CVector3::operator-=(const CVector3& a_Rhs)
{
	values[0] -= a_Rhs.values[0];
	m_Y -= a_Rhs.m_Y;
	m_Z -= a_Rhs.m_Z;
}

void Cinkes::CVector3::operator*=(const CVector3& a_Rhs)
{
	values[0] *= a_Rhs.values[0];
	m_Y *= a_Rhs.m_Y;
	m_Z *= a_Rhs.m_Z;
}

void Cinkes::CVector3::operator/=(const CVector3& a_Rhs)
{
	values[0] /= a_Rhs.values[0];
	m_Y /= a_Rhs.m_Y;
	m_Z /= a_Rhs.m_Z;
}

CVector3 Cinkes::CVector3::operator+(const CVector3& a_Rhs)
{
	return CVector3(values[0] + a_Rhs.values[0], m_Y + a_Rhs.m_Y, m_Z + a_Rhs.m_Z);
}

CVector3 Cinkes::CVector3::operator-(const CVector3& a_Rhs)
{
	return CVector3(values[0] - a_Rhsvalues[0], m_Y - a_Rhs.m_Y, m_Z - a_Rhs.m_Z);
}

CVector3 Cinkes::CVector3::operator*(const CVector3& a_Rhs)
{
	return CVector3(values[0] * a_Rhs.values[0], m_Y * a_Rhs.m_Y, m_Z * a_Rhs.m_Z);
}

CVector3 Cinkes::CVector3::operator/(const CVector3& a_Rhs)
{
	return CVector3(values[0] / a_Rhs.values[0], m_Y / a_Rhs.m_Y, m_Z / a_Rhs.m_Z);
}

bool Cinkes::CVector3::operator==(const CVector3& a_Rhs)
{
	return values[0] == a_Rhs.values[0] && m_Y == a_Rhs.m_Y && m_Z == a_Rhs.m_Z;
}

bool Cinkes::CVector3::operator!=(const CVector3& a_Rhs)
{
	return values[0] != a_Rhs.values[0] || m_Y != a_Rhs.m_Y || m_Z != a_Rhs.m_Z;
}

CScalar Cinkes::CVector3::Length2()
{
	return CScalar(values[0] * values[0] + m_Y * m_Y + m_Z * m_Z);
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
	values[0] /= Length();
	m_Y /= Length();
	m_Z /= Length();
}

CScalar Cinkes::CVector3::Dot(CVector3 a_Rhs)
{
	return CScalar(values[0] * a_Rhs.values[0] + m_Y * a_Rhs.m_Y + m_Z * a_Rhs.m_Z);
}

CVector3 Cinkes::CVector3::Cross(CVector3 a_Rhs)
{
	CVector3 result;
	cross_P[0] = vect_A[1] * vect_B[2] - vect_A[2] * vect_B[1];
	cross_P[1] = vect_A[2] * vect_B[0] - vect_A[0] * vect_B[2];
	cross_P[2] = vect_A[0] * vect_B[1] - vect_A[1] * vect_B[0];
	return CVector3();
}

CVector3 Cinkes::CVector3::Lerp(CVector3 a_Other, CScalar a_T)
{
	return CVector3();
}
