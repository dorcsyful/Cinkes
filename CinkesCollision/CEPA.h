#pragma once
#include <memory>
#include <utility>
#include <vector>
#include "../CinkesMath/CVector3.h"

namespace Cinkes
{
	class CCollisionObject;
	struct CContactInfo;
	class CSimplex;

	struct CFaceData
	{
		CFaceData(CVector3 a_Normal, CScalar a_Distance) : m_Normal(std::move(a_Normal)), m_Distance(a_Distance) {}
		CVector3 m_Normal;
		CScalar m_Distance;
	};


	class CEPA
	{
	public:
		CEPA() = default;
		~CEPA() = default;

		CEPA(const CEPA& a_Rhs) = delete;
		CEPA(CEPA&& a_Rhs) noexcept = delete;
		//}

		//Subgroup: Operators {
		CEPA& operator=(CEPA&& a_Rhs) noexcept = delete;
		CEPA& operator=(const CEPA& a_Rhs) noexcept = delete;

		void Run(std::shared_ptr<CContactInfo> a_Contact, CSimplex& a_Simplex);
		void Algorithm(std::shared_ptr<CContactInfo> a_Contact, const CSimplex& a_Simplex);
		void BlowUp(CSimplex& a_Simplex, const std::shared_ptr<CContactInfo>& a_Contact);
		CVector3 CSOSupport(const CContactInfo* a_Contact, const CVector3& a_Dir);
		CVector3 SmallestAxis(const CVector3& a_Vector3);
		std::pair<std::vector<CFaceData>, size_t> GetFaceNormals(const std::vector<CVector3>& a_Polytope, const std::vector<size_t>& a_Faces);
		void AddUniqueEdge(std::vector<std::pair<size_t, size_t>>& a_Edges, const std::vector<size_t>& a_Faces, size_t a_A, size_t a_B);
	};
}
