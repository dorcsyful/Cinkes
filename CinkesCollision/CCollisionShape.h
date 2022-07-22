#pragma once
#include <vector>

#include "CMat3x3.h"
#include "../CinkesMath/CVector3.h"

namespace Cinkes
{
	class CTransform;

	enum class ESHAPE_TYPE
	{
		SHAPE_NO_TYPE,
		SHAPE_SPHERE,
		SHAPE_BOX,
		SHAPE_CONVEX_HULL,
		SHAPE_CONCAVE,
		SHAPE_COMPOUND,
		SHAPE_COMPOUND_PARTIAL,
		SHAPE_CAPSULE,
		SHAPE_CONE,
		SHAPE_CYLINDER
	};


	class CCollisionShape
	{
	public:
		//Subgroup: Constructors {
		CCollisionShape() = default;
		virtual ~CCollisionShape() = default;
		CCollisionShape(const CCollisionShape& a_Rhs) = default;
		CCollisionShape(CCollisionShape&& a_Rhs) = default;
		//}

		//Subgroup: Operators {
		virtual CCollisionShape& operator=(CCollisionShape&& a_Rhs) noexcept = default;
		virtual CCollisionShape& operator=(const CCollisionShape& a_Rhs) noexcept = default;
		//}

		//Subgroup: Other {
		ESHAPE_TYPE GetType() const { return m_Type; }
		virtual CVector3 Support(const CVector3& a_V) = 0;
		virtual void CreateAABB(CVector3& a_Min, CVector3& a_Max) = 0;
		virtual std::vector<CVector3> SupportPointsForContact(const CVector3& a_Direction, const CTransform& a_Position) = 0;
		virtual CMat3x3 CalculateInertiaTensor(CScalar a_Mass) = 0;

		//}

	protected:
		ESHAPE_TYPE m_Type = ESHAPE_TYPE::SHAPE_NO_TYPE;
	};

}

