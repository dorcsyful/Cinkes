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
		CTransform(const CMat3x3& a_Basis, const CVector3& a_Origin);
		CTransform(const CTransform& a_Rhs);
		//}

		//Subgroup: Operators { 
		void operator*=(const CTransform& a_Rhs);
		CTransform operator*(const CTransform& a_Rhs);
		CTransform& operator=(const CTransform& a_Rhs);
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
		CQuaternion getQuaternion();
		void setBasis(const CMat3x3& a_Rhs);
		void setOrigin(const CVector3& a_Rhs);
		void setIdentity();
		static CTransform getIdentity();
		CTransform Inverse();
		//}

	private:
		//Subgroup: : Private members {
		CMat3x3 m_Basis;
		CVector3 m_Origin;
		//}
	};

}
