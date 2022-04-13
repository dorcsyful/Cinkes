#pragma once
#include <cassert>
#include <memory>
#include "../CinkesMath/CVector3.h"
#include <vector>

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



	class CCollisionObject;

	struct CBroadContactInfo
	{
		std::vector<std::shared_ptr<CCollisionObject>> m_Objects;
	};

	struct CContactInfo
	{
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
		ECONTACT_TYPE m_Type = ECONTACT_TYPE::CONTACT_EDGE_EDGE;
		std::vector<CVector3> m_ContactPoints;
		CScalar m_Friction{};
		CScalar m_Restitution{};
		CScalar m_DesiredVelocity{};
		CVector3 m_ContactVelocity;
		CMat3x3 m_ContactToWorld;
		float m_DeltaVelocity{};
		CVector3 m_RelativeContactPosition[2];
	};
}

