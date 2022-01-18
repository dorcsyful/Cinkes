#pragma once
#include "CContactInfo.h"

namespace Cinkes
{
	class CSimplex;

	class CContactPointCalculator
	{
	public:
		CContactPointCalculator() = default;
		~CContactPointCalculator() = default;

		CContactPointCalculator(const CContactPointCalculator& a_Rhs) = delete;
		CContactPointCalculator(CContactPointCalculator&& a_Rhs) noexcept = delete;
		//}

		//Subgroup: Operators {
		CContactPointCalculator& operator=(CContactPointCalculator&& a_Rhs) noexcept = delete;
		CContactPointCalculator& operator=(const CContactPointCalculator& a_Rhs) noexcept = delete;

		void RunForAllContacts(std::vector<CContactInfo>& a_All);
		void GetPoints(CContactInfo* a_Contact);



	private:
		CVector3 GetBaryCentric(const CVector3& a_Distance, const std::vector<CVector3>& a_Triangle);

	};
}
