#pragma once
#include "CContactInfo.h"

namespace Cinkes
{
	struct CSorter
	{
		CVector3 m_Vertex;
		CCollisionObject* m_CollisionObject;
		CScalar m_Dot;

		CSorter(CVector3 a_Vertex, CCollisionObject* a_CollisionObject, const CVector3& a_Direction) : m_Vertex(a_Vertex)
		{
			m_CollisionObject = a_CollisionObject;
			m_Dot = m_Vertex.Dot(a_Direction);
		}
	};


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
		void GetPoints(CContactInfo& a_Contact);



	private:
		static bool IsLarger(const CSorter& a_First, const CSorter& a_Second) { return a_First.m_Dot < a_Second.m_Dot; }
		CVector3 ClosestToEdge(const CVector3& a_Vertex1, const CVector3& a_OtherVertex1, const CVector3& a_OtherVertex2);
		void ContactFaceFace(const std::vector<CVector3>& a_FaceA, const std::vector<CVector3>& a_FaceB, CContactInfo& a_Contact);
		void ContactFaceEdge(const std::vector<CVector3>& a_Face, const std::vector<CVector3>& a_Edge, CContactInfo& a_Contact);
		void ContactFaceVertex(const std::vector<CVector3>& a_Face, const CVector3& a_Vertex, CContactInfo& a_Contact);
		void ContactEdgeEdge(std::vector<CVector3>& a_EdgeA, std::vector<CVector3>& a_EdgeB, CContactInfo& a_Contact);
		void ContactEdgeVertex(const std::vector<CVector3>& a_Edge, const CVector3& a_Vertex, CContactInfo& a_Contact);

	};
}
