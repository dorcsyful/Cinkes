#pragma once
#include "CMat3x3.h"

namespace Cinkes
{
	//Group: CMath
	/* ClassDescription: A transform is normally a 4x4 matrix, but since we do not need scaling, the class only stores the rotation and the position
	 */
	class CTransform
	{
	public:
		//Subgroup: Constructors { 
		CTransform();
		~CTransform() = default;
		CTransform(const CMat3x3& a_Basis, const CVector3& a_Origin);
		CTransform(const CTransform& a_Rhs);
		CTransform(CTransform&& a_Rhs) noexcept;
		CTransform& operator=(CTransform&& a_Rhs) noexcept;
		CTransform& operator=(const CTransform& a_Rhs);
		//}


		//Subgroup: Operators { 
		void operator*=(const CTransform& a_Rhs);
		CTransform operator*(const CTransform& a_Rhs);
		CVector3 operator*(const CVector3& a_Rhs);
		bool operator==(const CTransform& a_Rhs);
		bool operator!=(const CTransform& a_Rhs);
		CVector3 operator()(const CVector3& a_Rhs);
		//}

		//Subgroup: Other { 
		void Multiply(const CTransform& a_Lhs, const CTransform& a_Rhs);
		CMat3x3 getBasis();
		CMat3x3 getBasis() const;
		CVector3 getOrigin();
		CVector3 getOrigin() const;
		CScalar getPerValue(unsigned a_Value);
		CScalar getPerValue(unsigned a_Value) const;
		CVector3 getAxisVector(unsigned a_Value);
		CVector3 getAxisVector(unsigned a_Value) const;
		CQuaternion getQuaternion();
		void setBasis(const CMat3x3& a_Rhs);
		void setOrigin(const CVector3& a_Rhs);
		void setIdentity();
		static CTransform getIdentity();
		CTransform Inverse();

		CVector3 getAxisVector(int i) const
		{
			return CVector3(getPerValue(i), getPerValue(i + 4), getPerValue(i + 8));
		}
		CVector3 getAxisVector(int i)
		{
			return CVector3(getPerValue(i), getPerValue(i + 4), getPerValue(i + 8));
		}
		//}

	private:
		//Subgroup: : Private members {
		CMat3x3 m_Basis;
		CVector3 m_Origin;
		//}
	};

}
