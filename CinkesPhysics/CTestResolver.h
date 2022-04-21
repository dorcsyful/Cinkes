#pragma once
#include "CContactInfo.h"
#include "CScalar.h"

namespace Cinkes
{

	class CTestResolver
	{
	public:
		CTestResolver() = default;
		~CTestResolver() = default;
		CTestResolver(CTestResolver&& a_Rhs) = delete;
		CTestResolver(const CTestResolver& a_Rhs) = delete;

		CTestResolver& operator=(CTestResolver&& a_Rhs) noexcept = delete;
		CTestResolver& operator=(const CTestResolver& a_Rhs) = delete;

		bool Resolve(const std::vector<std::shared_ptr<Cinkes::CContactInfo>>& a_Info, CScalar a_T) const;

	};

}