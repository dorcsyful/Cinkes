#include "CEPA.h"

#include <corecrt_math_defines.h>
#include <functional>

#include "CCollisionObject.h"
#include "CCollisionShape.h"
#include "CContactInfo.h"
#include "../CinkesMath/CUtils.h"
#include "CSimplex.h"

void Cinkes::CEPA::Run(std::shared_ptr<CContactInfo> a_Contact, CSimplex& a_Simplex)
{
	while(a_Simplex.Size() < 4)
	{
		BlowUp(a_Simplex, a_Contact);
	}
	Algorithm(a_Contact, a_Simplex);
}

void Cinkes::CEPA::Algorithm(std::shared_ptr<CContactInfo> a_Contact, const CSimplex& a_Simplex)
{
	//the tetrahedron from GJK, the faces contain every triangle that are on it by the vertex indices
	std::vector<CVector3> polytope = { a_Simplex[0],a_Simplex[1],a_Simplex[2],a_Simplex[3] };
	std::vector<unsigned> faces{
		0,1,2,
		0,3,1,
		0,2,3,
		1,3,2
	};

	std::pair<std::vector<CFaceData>, unsigned> temp = GetFaceNormals(polytope, faces);

	std::vector<CFaceData>& normals = temp.first;
	unsigned minFace = temp.second;

	CVector3 minNormal;
	CScalar minDistance = std::numeric_limits<CScalar>::max();

	while(minDistance == std::numeric_limits<CScalar>::max())  // NOLINT(clang-diagnostic-float-equal)
	{
		minNormal = normals[minFace].m_Normal;
		minDistance = normals[minFace].m_Distance;

		CVector3 support = a_Contact->m_First->GetCollisionShape()->Support(minNormal, a_Contact->m_First->GetTransform()) -
				a_Contact->m_Second->GetCollisionShape()->Support(minNormal * (-1), a_Contact->m_Second->GetTransform());

		CScalar distance = minNormal.Dot(support);

		if(CUtils::Abs(distance - minDistance) > static_cast<CScalar>(0.001))
		{
			minDistance = std::numeric_limits<CScalar>::max();

			std::vector<std::pair<unsigned, unsigned>> unique;

			for(unsigned i = 0; i < normals.size(); i++)
			{
				if(normals[i].m_Normal.Dot(support) > 0)
				{
					unsigned face = i * 3;

					AddUniqueEdge(unique, faces, face, face + 1);
					AddUniqueEdge(unique, faces, face + 1, face + 2);
					AddUniqueEdge(unique, faces, face + 2, face);

					faces[face + 2] = faces.back(); faces.pop_back();
					faces[face + 1] = faces.back(); faces.pop_back();
					faces[face] = faces.back(); faces.pop_back();

					normals[i] = normals.back(); normals.pop_back();

					i--;
				}
			}
			std::vector<unsigned> newFaces;
			for (const auto& i : unique)
			{
				newFaces.push_back(i.first);
				newFaces.push_back(i.second);
				newFaces.push_back(polytope.size());  // NOLINT(clang-diagnostic-shorten-64-to-32)
			}

			polytope.push_back(support);

			std::pair<std::vector<Cinkes::CFaceData>, unsigned> newStuff = GetFaceNormals(polytope, newFaces);

			CScalar oldMinDistance = std::numeric_limits<CScalar>::max();
			for (unsigned i = 0; i < normals.size(); i++) {
				if (normals[i].m_Distance < oldMinDistance) {
					oldMinDistance = normals[i].m_Distance;
					minFace = i;
				}
			}

			if (newStuff.first[newStuff.second].m_Distance < oldMinDistance) {
				minFace = newStuff.second + normals.size();  // NOLINT(clang-diagnostic-shorten-64-to-32)
			}

			faces.insert(faces.end(), newFaces.begin(), newFaces.end());
			normals.insert(normals.end(), newStuff.first.begin(), newStuff.first.end());
		}
	}

	a_Contact->m_Normal = minNormal;
	a_Contact->m_PenetrationDepth = minDistance + 0.001f;
}

void Cinkes::CEPA::BlowUp(CSimplex& a_Simplex, const std::shared_ptr<CContactInfo>& a_Contact)
{
	CVector3 d = a_Simplex[1] - a_Simplex[0];
	CVector3 axis = SmallestAxis(d);
	CVector3 vector;

	const CScalar epsilon = 0.00001f;
	const CScalar epsilon2 = epsilon * epsilon;

	if(a_Simplex.Size() == 1)
	{
		return;
	}

	if(a_Simplex.Size() == 2)
	{
		a_Simplex.Push_Front(CVector3());
		vector = d.Cross(axis);
		CMat3x3 rotation = CMat3x3(d, static_cast<CScalar>(M_PI * 0.3));

		for(unsigned i = 0; i < 6; i++)
		{
			a_Simplex[a_Simplex.Size() - 1] = (CSOSupport(a_Contact.get(), vector));    // NOLINT(bugprone-narrowing-conversions, cppcoreguidelines-narrowing-conversions)
			if (a_Simplex[2].Length2() > epsilon2) { break; }
			vector = rotation * vector;
		}
	}

	if(a_Simplex.Size() == 3)
	{
		a_Simplex.Push_Front(CVector3());
		CVector3 v1 = a_Simplex[1] - a_Simplex[0];
		CVector3 v2 = a_Simplex[2] - a_Simplex[0];
		vector = v1.Cross(v2);
		a_Simplex[a_Simplex.Size() - 1] = CSOSupport(a_Contact.get(), vector);  // NOLINT(bugprone-narrowing-conversions, cppcoreguidelines-narrowing-conversions)

		if(a_Simplex[3].Length2() < epsilon2)
		{
			vector *= -1;
			CSOSupport(a_Contact.get(), vector);
		}
	}
}

Cinkes::CVector3 Cinkes::CEPA::CSOSupport(const CContactInfo* a_Contact, const CVector3& a_Dir)
{
	CVector3 dir = a_Dir;
	dir.Normalize();
	CVector3 localA = a_Contact->m_First->GetTransform().getBasis().GetInverse() * dir;
	CVector3 localB = a_Contact->m_Second->GetTransform().getBasis().GetInverse() * dir;

	CVector3 supportA = a_Contact->m_First->GetCollisionShape()->Support(localA, CTransform());
	CVector3 supportB = a_Contact->m_Second->GetCollisionShape()->Support(localB, CTransform());

	supportA = a_Contact->m_First->GetTransform().getBasis() * supportA + a_Contact->m_First->GetTransform().getOrigin();
	supportB = a_Contact->m_Second->GetTransform().getBasis() * supportB + a_Contact->m_Second->GetTransform().getOrigin();
	return supportA - supportB;
}

Cinkes::CVector3 Cinkes::CEPA::SmallestAxis(const CVector3& a_Vector3)
{
	CVector3 axis;

	if (CUtils::Abs(a_Vector3[0]) <= CUtils::Abs(a_Vector3[1]) && CUtils::Abs(a_Vector3[0]) <= CUtils::Abs(a_Vector3[2]))
	{
		axis = CVector3(1, 0, 0);
	}
	else if (CUtils::Abs(a_Vector3[1]) <= CUtils::Abs(a_Vector3[0]) && CUtils::Abs(a_Vector3[1]) <= CUtils::Abs(a_Vector3[2]))
	{
		axis = CVector3(0, 1, 0);
	}
	else if (CUtils::Abs(a_Vector3[2]) <= CUtils::Abs(a_Vector3[0]) && CUtils::Abs(a_Vector3[2]) <= CUtils::Abs(a_Vector3[1]))
	{
		axis = CVector3(0, 0, 1);
	}
	else
	{
		axis = CVector3(1, 1, 1);
	}

	return axis;
}

std::pair<std::vector<Cinkes::CFaceData>, unsigned> Cinkes::CEPA::GetFaceNormals(const std::vector<CVector3>& a_Polytope, const std::vector<unsigned>& a_Faces)
{
	std::vector<CFaceData> normals;
	unsigned int minTriangle = 0;
	CScalar minDistance = std::numeric_limits<CScalar>::max();

	for(unsigned i = 0; i < a_Faces.size(); i += 3)
	{
		CVector3 a = a_Polytope[a_Faces[i]];
		CVector3 b = a_Polytope[a_Faces[1 + i]];
		CVector3 c = a_Polytope[a_Faces[2 + i]];

		CVector3 normal = CVector3( (b - a).Cross(c - a) );
		normal.Normalize();
		CScalar distance = normal.Dot(a);
		if(distance < 0)
		{
			normal *= -1;
			distance *= -1;
		}
		normals.emplace_back(CFaceData(normal, distance));

		if(distance < minDistance)
		{
			minTriangle = i / 3;
			minDistance = distance;
		}
	}

	return std::pair<std::vector<CFaceData>, CScalar>(normals,minTriangle);
}

void Cinkes::CEPA::AddUniqueEdge(std::vector<std::pair<unsigned, unsigned>>& a_Edges, const std::vector<unsigned>& a_Faces, unsigned a_A, unsigned a_B)
{
	//Actual return value: std::vector<std::pair<unsigned, unsigned>>::iterator
	auto reverse = std::find(a_Edges.begin(), a_Edges.end(),
		std::make_pair(a_Faces[a_B], a_Faces[a_A]));
	if(reverse != a_Edges.end())
	{
		a_Edges.erase(reverse);
	}
	else
	{
		a_Edges.emplace_back(a_Faces[a_A], a_Faces[a_B]);
	}
}
