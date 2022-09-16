#pragma once
#include "CVector3.h"

namespace Cinkes
{
	//Group: CMath
	/*
	 * ClassDescription: A 3x3 matrix, generally used to represent rotations
	 */
	class CMat3x3
	{
	public:
		
		//Subgroup: Constructors {
		CMat3x3();
		CMat3x3(const CVector3& a_Axis, CScalar a_Angle);
		CMat3x3(const CVector3& a_Row1, const CVector3& a_Row2, const CVector3& a_Row3);
		CMat3x3(CScalar a_00, CScalar a_01, CScalar a_02,
				CScalar a_10, CScalar a_11, CScalar a_12,
				CScalar a_20, CScalar a_21, CScalar a_22);
		CMat3x3(const CQuaternion& a_Rotation);
		CMat3x3(const CMat3x3& a_Copy);
		//}
		//Subgroup: Operators
		bool operator==(const CMat3x3& a_Rhs) const;
		bool operator!=(const CMat3x3& a_Rhs) const;
		CMat3x3& operator=(const CMat3x3& a_Rhs);
		CMat3x3 operator+(const CMat3x3& a_Rhs);
		void operator+=(const CMat3x3& a_Rhs);
		CMat3x3 operator+(const CScalar& a_Rhs);
		void operator+=(const CScalar& a_Rhs);
		CMat3x3 operator-(const CScalar& a_Rhs);
		void operator-=(const CScalar& a_Rhs);
		CMat3x3 operator-(const CMat3x3& a_Rhs);
		void operator-=(const CMat3x3& a_Rhs);
		CMat3x3 operator*(const CMat3x3& a_Rhs);
		void operator*=(const CMat3x3& a_Rhs);
		CMat3x3 operator*(const CScalar& a_Rhs);
		void operator*=(const CScalar& a_Rhs);
		CVector3 operator*(const CVector3& a_Rhs);
		CVector3 operator[](unsigned a_Row) const;
		CVector3& operator[](unsigned a_Row);
		//}

		// Subgroup: Other {
		CScalar MultiplicationValues(const CVector3& a_Vector3, int a_Column) const;
		CVector3 getRow(unsigned a_Row);
		CVector3 getRow(unsigned a_Row) const;
		CVector3 getColumn(unsigned a_Column);
		CVector3 getColumn(unsigned a_Column) const;
		void setColumn(unsigned a_Num, const CVector3& a_Column);
		void setFromColumns(const CVector3& a_0, const CVector3& a_1, const CVector3& a_2);
		void setSkewSymmetric(const CVector3& a_Vector);
		/*
		 MemberDescription:
		 Makes columns into rows and vice versa
		 */
		CMat3x3 Transpose();
		CMat3x3 GetInverse();
		CMat3x3 GetInverse() const { return GetInverse(); };
		CVector3 TransformTranspose(const CVector3& a_Vector);
		/*
		 MemberDescription:
		 Static function to get the identity matrix. Do not call on member function!
		 */
		static CMat3x3 GetIdentity();
		CScalar Determinant();
		/*
		 MemberDescription:
		  Gets the determinant of a 2x2 matrix. Used for calculating the inverse
		 */
		CScalar DeterminantOfMinor(CScalar a_00, CScalar a_01, CScalar a_10, CScalar a_11);
		CQuaternion ToQuaternion();
		void GetEuler(CScalar& a_Yaw, CScalar& a_Pitch, CScalar& a_Roll);
		CMat3x3 Abs();
		void SetFromAxisAngle(const CVector3& a_Axis, CScalar a_Angle);
		void SetFromQuaternion(const CQuaternion& a_Quaternion);
		CMat3x3 Scale(const CVector3& a_V);
		//}
	private:
		//Subgroup: Matrix Elements {
		CVector3 m_Rows[3];
		//}
	};
}

