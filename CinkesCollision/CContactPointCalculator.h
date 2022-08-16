#pragma once
#include "CContactInfo.h"
#include "CVector3.h"
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
		CVector3 GetBaryCentric(const CVector3& a_Point, const CTriangle& a_Triangle);
		CVector3 ProjectToTriangle(CScalar a_Distance, const CTriangle& a_Triangle);
		CScalar Clip(CScalar a_Original, CScalar a_Lower, CScalar a_Upper); //Because what the fuck std
	};
}
