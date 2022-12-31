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
	if (a_Info->m_Normal.getX() >= static_cast<CScalar>(0.57735))
		a_Info->m_Tangents[0] = CVector3(a_Info->m_Normal.getY(), -a_Info->m_Normal.getX(), 0.0f);
	else
		a_Info->m_Tangents[1] = CVector3(0.0f, -a_Info->m_Normal.getZ(), -a_Info->m_Normal.getY());

	a_Info->m_Tangents[0].Normalize();
	a_Info->m_Tangents[1] = a_Info->m_Normal.Cross(a_Info->m_Tangents[0]);

	m_Info = a_Info;
	FindReference();
	FindIncident();
	FindRefSidePlanes();
	FindIncSidePlanes();
	CreateIncidentLines();

	if (m_ReferenceFace.vertices.size() > 1 && m_IncidentFace.vertices.size() > 1) {
		Clip(m_ReferenceFace,m_ReferenceBox,m_RefSidePlanes,0);
		Clip(m_IncidentFace,m_IncidentBox,m_IncSidePlanes,1);
	} 
	m_ReferenceFace = CFace();
	m_IncidentFace = CFace();
	m_Info = nullptr;
	m_RefSidePlanes.clear();
	m_IncSidePlanes.clear();
	m_Lines.clear();
	m_LinesReference.clear();
    return true;
}

void Cinkes::CBoxBoxCollision::FindReference()
{
	//TODO: generalize this to accept vertices instead
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
	CScalar dots[8]{};

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
	CVector3 crossed;
	if (m_ReferenceFace.vertices.size() >= 3) {
		CVector3 a = m_ReferenceBox[m_ReferenceFace.vertices[0]] - m_ReferenceBox[m_ReferenceFace.vertices[1]];
		CVector3 b = m_ReferenceBox[m_ReferenceFace.vertices[2]] - m_ReferenceBox[m_ReferenceFace.vertices[0]];
		a.Normalize();
		b.Normalize();
		crossed = CVector3::Cross(a, b);
		if((m_ReferenceBox[m_ReferenceFace.vertices[0]] - m_Info->m_First->GetTransform().getOrigin()).Dot(crossed) < 0)
		{
			crossed *= -1.f;
		}
	}
	else if(m_ReferenceFace.vertices.size() == 2)
	{
		CVector3 lerp = m_ReferenceBox[m_ReferenceFace.vertices[0]].Lerp(m_ReferenceBox[m_ReferenceFace.vertices[1]], static_cast<CScalar>(0.5));
		crossed =  m_Info->m_First->GetTransform().getOrigin() - lerp;
	}
	else if(m_ReferenceFace.vertices.size() == 1)
	{
		crossed = m_ReferenceBox[m_ReferenceFace.vertices[0]] - m_Info->m_First->GetTransform().getOrigin();
	}
	crossed.Normalize();
	m_ReferenceFace.normal = crossed;
	m_ReferenceFace.isValid = true;
	
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
	CVector3 crossed;
	if (m_IncidentFace.vertices.size() >= 3) {
		CVector3 a = m_IncidentBox[m_IncidentFace.vertices[0]] - m_IncidentBox[m_IncidentFace.vertices[1]];
		CVector3 b = m_IncidentBox[m_IncidentFace.vertices[2]] - m_IncidentBox[m_IncidentFace.vertices[0]];
		a.Normalize();
		b.Normalize();
		crossed = CVector3::Cross(a, b);
		if ((m_IncidentBox[m_IncidentFace.vertices[0]] - m_Info->m_Second->GetTransform().getOrigin()).Dot(crossed) < 0)
		{
			crossed *= -1.f;
		}
	}
	else if (m_IncidentFace.vertices.size() == 2)
	{
		CVector3 lerp = m_IncidentBox[m_IncidentFace.vertices[0]].Lerp(m_IncidentBox[m_IncidentFace.vertices[1]], static_cast<CScalar>(0.5));
		crossed = lerp - m_Info->m_Second->GetTransform().getOrigin();
	}
	else if (m_IncidentFace.vertices.size() == 1)
	{
		crossed = m_IncidentBox[m_IncidentFace.vertices[0]] - m_Info->m_Second->GetTransform().getOrigin();
	}
	crossed.Normalize();
	m_IncidentFace.normal = crossed;
	m_IncidentFace.isValid = true;
}

void Cinkes::CBoxBoxCollision::FindRefSidePlanes()
{
	//TODO: optimize
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
			m_RefSidePlanes.emplace_back();
			m_RefSidePlanes[m_RefSidePlanes.size() - 1].normal = normal;
			m_RefSidePlanes[m_RefSidePlanes.size() - 1].point = middle;
		}
	}
}

void Cinkes::CBoxBoxCollision::FindIncSidePlanes()
{
	CVector3 top = m_Info->m_Second->GetTransform().getOrigin() +
		(static_cast<CBoxShape*>(m_Info->m_Second->GetCollisionShape().get())->GetDimensions() * m_IncidentFace.normal);
	std::vector<int>& inc = m_IncidentFace.vertices;

	std::vector<std::pair<int, int>> pairs;
	for (size_t i = 0; i < inc.size(); i++)
	{
		for (size_t j = 0; j < inc.size(); j++)
		{
			if (i != j)
			{
				pairs.emplace_back(inc[i], inc[j]);
			}
		}
	}

	for (size_t i = 0; i < pairs.size(); i++) {
		CVector3 middle = (m_IncidentBox[pairs[i].first] + m_IncidentBox[pairs[i].second]) / 2;
		CVector3 normal = middle - top;
		CScalar length = normal.Length2();
		if (length >= CEPSILON) {
			pairs.erase(std::find(pairs.begin(), pairs.end(),
				std::pair<int, int>(pairs[i].second, pairs[i].first)));

			normal.Normalize();
			m_IncSidePlanes.emplace_back();
			m_IncSidePlanes[m_IncSidePlanes.size() - 1].normal = normal;
			m_IncSidePlanes[m_IncSidePlanes.size() - 1].point = middle;
		}
	}
}

void Cinkes::CBoxBoxCollision::Clip(CFace& a_Face, std::vector<CVector3>& a_Box, std::vector<CPlane>& a_Planes, int a_Index)
{
	CScalar D1, D2;
	CVector3 v1, v2;
	std::vector<CVector3> input;
	for(auto& verts : a_Face.vertices)
	{
		input.push_back(a_Box[verts]);
	}
	std::vector<CVector3> new_face;
	for (auto& plane : a_Planes)
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
		if (new_face.empty()) { break; }
		input = new_face;
		new_face.clear();
	}
	m_Info->m_RelativeContactPosition[a_Index] = input;
}

void Cinkes::CBoxBoxCollision::CreateIncidentLines()
{
	//TODO: optimize
	CVector3 top = 
		static_cast<CBoxShape*>(m_Info->m_First->GetCollisionShape().get())->GetDimensions() * m_IncidentFace.normal;
	int first = 0;

	for (int& vertice : m_IncidentFace.vertices)
	{
		auto it = std::find(m_LinesReference.begin(), m_LinesReference.end(),
			std::pair<int, int>(m_IncidentFace.vertices[first], vertice));
		if (it != m_LinesReference.end()) {
			m_IncidentFace.vertices[first + 1] = (* it).second;
			first++;
			if (first > 3) { break; }
		}
	}


	top.Normalize();
}