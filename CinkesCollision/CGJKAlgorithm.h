#pragma once

namespace Cinkes
{
	class CVector3;
	class CCollisionObject;

	class CGJKAlgorithm
	{
		CGJKAlgorithm() = default;
		~CGJKAlgorithm() = default;
		CGJKAlgorithm(CGJKAlgorithm& a_Cgjk) = default;
		CGJKAlgorithm(CGJKAlgorithm&& a_Cgjk) = default;
		CGJKAlgorithm& operator=(const CGJKAlgorithm& a_Cgjk) = default;
		CGJKAlgorithm& operator=(CGJKAlgorithm&& a_Cgjk) = default;

		static bool Algorithm(CCollisionObject* a_Object1, CCollisionObject* a_Object2);
		static bool FurthestPoint(CCollisionObject* a_Object, CVector3 a_Direction);
		static bool Support(CCollisionObject* a_Object1, CCollisionObject* a_Object2, CVector3 a_Direction);
	};
}
