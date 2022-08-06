#pragma once
#include "CCollisionShape.h"
#include "../CinkesMath/CTransform.h"
#include "../CinkesMath/CVector3.h"
namespace Cinkes {

    class CSphereShape : public CCollisionShape
    {
    public:
		//Subgroup: Constructors {
		CSphereShape() : m_Radius(0) {}
    	~CSphereShape() override = default;
		CSphereShape(const CSphereShape& a_Rhs) noexcept : CCollisionShape(a_Rhs) { m_Radius = a_Rhs.m_Radius; }
		CSphereShape(CSphereShape&& a_Rhs) noexcept { m_Radius = a_Rhs.m_Radius; }
		//}

		//Subgroup: Operators {
		CSphereShape& operator=(CSphereShape&& a_Rhs) noexcept { m_Radius = a_Rhs.m_Radius; return *this; }
		CSphereShape& operator=(const CSphereShape& a_Rhs) { m_Radius = a_Rhs.m_Radius; return *this; }
		//}
		//Subgroup: Other {
		CScalar GetRadius() const { return m_Radius; }
		void GetRadius(CScalar& a_Radius) const { a_Radius = m_Radius; }
		void SetRadius(CScalar a_Radius) { m_Radius = a_Radius; }
		CVector3 Support(const CVector3& a_V) override { return a_V * m_Radius; }
		void CreateAABB(const CMat3x3& a_Rotation, CVector3& a_Min, CVector3& a_Max) override;
		//}

    private:
		CScalar m_Radius;
		Cinkes::ESHAPE_TYPE m_Type = ESHAPE_TYPE::SHAPE_SPHERE;
    };
}

