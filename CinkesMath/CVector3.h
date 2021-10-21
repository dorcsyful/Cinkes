#pragma once
#include "CScalar.h"

namespace Cinkes {

	class CQuaternion;

	//Group: CMath
	/* ClassDescription: a vector containing 3 elements, or a 1x3 matrix
	*/
	class CVector3
	{
	public:

		//Subgroup: Constructors {
		CVector3();
		CVector3(CScalar a_X, CScalar a_Y, CScalar a_Z);
		CVector3(const CVector3& a_Vector);
		//}
		//Subgroup: Other {
		CScalar getX();
		CScalar getY();
		CScalar getZ();

		void setX(CScalar a_New);
		void setY(CScalar a_New);
		void setZ(CScalar a_New);
		//}

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
		//}

		//Subgroup: Other {
		/* MemberDescription: Squared length of the vector
			Calculating the square root is an expensive operation. This function is useful for example when
			checking if a vector is normalized (since 1^2 == 1)
		 */
		CScalar Length2();

		/*MemberDescription: Gets the length of the vector
			  The equation is 5
				\f$\sqrt{v0^2+v1^2+v2^2}\f$.
		 */
		CScalar Length();

		/* MemberDescription:
		  Divides each value by the length, so the magnitude becomes 1.
		 */
		void Normalize();

		/*MemberDescription: Also called scalar product. Calculates the arccosine between the two vectors
		*/
		CScalar Dot(const CVector3& a_Rhs);
		CScalar Dot(const CVector3& a_Rhs) const;

		/*MemberDescription:
		 Created specifically for calculating the inverse inside the CTransform class
		 */
		CVector3 Dot3(const CVector3& a_V0, const CVector3& a_V1, const CVector3& a_V2);

		/*MemberDescription:
		 Also called vector product. Calculates a vector that is perpendicular to both vectors. NOT commutative!
		 */
		CVector3 Cross(const CVector3& a_Rhs);

		/*MemberDescription:
		 Calculates a position between 2 vectors. a_T is the distance from A to B. (a_T is between 0 and 1)
		 */
		CVector3 Lerp(const CVector3& a_Other, CScalar a_T);


	private:
		//Subgroup: Class members {
		CScalar m_Values[3];
		//}
	};
	/** @} */
}

