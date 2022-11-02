#pragma once
#include <memory>
#include <vector>

#include "CMat3x3.h"

namespace Cinkes
{
	class CRigidBody;
	class CCollisionObject;
	struct CInternalContactInfo;

	class CCollisionResolver
	{
	public:
		CCollisionResolver() = default;
		~CCollisionResolver() = default;
		CCollisionResolver(CCollisionResolver&& a_Rhs) = delete;
		CCollisionResolver(const CCollisionResolver& a_Rhs) = delete;

		CCollisionResolver& operator=(CCollisionResolver&& a_Rhs) noexcept = delete;
		CCollisionResolver& operator=(const CCollisionResolver& a_Rhs) = delete;

		bool Resolve(std::vector<std::shared_ptr<CInternalContactInfo>>& a_Info, CScalar a_T) const;

	private:

	};
}

