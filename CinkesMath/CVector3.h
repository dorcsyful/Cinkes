#pragma once
#include "CScalar.h"

namespace Cinkes {

	class CQuaternion;

	/**
	 * @ingroup CVector3
	 * @brief Class for a vector with 3 elements
	 * @{
	 */
	class CVector3
	{
	public:

		/**
		 * @ingroup Constructors
		 * @{
		 */
		CVector3();
		CVector3(CScalar a_X, CScalar a_Y, CScalar a_Z);
		CVector3(const CVector3& a_Vector);

		/** @} */
		/**
		 * @ingroup Other
		 * Getters and Setters
		 * @{
		 */
		CScalar getX();
		CScalar getY();
		CScalar getZ();

		void setX(CScalar a_New);
		void setY(CScalar a_New);
		void setZ(CScalar a_New);
		/** @} */

		/**
		 * @ingroup Operators
		 * @{
		 */
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
		CVector3 operator*(const CVector3& a_Rhs);
		CVector3 operator/(const CVector3& a_Rhs);

		CVector3 operator+(CScalar a_Rhs);
		CVector3 operator-(CScalar a_Rhs);
		CVector3 operator*(CScalar a_Rhs);
		CVector3 operator/(CScalar a_Rhs);

		CScalar& operator[](int a_Rhs);
		CScalar operator[](int a_Rhs) const;

		bool operator==(const CVector3& a_Rhs) const;
		bool operator!=(const CVector3& a_Rhs) const;

		/** @}*/

		/**
		 * @ingroup Other
		 * @{
		 */
		/**
		 * @brief Squared length of the vector
		 * !
		    Calculating the square root is an expensive operation. This function is useful for example when
		    checking if a vector is normalized (since \f$ 1^2 == 1 \f$
		 */
		CScalar Length2();
		/**
		 * @brief Gets the length of the vector
		 * !
		      The equation is 5
				\f$\sqrt{v0^2+v1^2+v2^2}\f$.
		 */
		CScalar Length();
		/**
		 * @brief Divides each value by the length, so the magnitude becomes 1.
		 */
		void Normalize();

		/**
		 * @brief Also called scalar product. Calculates the arccosine between the two vectors
		 */
		CScalar Dot(const CVector3& a_Rhs);
		/**
		 * @brief Created specifically for calculating the inverse inside the CTransform class
		 */
		CVector3 Dot3(const CVector3& a_V0, const CVector3& a_V1, const CVector3& a_V2);
		/**
		 * @brief  Also called vector product. Calculates a vector that is perpendicular to both vectors. NOT commutative!
		 */
		CVector3 Cross(const CVector3& a_Rhs);
		/**
		 * @brief Calculates a position between 2 vectors. a_T is the distance from A to B. (a_T is between 0 and 1)
		 */
		CVector3 Lerp(const CVector3& a_Other, CScalar a_T);
		/** @}*/
	private:

		CScalar m_Values[3];
	};
	/** @} */
}

