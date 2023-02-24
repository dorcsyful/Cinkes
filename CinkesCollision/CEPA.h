#pragma once
#include <memory>
#include <utility>
#include <vector>
#include "../CinkesMath/CVector3.h"

namespace Cinkes
{
	class CEPAVisualization;
	class CCollisionObject;
	struct CInternalContactInfo;
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

		//Subgroup: Operators {
		CEPA& operator=(CEPA&& a_Rhs) noexcept = delete;
		CEPA& operator=(const CEPA& a_Rhs) noexcept = delete;

		void Run(CInternalContactInfo* a_Contact, CSimplex& a_Simplex);
		void Algorithm(CInternalContactInfo* a_Contact, const CSimplex& a_Simplex);

		std::pair<std::vector<CFaceData>, size_t> GetFaceNormals(const std::vector<CVector3>& a_Polytope, const std::vector<size_t>& a_Faces);
		void AddUniqueEdge(std::vector<std::pair<size_t, size_t>>& a_Edges, const std::vector<size_t>& a_Faces, size_t a_A, size_t a_B);

	};
}
