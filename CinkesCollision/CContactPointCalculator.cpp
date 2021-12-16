#include "CContactPointCalculator.h"

#include <algorithm>

#include "CCollisionObject.h"
#include "CCollisionShape.h"

void Cinkes::CContactPointCalculator::RunForAllContacts(std::vector<CContactInfo>& a_All)
{
	for (auto& element : a_All)
	{
		GetPoints(element);
	}
}

void Cinkes::CContactPointCalculator::GetPoints(CContactInfo& a_Contact)
{
	std::vector<CVector3> verticesA = a_Contact.m_First->GetCollisionShape()->SupportPointsForContact(a_Contact.m_Normal,a_Contact.m_First->GetTransform().getOrigin());
	std::vector<CVector3> verticesB = a_Contact.m_Second->GetCollisionShape()->SupportPointsForContact(a_Contact.m_Normal * -1, a_Contact.m_Second->GetTransform().getOrigin());


}

Cinkes::CVector3 Cinkes::CContactPointCalculator::ClosestToEdge(const CVector3& a_Vertex1, const CVector3& a_OtherVertex1, const CVector3& a_OtherVertex2)
{
	CVector3 ab = a_OtherVertex1 - a_OtherVertex2;
	CVector3 ap = a_Vertex1 - a_OtherVertex1;
	CScalar dotab = ab.Dot(ab);
	CScalar dotabap = ap.Dot(ab);
	CScalar distance = dotabap - dotab;
	if (distance < CScalar(0)) { distance = 0; }
	else
	{
		if (distance > CScalar(1)) { distance = 1; }
	}
	return a_OtherVertex1 + ab * distance;

}

void Cinkes::CContactPointCalculator::ContactFaceFace(const std::vector<CVector3>& a_FaceA, const std::vector<CVector3>& a_FaceB, CContactInfo& a_Contact)
{

}

void Cinkes::CContactPointCalculator::ContactFaceEdge(const std::vector<CVector3>& a_Face, const std::vector<CVector3>& a_Edge, CContactInfo& a_Contact)
{
}

void Cinkes::CContactPointCalculator::ContactFaceVertex(const std::vector<CVector3>& a_Face, const CVector3& a_Vertex, CContactInfo& a_Contact)
{
}

void Cinkes::CContactPointCalculator::ContactEdgeEdge(std::vector<CVector3>& a_EdgeA, std::vector<CVector3>& a_EdgeB, CContactInfo& a_Contact)
{
	CVector3 direction = a_EdgeA[0] - a_EdgeA[1];

	std::vector<CSorter> sorted;
	sorted.emplace_back(a_EdgeA[0], a_Contact.m_First.get(), direction);
	sorted.emplace_back(a_EdgeA[1], a_Contact.m_First.get(), direction);
	sorted.emplace_back(a_EdgeB[0], a_Contact.m_Second.get(), direction);
	sorted.emplace_back(a_EdgeB[1], a_Contact.m_Second.get(), direction);
	std::sort(sorted.begin(), sorted.end(), IsLarger);

	for(auto& current : sorted)
	{
		if(current.m_CollisionObject == a_Contact.m_First.get())
		{
			a_Contact.m_ContactPoints.push_back(current.m_Vertex);
			a_Contact.m_ContactPoints.push_back(ClosestToEdge(current.m_Vertex, a_EdgeB[0], a_EdgeB[1]));
		} else
		{
			a_Contact.m_ContactPoints.push_back(ClosestToEdge(current.m_Vertex, a_EdgeA[0], a_EdgeA[1]));
			a_Contact.m_ContactPoints.push_back(current.m_Vertex);

		}
	}
}

void Cinkes::CContactPointCalculator::ContactEdgeVertex(const std::vector<CVector3>& a_Edge, const CVector3& a_Vertex, CContactInfo& a_Contact)
{
	a_Contact.m_ContactPoints.push_back(ClosestToEdge(a_Vertex, a_Edge[0], a_Edge[1]));
	a_Contact.m_ContactPoints.push_back(a_Vertex);
}
