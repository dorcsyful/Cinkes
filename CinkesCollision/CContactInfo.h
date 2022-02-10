#pragma once
#include <memory>
#include "../CinkesMath/CVector3.h"
#include <utility>
#include <vector>

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
		std::shared_ptr<CCollisionObject> m_First;
		std::shared_ptr<CCollisionObject> m_Second;
		CVector3 m_Normal;
		CScalar m_PenetrationDepth{};
		ECONTACT_TYPE m_Type = ECONTACT_TYPE::CONTACT_EDGE_EDGE;
		std::vector<CVector3> m_ContactPoints;
		CScalar m_Friction{};
		CScalar m_Restitution{};
		CScalar m_DesiredVelocity;
	};
}

