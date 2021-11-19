#pragma once
#include <memory>

namespace Cinkes
{
	class CCollisionObject;
	struct CContactInfo
	{
		std::shared_ptr<CCollisionObject> m_First;
		std::shared_ptr<CCollisionObject> m_Second;
		bool m_PassedNarrowphase = true;
		std::vector<std::shared_ptr<CCollisionObject>> m_Other;
	};
}

