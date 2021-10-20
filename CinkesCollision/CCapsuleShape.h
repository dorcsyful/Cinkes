#pragma once
#include "../CinkesMath/CScalar.h"
#include "CCollisionShape.h"

namespace Cinkes
{

    class CCapsuleShape : public CCollisionShape
    {
    public:
		//Subgroup: Constructors {
		CCapsuleShape(CScalar a_Radius, CScalar a_Height) : m_Radius(a_Radius), m_Height(a_Height) {}
		CCapsuleShape() : m_Radius(0), m_Height(0) {}
		virtual ~CCapsuleShape() = default;
		CCapsuleShape(const CCapsuleShape& a_Rhs) { m_Height = a_Rhs.m_Height; m_Radius = a_Rhs.m_Radius; }
		CCapsuleShape(CCapsuleShape&& a_Rhs) noexcept { m_Height = a_Rhs.m_Height; m_Radius = a_Rhs.m_Radius; }
		//}

		//Subgroup: Operators {
		virtual CCapsuleShape& operator=(CCapsuleShape&& a_Rhs) noexcept { m_Height = a_Rhs.m_Height; m_Radius = a_Rhs.m_Radius; return *this; }
		CCapsuleShape& operator=(const CCapsuleShape& a_Rhs) noexcept { m_Height = a_Rhs.m_Height; m_Radius = a_Rhs.m_Radius; return *this; }
		//}

		//Subgroup: Getters and Setters {
		CScalar getRadius() { return m_Radius; }
		CScalar getHeight() { return m_Height; }
		CScalar getRadius() const { return m_Radius; }
		CScalar getHeight() const { return m_Height; }

		void setRadius(CScalar a_New) { m_Radius = a_New; }
		void setHeight(CScalar a_New) { m_Height = a_New; }
		//}

		//Subgroup: Other {
		CVector3 Support(const CVector3& a_V) override;
		//}

    private:
		CScalar m_Radius;
		//does not include the radius of the spheres at each end
		CScalar m_Height;
		ESHAPE_TYPE m_Type = ESHAPE_TYPE::SHAPE_CAPSULE;

    };

}