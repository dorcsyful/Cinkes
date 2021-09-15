#pragma once
#include "CMat3x3.h"

namespace Cinkes
{
	/**
	 * @ingroup CTransform
	 * @brief Contains rotation and position of an object. Normally a transform also represents scale but it is not needed in a physics engine.
	 * @{
	 */
	class CTransform
	{
	public:
		/**
		 * @ingroup Constructors
		 * @{
		 */
		CTransform();
		CTransform(const CMat3x3& a_Basis, const CVector3& a_Origin);
		CTransform(const CTransform& a_Rhs);
		/** @}*/

		/**
		 * @ingroup Operators
		 * @{
		 */
		void operator*=(const CTransform& a_Rhs);
		CTransform operator*(const CTransform& a_Rhs);
		CTransform& operator=(const CTransform& a_Rhs);
		bool operator==(const CTransform& a_Rhs);
		bool operator!=(const CTransform& a_Rhs);
		CVector3 operator()(const CVector3& a_Rhs);

		/** @}*/

		/**
		 * @ingroup Other
		 * @brief All other functions
		 * !
			Getters have a const and non-const version so it works when they are passed as const references
			@{
		 */
		void Multiply(const CTransform& a_Lhs, const CTransform& a_Rhs);
		CMat3x3 getBasis();
		CMat3x3 getBasis() const;
		CVector3 getOrigin();
		CVector3 getOrigin() const;
		CQuaternion getQuaternion();
		void setBasis(const CMat3x3& a_Rhs);
		void setOrigin(const CVector3& a_Rhs);
		void setIdentity();
		static CTransform getIdentity();
		CTransform Inverse();

		/** @} */
	private:
		CMat3x3 m_Basis;
		CVector3 m_Origin;
	};
	/** @} */
}
