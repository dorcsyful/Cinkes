#pragma once
#include <memory>
#include "../CinkesMath/CVector3.h"

namespace Cinkes
{
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
	};
}

