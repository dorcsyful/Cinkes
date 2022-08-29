#pragma once
#include <cassert>
#include <memory>
#include "../CinkesMath/CVector3.h"
#include <vector>
#include "CSimplex.h"
#include "CMat3x3.h"

namespace Cinkes
{
	enum class ECONTACT_TYPE
	{
		CONTACT_NO_CONTACT,
		CONTACT_FACE_FACE,
		CONTACT_FACE_EDGE,
		CONTACT_FACE_VERTEX,
		CONTACT_EDGE_VERTEX,
		CONTACT_EDGE_EDGE
	};

	struct CTriangle {
	public:
		CVector3 m_Values[3];
		CVector3 m_Normal;
		CTriangle() = default;
		CTriangle(CVector3 a_X, CVector3 a_Y, CVector3 a_Z, CVector3 a_Normal = CVector3(0, 1, 0)) {
			m_Values[0] = a_X;
			m_Values[1] = a_Y;
			m_Values[2] = a_Z;
			m_Normal = a_Normal;
		}
		CVector3 operator[](int a_Rhs) {
			return m_Values[a_Rhs];
		}
		CVector3 operator[](int a_Rhs) const {
			return m_Values[a_Rhs];
		}
	};


	class CCollisionObject;

	struct CBroadContactInfo
	{
		std::vector<std::shared_ptr<CCollisionObject>> m_Objects;
	};

	struct CContactInfo
	{
		CContactInfo(void) = default;
		CCollisionObject* operator[](const unsigned int a_Rhs)
		{
			assert(a_Rhs == 0 || a_Rhs == 1);
			if (a_Rhs == 0) { return m_First.get(); }
			return m_Second.get();
		}

		CCollisionObject* operator[](const unsigned int a_Rhs) const
		{
			assert(a_Rhs == 0 || a_Rhs == 1);
			if (a_Rhs == 0) { return m_First.get(); }
			return m_Second.get();
		}

		std::shared_ptr<CCollisionObject> m_First;
		std::shared_ptr<CCollisionObject> m_Second;
		CVector3 m_Normal;
		CScalar m_PenetrationDepth{};
		ECONTACT_TYPE m_Type = ECONTACT_TYPE::CONTACT_NO_CONTACT;
		std::vector<CVector3> m_ContactPoints;
		CTriangle m_Triangle[3]; //[0] -> main triangle [1] -> polytopeA [2] -> polytopeB
		CScalar m_Friction{};
		CScalar m_Restitution{};
		CScalar m_DesiredVelocity{};
		CVector3 m_ContactVelocity;
		CMat3x3 m_ContactToWorld;
		float m_DeltaVelocity{};
		std::vector<CVector3> m_RelativeContactPosition[2];
		CSimplex m_Simplex;
	};
}

