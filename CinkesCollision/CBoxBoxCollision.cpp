#pragma once
#include <algorithm>
#include <cmath>
#include "CBoxBoxCollision.h"
#include "CCollisionObject.h"
#include "CBoxShape.h"
Cinkes::CBoxBoxCollision::CBoxBoxCollision()
{
	m_Sides[0] = CVector3(0, 1, 0);
	m_Sides[1] = CVector3(0, -1, 0);
	m_Sides[2] = CVector3(1, 0, 0);
	m_Sides[3] = CVector3(-1, 0, 0);
	m_Sides[4] = CVector3(0, 0, 1);
	m_Sides[5] = CVector3(0, 0, -1);
}
bool Cinkes::CBoxBoxCollision::Run(CContactInfo* a_Info)
{
	m_Info = a_Info;
	FindReference();
	FindIncident();
	FindSidePlanes();

	if (m_ReferenceFace.vertices.size() == 4 && m_IncidentFace.vertices.size() == 4) {
		Clip();
	}
	for (auto& current : m_Points) {
		m_Info->m_ContactPoints.push_back(current);
	}


	m_ReferenceFace.isValid = false;
	m_IncidentFace.isValid = false;
	m_Info = nullptr;
    return true;
}

void Cinkes::CBoxBoxCollision::FindReference()
{

    CVector3 local = m_Info->m_First->GetTransform().getBasis().GetInverse() * m_Info->m_Normal;
	m_LocalNormal = local;
	CVector3 position = m_Info->m_First->GetTransform().getOrigin();
	CVector3 dimensions = static_cast<CBoxShape*>(m_Info->m_First->GetCollisionShape().get())->GetDimensions();
	CVector3 vertices[8];
	vertices[0] = CVector3(position.getX() - dimensions.getX(), position.getY() - dimensions.getY(), position.getZ() - dimensions.getZ());
	vertices[1] = CVector3(position.getX() - dimensions.getX(), position.getY() - dimensions.getY(), position.getZ() + dimensions.getZ());
	vertices[2] = CVector3(position.getX() - dimensions.getX(), position.getY() + dimensions.getY(), position.getZ() + dimensions.getZ());
	vertices[3] = CVector3(position.getX() - dimensions.getX(), position.getY() + dimensions.getY(), position.getZ() - dimensions.getZ());
	vertices[4] = CVector3(position.getX() + dimensions.getX(), position.getY() + dimensions.getY(), position.getZ() + dimensions.getZ());
	vertices[5] = CVector3(position.getX() + dimensions.getX(), position.getY() + dimensions.getY(), position.getZ() - dimensions.getZ());
	vertices[6] = CVector3(position.getX() + dimensions.getX(), position.getY() - dimensions.getY(), position.getZ() + dimensions.getZ());
	vertices[7] = CVector3(position.getX() + dimensions.getX(), position.getY() - dimensions.getY(), position.getZ() - dimensions.getZ());
	float dots[8];

	for (int i = 0; i < 8; i++)
	{
		dots[i] = local.Dot(vertices[i]);
	}
	CScalar max = *std::max_element(dots, dots + 7);
	for (int i = 0; i < 8; i++)
	{
		CScalar base = max - dots[i];
		if (base < static_cast<CScalar>(0.001) && base > -static_cast<CScalar>(0.001))
		{
			m_ReferenceFace.vertices.push_back(vertices[i]);
			m_ReferenceFace.ids.push_back(i);
		}
	}
	m_ReferenceFace.isValid = true;
	m_ReferenceFace.normal = m_Info->m_Normal;
}

void Cinkes::CBoxBoxCollision::FindIncident()
{

	CVector3 local = m_Info->m_Second->GetTransform().getBasis().GetInverse() * m_Info->m_Normal;
	CVector3 position = m_Info->m_Second->GetTransform().getOrigin();
	CVector3 dimensions = static_cast<CBoxShape*>(m_Info->m_Second->GetCollisionShape().get())->GetDimensions();
	CVector3 vertices[8];
	vertices[0] = CVector3(position.getX() - dimensions.getX(), position.getY() - dimensions.getY(), position.getZ() - dimensions.getZ());
	vertices[1] = CVector3(position.getX() - dimensions.getX(), position.getY() - dimensions.getY(), position.getZ() + dimensions.getZ());
	vertices[2] = CVector3(position.getX() - dimensions.getX(), position.getY() + dimensions.getY(), position.getZ() + dimensions.getZ());
	vertices[3] = CVector3(position.getX() - dimensions.getX(), position.getY() + dimensions.getY(), position.getZ() - dimensions.getZ());
	vertices[4] = CVector3(position.getX() + dimensions.getX(), position.getY() + dimensions.getY(), position.getZ() + dimensions.getZ());
	vertices[5] = CVector3(position.getX() + dimensions.getX(), position.getY() + dimensions.getY(), position.getZ() - dimensions.getZ());
	vertices[6] = CVector3(position.getX() + dimensions.getX(), position.getY() - dimensions.getY(), position.getZ() + dimensions.getZ());
	vertices[7] = CVector3(position.getX() + dimensions.getX(), position.getY() - dimensions.getY(), position.getZ() - dimensions.getZ());
	float dots[8];

	for (int i = 0; i < 8; i++)
	{
		dots[i] = local.Dot(vertices[i]);
	}
	CScalar max = *std::min_element(dots, dots + 7);
	for (int i = 0; i < 8; i++)
	{
		CScalar base = max - dots[i];
		if (base < static_cast<CScalar>(0.001) && base > -static_cast<CScalar>(0.001))
		{
			m_IncidentFace.vertices.push_back(vertices[i]);
		}
	}
	m_IncidentFace.isValid = true;
	m_IncidentFace.normal = m_Info->m_Normal * -1;
}

void Cinkes::CBoxBoxCollision::FindSidePlanes()
{
	CVector3 top = static_cast<CBoxShape*>(m_Info->m_First->GetCollisionShape().get())->GetDimensions() * m_LocalNormal;
	top.Normalize();
	CVector3 ref[4] = { m_ReferenceFace.vertices[0],m_ReferenceFace.vertices[1],m_ReferenceFace.vertices[2],m_ReferenceFace.vertices[3] };
	std::vector<CPlane> sides;
	CScalar lengthSqrd = (static_cast<CBoxShape*>(m_Info->m_First->GetCollisionShape().get())->GetDimensions() * m_LocalNormal).Length2();
	if ((ref[0] - ref[1]).Length2() == lengthSqrd) {
		sides.push_back(CPlane());
		sides[sides.size() - 1].point = CVector3((ref[0][0] + ref[1][0]) / 2, (ref[0][1] + ref[1][1]) / 2, (ref[0][2] + ref[1][2]) / 2);
		sides[sides.size() - 1].normal = sides[sides.size() - 1].point - top;
		sides[sides.size() - 1].normal.Normalize();
	}
	if ((ref[0] - ref[3]).Length2() == lengthSqrd) {
		sides.push_back(CPlane());
		sides[sides.size() - 1].point = CVector3((ref[0][0] + ref[3][0]) / 2, (ref[0][1] + ref[3][1]) / 2, (ref[0][2] + ref[3][2]) / 2);
		sides[sides.size() - 1].normal = sides[sides.size() - 1].point - top;
		sides[sides.size() - 1].normal.Normalize();
	}
	if ((ref[1] - ref[2]).Length2() == lengthSqrd) {
		sides.push_back(CPlane());
		sides[sides.size() - 1].point = CVector3((ref[1][0] + ref[2][0]) / 2, (ref[1][1] + ref[2][1]) / 2, (ref[1][2] + ref[2][2]) / 2);
		sides[sides.size() - 1].normal = sides[sides.size() - 1].point - top;
		sides[sides.size() - 1].normal.Normalize();
	}
	if ((ref[2] - ref[3]).Length2() == lengthSqrd) {
		sides.push_back(CPlane());
		sides[sides.size() - 1].point = CVector3((ref[2][0] + ref[3][0]) / 2, (ref[2][1] + ref[3][1]) / 2, (ref[2][2] + ref[3][2]) / 2);
		sides[sides.size() - 1].normal = sides[sides.size() - 1].point - top;
		sides[sides.size() - 1].normal.Normalize();
	}
	if ((ref[0] - ref[2]).Length2() == lengthSqrd) {
		sides.push_back(CPlane());
		sides[sides.size() - 1].point = CVector3((ref[0][0] + ref[2][0]) / 2, (ref[0][1] + ref[2][1]) / 2, (ref[0][2] + ref[2][2]) / 2);
		sides[sides.size() - 1].normal = sides[sides.size() - 1].point - top;
		sides[sides.size() - 1].normal.Normalize();
	}
	if ((ref[1] - ref[3]).Length2() == lengthSqrd) {
		sides.push_back(CPlane());
		sides[sides.size() - 1].point = CVector3((ref[1][0] + ref[3][0]) / 2, (ref[1][1] + ref[3][1]) / 2, (ref[1][2] + ref[3][2]) / 2);
		sides[sides.size() - 1].normal = sides[sides.size() - 1].point - top;
		sides[sides.size() - 1].normal.Normalize();
	}
}

void Cinkes::CBoxBoxCollision::Clip()
{
	CScalar D1, D2 = 0;
	for (unsigned int c = 0; c < m_Planes.size(); c++) {
		for (unsigned int i = 0; i < m_IncidentFace.vertices.size() - 1; i++) {
			D1 = m_Planes[c].DistanceToPoint(m_IncidentFace.vertices[i]);
			D2 = m_Planes[c].DistanceToPoint(m_IncidentFace.vertices[i + 1]);
			if ((D1 <= 0) && (D2 <= 0))
			{
				m_Points.push_back(m_IncidentFace.vertices[i + 1]);
			}
			else if ((D1 > 0) && ((D2 > -CEPSILON) && (D2 < CEPSILON)))
			{
				m_Points.push_back(m_IncidentFace.vertices[i + 1]);
			}
			else if (((D1 > -CEPSILON) && (D1 < CEPSILON)) && (D2 > 0))
			{
				continue;
			}
			else if ((D1 <= 0) && (D2 > 0))
			{
				m_Points.push_back(m_Planes[c].Intersection(m_IncidentFace.vertices[i],
					m_IncidentFace.vertices[i + 1]));
			}
			else if ((D1 > 0) && (D2 <= 0))
			{
				m_Points.push_back(m_Planes[c].Intersection(m_IncidentFace.vertices[i],
					m_IncidentFace.vertices[i + 1]));
				m_Points.push_back(m_IncidentFace.vertices[i + 1]);
			}
		}
	}
}
