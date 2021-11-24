#pragma once
#include <memory>

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
	};
}

