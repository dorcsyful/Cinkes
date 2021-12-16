#pragma once
#include "../CinkesMath/CScalar.h"
#include "CCollisionShape.h"

namespace Cinkes
{

	class CCylinder :public CCollisionShape
	{
		//Subgroup: Constructors {
		CCylinder() : m_Radius(0), m_Height(0) {}
		CCylinder(CScalar a_Radius, CScalar a_Height) : m_Radius(a_Radius), m_Height(a_Height) {}
		~CCylinder() override = default;
		CCylinder(const CCylinder& a_Rhs) : CCollisionShape(a_Rhs)
		{ m_Height = a_Rhs.m_Height; m_Radius = a_Rhs.m_Radius; }
		CCylinder(CCylinder&& a_Rhs) noexcept { m_Height = a_Rhs.m_Height; m_Radius = a_Rhs.m_Radius; }
		//}

		//Subgroup: Operators {
		virtual CCylinder& operator=(CCylinder&& a_Rhs) noexcept;
		virtual CCylinder& operator=(const CCylinder& a_Rhs) noexcept;
		//}

		//Subgroup: Other {
		CVector3 Support(const CVector3& a_V, const CVector3& a_Position) override;
		void CreateAABB(CVector3& a_Min, CVector3& a_Max) override;
		std::vector<CVector3> SupportPointsForContact(const CVector3& a_Direction, const CVector3& a_Position) override;
		//}
	private:
		CScalar m_Radius;
		CScalar m_Height;
		ESHAPE_TYPE m_Type = ESHAPE_TYPE::SHAPE_CYLINDER;
	};

}