#pragma once
#include "CScalar.h"

namespace Cinkes {

	class CQuaternion;

	class CVector3
	{
	public:

		//Subgroup: Constructors {
		CVector3();
		CVector3(CScalar a_X, CScalar a_Y, CScalar a_Z);
		~CVector3() = default;
		CVector3(const CVector3& a_Vector);
		CVector3(CVector3&& a_Vector) noexcept;
		CVector3& operator=(CVector3&& a_Rhs) noexcept;

		//Subgroup: Other {
		CScalar getX();
		CScalar getX() const;
		CScalar getY();
		CScalar getY() const;
		CScalar getZ();
		CScalar getZ() const;

		void setX(CScalar a_New);
		void setY(CScalar a_New);
		void setZ(CScalar a_New);

		//Subgroup: Operators {
		CVector3& operator=(const CVector3& a_Rhs);
		void operator+=(const CVector3& a_Rhs);
		void operator-=(const CVector3& a_Rhs);
		void operator*=(const CVector3& a_Rhs);
		void operator/=(const CVector3& a_Rhs);
		void operator+=(CScalar a_Rhs);
		void operator-=(CScalar a_Rhs);
		void operator*=(CScalar a_Rhs);
		void operator/=(CScalar a_Rhs);
		const CVector3 operator+(const CVector3& a_Vector3) const;
		CVector3 operator+(const CVector3& a_Rhs);
		CVector3 operator-(const CVector3& a_Rhs);
		CVector3 operator-(const CVector3& a_Rhs) const;
		CVector3 operator*(const CVector3& a_Rhs);
		CVector3 operator/(const CVector3& a_Rhs);
		CVector3 operator+(CScalar a_Rhs) const;
		CVector3 operator+(CScalar a_Rhs);
		CVector3 operator-(CScalar a_Rhs);
		CVector3 operator*(CScalar a_Rhs) const;
		CVector3 operator*(CScalar a_Rhs);
		CVector3 operator/(CScalar a_Rhs);
		CScalar& operator[](int a_Rhs);
		CScalar operator[](int a_Rhs) const;
		bool operator==(const CVector3& a_Rhs) const;
		bool operator!=(const CVector3& a_Rhs) const;
		
		CScalar Length2();
		CScalar Length();
		void Normalize();
		CScalar Dot(const CVector3& a_Rhs);
		CScalar Dot(const CVector3& a_Rhs) const;
		CVector3 Dot3(const CVector3& a_V0, const CVector3& a_V1, const CVector3& a_V2);
		CVector3 Cross(const CVector3& a_Rhs);
		CVector3 Lerp(const CVector3& a_Other, CScalar a_T);

	private:
		CScalar m_Values[3];
	};
}

