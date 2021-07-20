#include "CQuaternion.h"

#include "CUtils.h"

Cinkes::CQuaternion::CQuaternion()
{
	for(int i = 0; i < 4; i++)
	{
		m_Values[i] = 0;
	}
}

Cinkes::CQuaternion::CQuaternion(CScalar a_X, CScalar a_Y, CScalar a_Z, CScalar a_W)
{
	m_Values[0] = a_X;
	m_Values[1] = a_Y;
	m_Values[2] = a_Z;
	m_Values[3] = a_W;
}

Cinkes::CQuaternion::CQuaternion(const CQuaternion& a_Other)
{
	m_Values[0] = a_Other.m_Values[0];
	m_Values[1] = a_Other.m_Values[1];
	m_Values[2] = a_Other.m_Values[2];
	m_Values[3] = a_Other.m_Values[3];
	
}

Cinkes::CQuaternion::CQuaternion(CVector3 a_Axis, CScalar a_Angle)
{
	CScalar temp = CUtils::Sin(a_Angle / static_cast<CScalar>(2));
	m_Values[0] = a_Axis.getX() * temp;
	m_Values[1] = a_Axis.getY() * temp;
	m_Values[2] = a_Axis.getZ() * temp;
	m_Values[3] = CUtils::Cos(a_Angle / static_cast<CScalar>(2));	
}

Cinkes::CQuaternion::CQuaternion(CScalar a_Yaw, CScalar a_Pitch, CScalar a_Roll)
{
	CScalar cy = CUtils::Cos(a_Yaw * static_cast<CScalar>(0.5));
	CScalar sy = CUtils::Sin(a_Yaw * static_cast<CScalar>(0.5));
	CScalar cp = CUtils::Cos(a_Pitch * static_cast<CScalar>(0.5));
	CScalar sp = CUtils::Sin(a_Pitch * static_cast<CScalar>(0.5));
	CScalar cr = CUtils::Cos(a_Roll * static_cast<CScalar>(0.5));
	CScalar sr = CUtils::Sin(a_Roll * static_cast<CScalar>(0.5));

	m_Values[0] = cr * cp * cy + sr * sp * sy;
	m_Values[1] = sr * cp * cy - cr * sp * sy;
	m_Values[2] = cr * sp * cy + sr * cp * sy;
	m_Values[3] = cr * cp * sy - sr * sp * cy;
}

CScalar Cinkes::CQuaternion::getX()
{
	return m_Values[0];
}

CScalar Cinkes::CQuaternion::getY()
{
	return m_Values[1];
}

CScalar Cinkes::CQuaternion::getZ()
{
	return m_Values[2];
}

CScalar Cinkes::CQuaternion::getW()
{
	return m_Values[3];
}

void Cinkes::CQuaternion::setX(CScalar a_New)
{
	m_Values[0] = a_New;
}

void Cinkes::CQuaternion::setY(CScalar a_New)
{
	m_Values[1] = a_New;
}

void Cinkes::CQuaternion::setZ(CScalar a_New)
{
	m_Values[2] = a_New;
}

void Cinkes::CQuaternion::setW(CScalar a_New)
{
	m_Values[3] = a_New;
}

void Cinkes::CQuaternion::SetFromAngleAxis(CVector3 a_Axis, CScalar a_Angle)
{
	CScalar temp = CUtils::Sin(a_Angle / static_cast<CScalar>(2));
	m_Values[0] = a_Axis.getX() * temp;
	m_Values[1] = a_Axis.getY() * temp;
	m_Values[2] = a_Axis.getZ() * temp;
	m_Values[3] = CUtils::Cos(a_Angle / static_cast<CScalar>(2));
}

void Cinkes::CQuaternion::SetFromEuler(CScalar a_Yaw, CScalar a_Pitch, CScalar a_Roll)
{
	CScalar cy = CUtils::Cos(a_Yaw * static_cast<CScalar>(0.5));
	CScalar sy = CUtils::Sin(a_Yaw * static_cast<CScalar>(0.5));
	CScalar cp = CUtils::Cos(a_Pitch * static_cast<CScalar>(0.5));
	CScalar sp = CUtils::Sin(a_Pitch * static_cast<CScalar>(0.5));
	CScalar cr = CUtils::Cos(a_Roll * static_cast<CScalar>(0.5));
	CScalar sr = CUtils::Sin(a_Roll * static_cast<CScalar>(0.5));

	m_Values[0] = cr * cp * cy + sr * sp * sy;
	m_Values[1] = sr * cp * cy - cr * sp * sy;
	m_Values[2] = cr * sp * cy + sr * cp * sy;
	m_Values[3] = cr * cp * sy - sr * sp * cy;
}

void Cinkes::CQuaternion::GetEuler(CScalar& a_Yaw, CScalar& a_Pitch, CScalar& a_Roll)
{
	//I wasn't sure about the naming in here, but there's more detail in the documentation

	// roll (x-axis rotation)
	CScalar sinr_cosp = static_cast<CScalar>(2) * (m_Values[3] * m_Values[0] + m_Values[1] * m_Values[2]);
	CScalar cosr_cosp = static_cast<CScalar>(1) - static_cast<CScalar>(2) * (m_Values[0] * m_Values[0] + m_Values[1] * m_Values[1]);
	a_Roll = CUtils::Atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	CScalar sinp = 2 * (m_Values[3] * m_Values[1] - m_Values[2] * m_Values[0]);
	if (std::abs(sinp) >= 1)
		a_Pitch = std::copysign(M_PI / 2, sinp); // use 90 degrees if out of range
	else
		a_Pitch = std::asin(sinp);

	// yaw (z-axis rotation)
	CScalar siny_cosp = 2 * (m_Values[3] * m_Values[2] + m_Values[0] * m_Values[1]);
	CScalar cosy_cosp = 1 - 2 * (m_Values[1] * m_Values[1] + m_Values[2] * m_Values[2]);
	a_Pitch = CUtils::Atan2(siny_cosp, cosy_cosp);

}

void Cinkes::CQuaternion::operator+=(const CQuaternion& a_Rhs)
{
	m_Values[0] += a_Rhs.m_Values[0];
	m_Values[1] += a_Rhs.m_Values[1];
	m_Values[2] += a_Rhs.m_Values[2];
	m_Values[3] += a_Rhs.m_Values[3];
}

void Cinkes::CQuaternion::operator-=(const CQuaternion& a_Rhs)
{
	m_Values[0] -= a_Rhs.m_Values[0];
	m_Values[1] -= a_Rhs.m_Values[1];
	m_Values[2] -= a_Rhs.m_Values[2];
	m_Values[3] -= a_Rhs.m_Values[3];
}

void Cinkes::CQuaternion::operator*=(const CQuaternion& a_Rhs)
{
	CQuaternion other = a_Rhs;
	m_Values[3] = getW() * other.getW() - getX() * other.getX() - getY() * other.getY() - getZ() * other.getZ();
	m_Values[0] = getW() * other.getX() + getX() * other.getW() + getY() * other.getZ() - getZ() * other.getY();
	m_Values[1] = getW() * other.getY() - getX() * other.getY() + getY() * other.getW() + getZ() * other.getX();
	m_Values[2] = getW() * other.getZ() + getX() * other.getY() - getY() * other.getX() + getZ() * other.getW();
}

void Cinkes::CQuaternion::operator*=(CScalar a_Rhs)
{
	m_Values[0] *= a_Rhs;
	m_Values[1] *= a_Rhs;
	m_Values[2] *= a_Rhs;
	m_Values[3] *= a_Rhs;
}

Cinkes::CQuaternion Cinkes::CQuaternion::operator+(const CQuaternion& a_Rhs)
{
	CQuaternion returnValue;
	returnValue[0] = m_Values[0] + a_Rhs.m_Values[0];
	returnValue[1] = m_Values[1] + a_Rhs.m_Values[1];
	returnValue[2] = m_Values[2] + a_Rhs.m_Values[2];
	returnValue[3] = m_Values[3] + a_Rhs.m_Values[3];

	return returnValue;
}

Cinkes::CQuaternion Cinkes::CQuaternion::operator-(const CQuaternion& a_Rhs)
{
	CQuaternion returnValue;
	returnValue[0] = m_Values[0] - a_Rhs.m_Values[0];
	returnValue[1] = m_Values[1] - a_Rhs.m_Values[1];
	returnValue[2] = m_Values[2] - a_Rhs.m_Values[2];
	returnValue[3] = m_Values[3] - a_Rhs.m_Values[3];

	return returnValue;
}

Cinkes::CQuaternion Cinkes::CQuaternion::operator*(const CQuaternion& a_Rhs)
{
	CQuaternion other = a_Rhs;
	CQuaternion returnQuat;
	returnQuat[3] = getW() * other.getW() - getX() * other.getX() - getY() * other.getY() - getZ() * other.getZ();
	returnQuat[0] = getW() * other.getX() + getX() * other.getW() + getY() * other.getZ() - getZ() * other.getY();
	returnQuat[1] = getW() * other.getY() - getX() * other.getY() + getY() * other.getW() + getZ() * other.getX();
	returnQuat[2] = getW() * other.getZ() + getX() * other.getY() - getY() * other.getX() + getZ() * other.getW();
}

Cinkes::CQuaternion Cinkes::CQuaternion::operator*(const CScalar& a_Rhs)
{
	CQuaternion returnValue;
	returnValue[0] = m_Values[0] * a_Rhs;
	returnValue[1] = m_Values[1] * a_Rhs;
	returnValue[2] = m_Values[2] * a_Rhs;
	returnValue[3] = m_Values[3] * a_Rhs;

	return returnValue;
}

Cinkes::CQuaternion Cinkes::CQuaternion::operator/(const CScalar& a_Rhs)
{
	CQuaternion returnValue;
	returnValue[0] = m_Values[0] / a_Rhs;
	returnValue[1] = m_Values[1] / a_Rhs;
	returnValue[2] = m_Values[2] / a_Rhs;
	returnValue[3] = m_Values[3] / a_Rhs;

	return returnValue;
}

Cinkes::CQuaternion Cinkes::CQuaternion::operator-()
{
	CQuaternion returnValue;
	returnValue[0] = -m_Values[0];
	returnValue[1] = -m_Values[1];
	returnValue[2] = -m_Values[2];
	returnValue[3] = -m_Values[3];

	return returnValue;
}

CScalar& Cinkes::CQuaternion::operator[](int a_Rhs)
{
	return m_Values[a_Rhs];
}

CScalar Cinkes::CQuaternion::Dot(const CQuaternion& a_Rhs)
{
}

CScalar Cinkes::CQuaternion::Length2()
{
}

CScalar Cinkes::CQuaternion::Length()
{
}

void Cinkes::CQuaternion::Normalize()
{
}

CScalar Cinkes::CQuaternion::GetAngleBetween(const CQuaternion& a_Rhs)
{
}

CScalar Cinkes::CQuaternion::GetAngle()
{
}

Cinkes::CVector3 Cinkes::CQuaternion::GetAxis()
{
}

Cinkes::CQuaternion Cinkes::CQuaternion::GetInverse()
{
}

Cinkes::CQuaternion Cinkes::CQuaternion::Slerp(const CQuaternion& a_Other, CScalar a_T)
{
}

const Cinkes::CQuaternion Cinkes::CQuaternion::GetIdentity()
{
}
