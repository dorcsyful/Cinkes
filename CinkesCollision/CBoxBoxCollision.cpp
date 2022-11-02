#include <algorithm>
#include "CBoxBoxCollision.h"
#include "CCollisionObject.h"
#include "CBoxShape.h"

//Order of indices:
// 0 -> (-1, -1, -1)
// 1 -> (-1, -1,  1)
// 2 -> (-1,  1,  1)
// 3 -> (-1,  1, -1)
// 4 -> ( 1,  1,  1)
// 5 -> ( 1,  1, -1)
// 6 -> ( 1, -1,  1)
// 7 -> ( 1, -1, -1)
Cinkes::CBoxBoxCollision::CBoxBoxCollision(): m_Info(nullptr)
{
	m_Sides[0] = CVector3(0, 1, 0);
	m_Sides[1] = CVector3(0, -1, 0);
	m_Sides[2] = CVector3(1, 0, 0);
	m_Sides[3] = CVector3(-1, 0, 0);
	m_Sides[4] = CVector3(0, 0, 1);
	m_Sides[5] = CVector3(0, 0, -1);

	m_ReferenceBox = std::vector<CVector3>(8);
	m_IncidentBox = std::vector<CVector3>(8);
}

bool Cinkes::CBoxBoxCollision::Run(CInternalContactInfo* a_Info)
{
	m_Info = a_Info;
	FindReference();
	FindIncident();
	FindSidePlanes();
	CreateIncidentLines();

	if (m_ReferenceFace.vertices.size() > 1 && m_IncidentFace.vertices.size() > 1) {
		Clip();
	} 
	//FilterPoints();

	m_ReferenceFace.isValid = false;
	m_IncidentFace.isValid = false;
	m_Info = nullptr;
    return true;
}

void Cinkes::CBoxBoxCollision::FindReference()
{

    CVector3 local = m_Info->m_Normal;
	CVector3 position = m_Info->m_First->GetTransform().getOrigin();
	CVector3 dimensions = static_cast<CBoxShape*>(m_Info->m_First->GetCollisionShape().get())->GetDimensions();
	m_ReferenceBox[0] = m_Info->m_First->GetTransform().getBasis() * 
		CVector3(position.getX() - dimensions.getX(), position.getY() - dimensions.getY(), position.getZ() - dimensions.getZ());
	m_ReferenceBox[1] = m_Info->m_First->GetTransform().getBasis() * 
		CVector3(position.getX() - dimensions.getX(), position.getY() - dimensions.getY(), position.getZ() + dimensions.getZ());
	m_ReferenceBox[2] = m_Info->m_First->GetTransform().getBasis() * 
		CVector3(position.getX() - dimensions.getX(), position.getY() + dimensions.getY(), position.getZ() + dimensions.getZ());
	m_ReferenceBox[3] = m_Info->m_First->GetTransform().getBasis() * 
		CVector3(position.getX() - dimensions.getX(), position.getY() + dimensions.getY(), position.getZ() - dimensions.getZ());
	m_ReferenceBox[4] = m_Info->m_First->GetTransform().getBasis() * 
		CVector3(position.getX() + dimensions.getX(), position.getY() + dimensions.getY(), position.getZ() + dimensions.getZ());
	m_ReferenceBox[5] = m_Info->m_First->GetTransform().getBasis() * 
		CVector3(position.getX() + dimensions.getX(), position.getY() + dimensions.getY(), position.getZ() - dimensions.getZ());
	m_ReferenceBox[6] = m_Info->m_First->GetTransform().getBasis() * 
		CVector3(position.getX() + dimensions.getX(), position.getY() - dimensions.getY(), position.getZ() + dimensions.getZ());
	m_ReferenceBox[7] = m_Info->m_First->GetTransform().getBasis() * 
		CVector3(position.getX() + dimensions.getX(), position.getY() - dimensions.getY(), position.getZ() - dimensions.getZ());
	CScalar dots[8];

	for (int i = 0; i < 8; i++)
	{
		dots[i] = local.Dot(m_ReferenceBox[i]);
	}
	CScalar max = *std::max_element(dots, dots + 7);
	for (int i = 0; i < 8; i++)
	{
		CScalar base = max - dots[i];
		if (base < static_cast<CScalar>(0.001) && base > -static_cast<CScalar>(0.001))
		{
			m_ReferenceFace.vertices.push_back(i);
		}
	}
	m_ReferenceFace.isValid = true;
	m_ReferenceFace.normal = m_Info->m_Normal;
}

void Cinkes::CBoxBoxCollision::FindIncident()
{

	CVector3 position = m_Info->m_Second->GetTransform().getOrigin();
	CVector3 dimensions = static_cast<CBoxShape*>(m_Info->m_Second->GetCollisionShape().get())->GetDimensions();
	m_IncidentBox[0] = m_Info->m_Second->GetTransform().getBasis() * 
		CVector3(position.getX() - dimensions.getX(), position.getY() - dimensions.getY(), position.getZ() - dimensions.getZ());
	m_IncidentBox[1] = m_Info->m_Second->GetTransform().getBasis() * 
		CVector3(position.getX() - dimensions.getX(), position.getY() - dimensions.getY(), position.getZ() + dimensions.getZ());
	m_IncidentBox[2] = m_Info->m_Second->GetTransform().getBasis() * 
		CVector3(position.getX() - dimensions.getX(), position.getY() + dimensions.getY(), position.getZ() + dimensions.getZ());
	m_IncidentBox[3] = m_Info->m_Second->GetTransform().getBasis() * 
		CVector3(position.getX() - dimensions.getX(), position.getY() + dimensions.getY(), position.getZ() - dimensions.getZ());
	m_IncidentBox[4] = m_Info->m_Second->GetTransform().getBasis() * 
		CVector3(position.getX() + dimensions.getX(), position.getY() + dimensions.getY(), position.getZ() + dimensions.getZ());
	m_IncidentBox[5] = m_Info->m_Second->GetTransform().getBasis() * 
		CVector3(position.getX() + dimensions.getX(), position.getY() + dimensions.getY(), position.getZ() - dimensions.getZ());
	m_IncidentBox[6] = m_Info->m_Second->GetTransform().getBasis() * 
		CVector3(position.getX() + dimensions.getX(), position.getY() - dimensions.getY(), position.getZ() + dimensions.getZ());
	m_IncidentBox[7] = m_Info->m_Second->GetTransform().getBasis() * 
		CVector3(position.getX() + dimensions.getX(), position.getY() - dimensions.getY(), position.getZ() - dimensions.getZ());
	float dots[8];

	for (int i = 0; i < 8; i++)
	{
		dots[i] = (m_Info->m_Normal).Dot(m_IncidentBox[i]);
	}
	CScalar max = *std::min_element(dots, dots + 7);
	for (int i = 0; i < 8; i++)
	{
		CScalar base = max - dots[i];
		if (base < static_cast<CScalar>(0.001) && base > -static_cast<CScalar>(0.001))
		{
			m_IncidentFace.vertices.push_back(i);
		}
	}
	m_IncidentFace.isValid = true;
	m_IncidentFace.normal = m_Info->m_Second->GetTransform().getBasis() * (m_Info->m_Normal * -1);
}

void Cinkes::CBoxBoxCollision::FindSidePlanes()
{
	CVector3 top = m_Info->m_First->GetTransform().getOrigin() + 
		(static_cast<CBoxShape*>(m_Info->m_First->GetCollisionShape().get())->GetDimensions() * m_ReferenceFace.normal);
	std::vector<int>& ref = m_ReferenceFace.vertices;

	std::vector<std::pair<int, int>> pairs;
	for(size_t i = 0; i < ref.size(); i++)
	{
		for(size_t j = 0; j < ref.size();j++)
		{
			if(i != j)
			{
				pairs.emplace_back(ref[i], ref[j]);
			}
		}
	}
	
	for (size_t i = 0; i < pairs.size(); i++) {
		CVector3 middle = (m_ReferenceBox[pairs[i].first] + m_ReferenceBox[pairs[i].second]) / 2;
			CVector3 normal = middle - top;
			CScalar length = normal.Length2();
		if (length >= CEPSILON) {
			pairs.erase(std::find(pairs.begin(), pairs.end(), 
						std::pair<int, int>(pairs[i].second, pairs[i].first)));

			normal.Normalize();
			m_Planes.emplace_back();
			m_Planes[m_Planes.size() - 1].normal = normal;
			m_Planes[m_Planes.size() - 1].point = middle;
		}
	}
	//CPlane face = CPlane(m_ReferenceFace.normal, top);
	//m_Planes.push_back(face);
	//face = CPlane(m_IncidentFace.normal, top);
	//m_Planes.push_back(face);
}

void Cinkes::CBoxBoxCollision::Clip()
{
	CScalar D1, D2;
	CVector3 v1, v2;
	std::vector<CVector3> input;
	for(auto& verts : m_IncidentFace.vertices)
	{
		input.push_back(m_IncidentBox[verts]);
	}
	std::vector<CVector3> new_face;
	for (auto& plane : m_Planes)
	{
		v1 = input[0];
		D1 = plane.DistanceToPoint(v1);
		for (size_t j = 1; j <= input.size(); j++) {
			size_t next = j % input.size();
			v2 = input[next];
			D2 = plane.DistanceToPoint(v2);
			if (D1 <= 0.0f && D2 <= 0.0f || D1 > 0.0f && D2 > -CEPSILON && D2 < CEPSILON) {
				new_face.push_back(v2);
			}
			else if (D1 > 0.0f && D2 < CEPSILON) {
				new_face.push_back(plane.Intersection(v1, v2));
				new_face.push_back(v2);
			}
			else if (D1 < CEPSILON && D2 > 0.0f) {
				new_face.push_back(plane.Intersection(v1, v2));
			}
			v1 = v2;
			D1 = D2;
		}
		if (new_face.empty()) break;
		input = new_face;
		new_face.clear();
	}
	m_Info->m_ContactPoints = input;
}

void Cinkes::CBoxBoxCollision::CreateIncidentLines()
{
	CVector3 top = 
		static_cast<CBoxShape*>(m_Info->m_First->GetCollisionShape().get())->GetDimensions() * m_IncidentFace.normal;
	int first = 0;

	for (size_t i = 0; i < m_IncidentFace.vertices.size(); i++) {
		auto it = std::find(m_LinesReference.begin(), m_LinesReference.end(),
			std::pair<int, int>(m_IncidentFace.vertices[first], m_IncidentFace.vertices[i]));
		if (it != m_LinesReference.end()) {
			m_IncidentFace.vertices[first + 1] = (* it).second;
			first++;
			if (first > 3) { break; }
		}
	}


	top.Normalize();
}