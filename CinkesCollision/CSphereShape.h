#pragma once
#include "CCollisionShape.h"
#include "../CinkesMath/CVector3.h"
namespace Cinkes {

    class CSphereShape : CCollisionShape
    {
    public:
		//Subgroup: Constructors {
		CSphereShape() : m_Radius(0) {}
    	~CSphereShape() override = default;
		CSphereShape(const CSphereShape& a_Rhs) noexcept { m_Radius = a_Rhs.m_Radius; }
		CSphereShape(CSphereShape&& a_Rhs) noexcept { m_Radius = a_Rhs.m_Radius; }
		//}

		//Subgroup: Operators {
		CSphereShape& operator=(CSphereShape&& a_Rhs) { m_Radius = a_Rhs.m_Radius; }
		CSphereShape& operator=(const CSphereShape& a_Rhs) { m_Radius = a_Rhs.m_Radius; }
		//}
		//Subgroup: Other {
		CScalar GetRadius() { return m_Radius; }
		void GetRadius(CScalar& a_Radius) { a_Radius = m_Radius; }
		void SetRadius(CScalar a_Radius) { m_Radius = a_Radius; }
		//}

    private:
		CScalar m_Radius;
		Cinkes::ESHAPE_TYPE m_Type = ESHAPE_TYPE::SHAPE_SPHERE;
    };
}

