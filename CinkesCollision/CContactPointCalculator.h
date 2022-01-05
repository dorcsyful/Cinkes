#pragma once
#include "CContactInfo.h"

namespace Cinkes
{

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
		void SphereSphere(CContactInfo* a_Contact);
		void SphereBox(CContactInfo* a_Contact);
		void BoxBox(CContactInfo* a_Contact);

	};
}
