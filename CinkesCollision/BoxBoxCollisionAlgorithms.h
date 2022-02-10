#pragma once
#include "CScalar.h"

namespace Cinkes
{
	class CVector3;
	class CCollisionObject;
	struct CContactInfo;

	class BoxBoxCollisionAlgorithms
	{
	public:
		BoxBoxCollisionAlgorithms() = default;
		~BoxBoxCollisionAlgorithms() = default;

		BoxBoxCollisionAlgorithms(const BoxBoxCollisionAlgorithms& a_Rhs) = delete;
		BoxBoxCollisionAlgorithms(BoxBoxCollisionAlgorithms&& a_Rhs) noexcept = delete;
		//}

		//Subgroup: Operators {
		BoxBoxCollisionAlgorithms& operator=(BoxBoxCollisionAlgorithms&& a_Rhs) noexcept = delete;
		BoxBoxCollisionAlgorithms& operator=(const BoxBoxCollisionAlgorithms& a_Rhs) noexcept = delete;

		bool CalculateCurrent(CContactInfo* a_ContactInfo);

	private:
		 bool TryAxis(const CCollisionObject& a_One, const CCollisionObject& a_Two, CVector3 a_Axis, const CVector3& a_ToCentre, unsigned a_Index,
						// These values may be updated
						CScalar& a_SmallestPenetration,
						unsigned& a_SmallestCase);
		 CScalar PenetrationOnAxis(const CCollisionObject& a_One, const CCollisionObject& a_Two, const CVector3& a_Axis, const CVector3& a_ToCentre);
		 CScalar TransformToAxis(const CCollisionObject& a_Object, const CVector3& a_Axis);
		 bool OverlapOnAxis(const CCollisionObject& a_One, const CCollisionObject& a_Two, const CVector3& a_Axis, const CVector3& a_ToCentre);
		 unsigned BoxAndBox(const CCollisionObject& a_One, const CCollisionObject& a_Two, CContactInfo* a_Data);
		 void FillPointFaceBoxBox(const CCollisionObject& a_One, const CCollisionObject& a_Two, const CVector3& a_ToCentre, CContactInfo* a_Data,
									unsigned a_Best, CScalar a_Pentration);
		 CVector3 ContactPoint(const CVector3& a_POne,const CVector3& a_DOne,CScalar a_OneSize,const CVector3& a_PTwo,const CVector3& a_DTwo,
								 CScalar a_TwoSize,
								 bool a_UseOne);
	};
}

