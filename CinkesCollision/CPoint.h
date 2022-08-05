#pragma once
#include <CVector3.h>
namespace Cinkes {
	class CPoint
	{
	public:
		CPoint() { coords = CVector3(0, 0, 0); }
		CPoint(const CVector3& a_Vector) { coords = a_Vector; }
		CPoint(CScalar a_X, CScalar a_Y, CScalar a_Z) { coords = CVector3(a_X, a_Y, a_Z); }
		~CPoint() = default;
		CPoint(const CPoint& a_Rhs) = default;
		CPoint(CPoint&& a_Rhs) noexcept : coords(a_Rhs.coords) {}

		CPoint& operator=(CPoint&& a_Rhs) noexcept { coords = a_Rhs.coords; return *this; }
		CPoint& operator=(const CPoint& a_Rhs) noexcept { coords = a_Rhs.coords; return *this; }
		CPoint operator+(CPoint v) const {
			return CPoint(coords[0] + v.coords[0], coords[1] + v.coords[1],
				coords[2] + v.coords[2]);
		}
		CPoint operator-(CPoint v) const {
			return CPoint(coords[0] - v.coords[0], coords[1] - v.coords[1],
				coords[2] - v.coords[2]);
		}
		CPoint operator*(double_t f) const { return CPoint(coords[0] * f, coords[1] * f, coords[2] * f); }
		CScalar operator[](int a_Rhs) const { return coords[a_Rhs]; }
		CScalar& operator[](int a_Rhs) { return coords[a_Rhs]; }

		CScalar Length() { return coords.Length(); }
		CScalar Length2() { return coords.Length2(); }
		void Normalize() { coords.Normalize(); }
		static CVector3 Normalize(const CVector3& a_Rhs) {
			CVector3 temp = a_Rhs;
			temp.Normalize();
			return temp;
		}
		static CScalar Length(CVector3& a_In) { return a_In.Length(); }
		static CScalar Length2(CVector3& a_In) { return a_In.Length(); }

		CVector3 coords;
	};
}

