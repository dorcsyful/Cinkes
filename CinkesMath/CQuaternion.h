#pragma once
#include "CVector3.h"

namespace Cinkes
{

	//Group: CMath
	/* ClassDescription: a 1x4 matrix used for 3D rotations
	 
	 */
	class CQuaternion
	{
	public:

		//Subgroup: Constructors {
		CQuaternion();
		CQuaternion(CScalar a_X, CScalar a_Y, CScalar a_Z, CScalar a_W);
		CQuaternion(const CQuaternion& a_Other);
		CQuaternion(CVector3 a_Axis, CScalar a_Angle);
		CQuaternion(CScalar a_Yaw, CScalar a_Pitch, CScalar a_Roll);
		//}
		//Subgroup: Other {
		CScalar getX() const;
		CScalar getY() const;
		CScalar getZ() const;
		CScalar getW() const;

		void setX(CScalar a_New);
		void setY(CScalar a_New);
		void setZ(CScalar a_New);
		void setW(CScalar a_New);

		/*
		 MemberDescription: 
		 Axis angle is one of three possible ways to represent rotations.
		 a_Axis A unit vector
		 a_Angle An angle of revolution around that axis
		 */
		void SetFromAngleAxis(CVector3 a_Axis, CScalar a_Angle);
		/*
		 MemberDescription: SetFromEuler
		 Euler angles is one of the three possible ways to represent rotations
		 a_Yaw Rotation around y axis
		 a_Pitch rotation around z axis
		 a_Roll rotation around x axis
		 */
		void SetFromEuler(CScalar a_Yaw, CScalar a_Pitch, CScalar a_Roll);

		void GetEuler(CScalar& a_Yaw, CScalar& a_Pitch, CScalar& a_Roll);
		//}
		//Subgroup: Operators {
		bool operator==(const CQuaternion& a_Rhs);
		bool operator!=(const CQuaternion& a_Rhs);
		void operator=(const CQuaternion& a_Rhs);

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
		CScalar& operator[](int a_Rhs);
		//}
		//Subgroup: Other

		 /*
		  MemberDescription:
		  Also called scalar product. Calculates the cosine between the two quaternions
		  */
		CScalar Dot(const CQuaternion& a_Rhs);
		/*
		 MemberDescription
		 Squared length of the quaternion
			Calculating the square root is an expensive operation. This function is useful for example when
			checking if a vector is normalized (since \f$ 1^2 == 1 \f$
		 */
		CScalar Length2();
		/*
		MemberDescription
		 Gets the length of the quaternion
			  The equation is 5
				\f$\sqrt{q0^2+q1^2+q2^2+q3^2}\f$.
		 */
		CScalar Length();
		/*
		 MemberDescription:
		 Divides each value by the length, so the magnitude becomes 1.
		 */
		void Normalize();
		/*
		 MemberDescription:
		 Calculates the dot product and calls the arccosine function on it to get the angle
		 */
		CScalar GetAngleBetween(const CQuaternion& a_Rhs);
		CScalar GetAngle();
		CVector3 GetAxis();

		CQuaternion GetInverse();
		CQuaternion Slerp(const CQuaternion& a_Other, CScalar a_T);
		/*
		 MemberDescription:
		 The identity for a quaternion is {0, 0, 0, 1}
		 */
		static CQuaternion GetIdentity();
		//}
	private:
		//Subgroup: Private Members {
		CScalar m_Values[4];
		//}
	};
}
