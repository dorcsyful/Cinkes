#pragma once
#include "CVector3.h"

namespace Cinkes
{

	class CQuaternion
	{
	public:
		CQuaternion();
		CQuaternion(CScalar a_X, CScalar a_Y, CScalar a_Z, CScalar a_W);
		CQuaternion(const CQuaternion& a_Other);
		CQuaternion(const CVector3& a_axis, CScalar a_angle);
		CQuaternion(CScalar a_Yaw, CScalar a_Pitch, CScalar a_Roll);

		CScalar getX();
		CScalar getY();
		CScalar getZ();
		CScalar getW();

		CScalar setX();
		CScalar setY();
		CScalar setZ();
		CScalar setW();

		void SetFromAngleAxis(const CVector3& a_Axis, CScalar a_Angle);
		void SetFromEuler(CScalar a_Yaw, CScalar a_Pitch, CScalar a_Roll);

		void GetEuler(CScalar& a_Yaw, CScalar& a_Pitch, CScalar& a_Roll);

		void operator+=(const CQuaternion& a_Rhs);
		void operator-=(const CQuaternion& a_Rhs);
		void operator*=(const CQuaternion& a_Rhs);
		void operator*=(CScalar a_Rhs);

		CQuaternion operator+(const CQuaternion& a_Rhs);
		CQuaternion operator-(const CQuaternion& a_Rhs);
		CQuaternion operator*(const CQuaternion& a_Rhs);
		CQuaternion operator*(const CScalar& a_Rhs);
		CQuaternion operator/(const CScalar& a_Rhs);
		CQuaternion operator-();

		CScalar Dot(const CQuaternion& a_Rhs);
		CScalar Length2();
		CScalar Length();
		void Normalize();

		CScalar GetAngleBetween(const CQuaternion& a_Rhs);
		CScalar GetAngle();
		CVector3 GetAxis();

		CQuaternion GetInverse();
		CQuaternion Slerp(const CQuaternion& a_Other, CScalar a_T);
		static const CQuaternion GetIdentity();
		
	};

}