#pragma once
#include "../CinkesMath/CScalar.h"
#include "../CinkesMath/CUtils.h"
#include "CCollisionShape.h"

namespace Cinkes
{

    class CConeShape : public CCollisionShape
    {
    public:
        //Subgroup: Constructors {
        CConeShape() : m_Radius(0), m_Height(0), m_SinOfAngle(0) {}
        CConeShape(CScalar a_Radius) : m_Radius(a_Radius), m_Height(0), m_SinOfAngle(0) {}
        CConeShape(CScalar a_Radius, CScalar a_Height);
    	~CConeShape() override = default;
        CConeShape(const CConeShape& a_Rhs);
        CConeShape(CConeShape&& a_Rhs) noexcept;
        //}

        //Subgroup: Operators {
    	CConeShape& operator=(CConeShape&& a_Rhs) noexcept;
    	CConeShape& operator=(const CConeShape& a_Rhs) noexcept;
        //}

        //Subgroup: Getters and setters {
        CScalar getRadius() { return m_Radius; }
        CScalar getHeight() { return m_Height; }
        CScalar getSin() { return m_SinOfAngle; }
        CScalar getAngle() { return CUtils::Asin(m_SinOfAngle); }

        CScalar getRadius() const { return m_Radius; }
        CScalar getHeight() const { return m_Height; }
        CScalar getSin() const { return m_SinOfAngle; }
        CScalar getAngle() const { return CUtils::Asin(m_SinOfAngle); }

        void setRadius(CScalar a_New);
        void setHeight(CScalar a_New);
        //}

        //Subgroup: Other {
        CVector3 Support(const CVector3& a_V, const CVector3& a_Position) override;
        void CreateAABB(CVector3& a_Min, CVector3& a_Max) override;
        std::vector<CVector3> SupportPointsForContact(const CVector3& a_Direction, const CVector3& a_Position) override;
        //}

    private:
        CScalar m_Radius;
        CScalar m_Height;
        //This could be calculated from the radius and the height but we store it for easy access

        CScalar m_SinOfAngle;
        ESHAPE_TYPE m_Type = ESHAPE_TYPE::SHAPE_CONE;

    };

}