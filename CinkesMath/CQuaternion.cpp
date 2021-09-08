#include "CQuaternion.h"

#include <cassert>

#include "CUtils.h"

Cinkes::CQuaternion::CQuaternion()
{
	m_Values[0] = 0;
	m_Values[1] = 0;
	m_Values[2] = 0;
	m_Values[3] = 1;
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
	SetFromEuler(a_Yaw, a_Pitch, a_Roll);
}

CScalar Cinkes::CQuaternion::getX() const
{
	return m_Values[0];
}

CScalar Cinkes::CQuaternion::getY() const
{
	return m_Values[1];
}

CScalar Cinkes::CQuaternion::getZ() const
{
	return m_Values[2];
}

CScalar Cinkes::CQuaternion::getW() const
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
	a_Yaw = CUtils::Atan2(siny_cosp, cosy_cosp);

}

bool Cinkes::CQuaternion::operator==(const CQuaternion& a_Rhs)
{
	bool x = getX() == a_Rhs.getX();
	bool y = getY() == a_Rhs.getY();
	bool z = getZ() == a_Rhs.getZ();
	bool w = getW() == a_Rhs.getW();

	return x && y && z && w;
}

bool Cinkes::CQuaternion::operator!=(const CQuaternion& a_Rhs)
{
	bool x = getX() != a_Rhs.getX();
	bool y = getY() != a_Rhs.getY();
	bool z = getZ() != a_Rhs.getZ();
	bool w = getW() != a_Rhs.getW();

	return x && y && z && w;
}

void Cinkes::CQuaternion::operator=(const CQuaternion& a_Rhs)
{
	m_Values[0] = a_Rhs.getX();
	m_Values[1] = a_Rhs.getY();
	m_Values[2] = a_Rhs.getZ();
	m_Values[3] = a_Rhs.getW();
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

	CQuaternion temp((*this));
	m_Values[0] = temp.getW() * a_Rhs.getX() + temp.getX() * a_Rhs.getW() + temp.getY() * a_Rhs.getZ() - temp.getZ() * a_Rhs.getY();
	m_Values[1] = temp.getW() * a_Rhs.getY() - temp.getX() * a_Rhs.getZ() + temp.getY() * a_Rhs.getW() + temp.getZ() * a_Rhs.getX();
	m_Values[2] = temp.getW() * a_Rhs.getZ() + temp.getX() * a_Rhs.getY() - temp.getY() * a_Rhs.getX() + temp.getZ() * a_Rhs.getW();
	m_Values[3] = temp.getW() * a_Rhs.getW() - temp.getX() * a_Rhs.getX() - temp.getY() * a_Rhs.getY() - temp.getZ() * a_Rhs.getZ();

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

	returnQuat[0] = getW() * other.getX() + getX() * other.getW() + getY() * other.getZ() - getZ() * other.getY();
	returnQuat[1] = getW() * other.getY() - getX() * other.getZ() + getY() * other.getW() + getZ() * other.getX();
	returnQuat[2] = getW() * other.getZ() + getX() * other.getY() - getY() * other.getX() + getZ() * other.getW();
	returnQuat[3] = getW() * other.getW() - getX() * other.getX() - getY() * other.getY() - getZ() * other.getZ();
	return returnQuat;
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
	return m_Values[0] * a_Rhs.getX() + m_Values[1] * a_Rhs.getY() + m_Values[2] * a_Rhs.getZ() + m_Values[3] * a_Rhs.getW();
}

CScalar Cinkes::CQuaternion::Length2()
{
	return m_Values[0] * m_Values[0] + m_Values[1] * m_Values[1] + m_Values[2] * m_Values[2] + m_Values[3] * m_Values[3];
}

CScalar Cinkes::CQuaternion::Length()
{
	return CUtils::Sqrt(Length2());
}

void Cinkes::CQuaternion::Normalize()
{
	CScalar length = Length();
	m_Values[0] = m_Values[0] / length;
	m_Values[1] = m_Values[1] / length;
	m_Values[2] = m_Values[2] / length;
	m_Values[3] = m_Values[3] / length;
}

CScalar Cinkes::CQuaternion::GetAngleBetween(const CQuaternion& a_Rhs)
{
	CQuaternion temp = a_Rhs;

	if(Length2() != CScalar(1))
	{
		Normalize();
	}
	if(temp.Length2() != CScalar(1))
	{
		temp.Normalize();
	}
	CScalar dot = Dot(temp) * Dot(temp);
	CScalar angle = CUtils::Acos((2*(dot)) - 1);
	if(angle > CScalar(M_PI))
	{
		angle = angle - M_PI * CScalar(2);
	}
	return angle;
}

CScalar Cinkes::CQuaternion::GetAngle()
{
	//assert(Length2() != CScalar(1));
	return static_cast<CScalar>(2) * CUtils::Acos((*this)[3]);
}

Cinkes::CVector3 Cinkes::CQuaternion::GetAxis()
{
	CVector3 axis;
	CQuaternion temp = *this;
	CScalar divisonBy = CUtils::Sqrt(static_cast<CScalar>(1) - temp[3] * temp[3]);
	if (temp[3] > static_cast<CScalar>(1))
	{
		temp.Normalize();
	}
	if (divisonBy < static_cast<CScalar>(0.000001)) {
		axis.setX(this->getX());
		axis.setY(this->getY());
		axis.setZ(this->getZ());
	} else
	{
		axis.setX(this->getX() / divisonBy);
		axis.setY(this->getY() / divisonBy);
		axis.setZ(this->getZ() / divisonBy);
	}

	return axis;
}

Cinkes::CQuaternion Cinkes::CQuaternion::GetInverse()
{
	CQuaternion quat;
	quat.setW(this->getW());
	quat.setZ(-this->getZ());
	quat.setY(-this->getY());
	quat.setZ(-this->getX());
	return quat / Length2();
}

Cinkes::CQuaternion Cinkes::CQuaternion::Slerp(const CQuaternion& a_Other, CScalar a_T)
{
	CQuaternion end = a_Other;
	CScalar cosHalfTheta = (*this)[3] * a_Other.getW() + (*this)[0] * a_Other.getX() + (*this)[1] * a_Other.getY() + (*this)[2] * a_Other.getZ();
	if (cosHalfTheta < 0) {
		end[3] = -end[3];
		end[0] = -end[0];
		end[1] = -end[1];
		cosHalfTheta = -cosHalfTheta;
	}
	if(CUtils::Abs(cosHalfTheta) >= static_cast<CScalar>(1.0))
	{
		end.setW(this->getW());
		end.setX(this->getX());
		end.setY(this->getY());
		end.setZ(this->getZ());

		return end;
	}
	CScalar halfTheta = CUtils::Acos(cosHalfTheta);
	CScalar sinHalfTheta = CUtils::Sin(halfTheta);
	if (CUtils::Abs(sinHalfTheta) < static_cast<float>(0.001))
	{
		end[3] = ((*this)[3] * static_cast<CScalar>(0.5) + a_Other.getW() * static_cast<CScalar>(0.5));
		end[0] = ((*this)[0] * static_cast<CScalar>(0.5) + a_Other.getX() * static_cast<CScalar>(0.5));
		end[1] = ((*this)[1] * static_cast<CScalar>(0.5) + a_Other.getY() * static_cast<CScalar>(0.5));
		end[2] = ((*this)[2] * static_cast<CScalar>(0.5) + a_Other.getZ() * static_cast<CScalar>(0.5));
		return end;
	}

	CScalar ratioA = CUtils::Sin((1 - a_T) * halfTheta) / sinHalfTheta;
	CScalar ratioB = CUtils::Sin(a_T * halfTheta) / sinHalfTheta;
	//calculate Quaternion.
	end[3] = ((*this)[3] * ratioA + a_Other.getW() * ratioB);
	end[0] = ((*this)[0] * ratioA + a_Other.getX() * ratioB);
	end[1] = ((*this)[1] * ratioA + a_Other.getY() * ratioB);
	end[2] = ((*this)[2] * ratioA + a_Other.getZ() * ratioB);
	return end;
}

Cinkes::CQuaternion Cinkes::CQuaternion::GetIdentity()
{
	return CQuaternion(static_cast<CScalar>(0), static_cast<CScalar>(0), static_cast<CScalar>(0), static_cast<CScalar>(1));
}
