#pragma once
#include "CVector3.h"

namespace Cinkes
{

	class CMat3x3
	{
	public:
		CMat3x3();
		CMat3x3(const CVector3& a_Row1, const CVector3& a_Row2, const CVector3& a_Row3);
		CMat3x3(CScalar a_00, CScalar a_01, CScalar a_02,
				CScalar a_10, CScalar a_11, CScalar a_12,
				CScalar a_20, CScalar a_21, CScalar a_22);
		CMat3x3(const CMat3x3& a_Copy);

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

		CVector3 operator[](int a_Row) const;
		CVector3& operator[](int a_Row);
		CVector3 getRow(int a_Row);
		CVector3 getColumn(int a_Column);

		CMat3x3 Transpose();
		CMat3x3 GetInverse();
		static CMat3x3 GetIdentity();
		CScalar Determinant();
		CScalar DeterminantOfMinor(CScalar a_00, CScalar a_01, CScalar a_10, CScalar a_11);
		CQuaternion ToQuaternion();
		void GetEuler(CScalar& a_Yaw, CScalar& a_Pitch, CScalar& a_Roll);
		CMat3x3 Abs();

	private:
		CVector3 m_Rows[3];
	};
}

