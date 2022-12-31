#include "CEPA.h"

#include <corecrt_math_defines.h>
#include <functional>

#include "CCollisionObject.h"
#include "CCollisionShape.h"
#include "CInternalContactInfo.h"
#include "../CinkesMath/CUtils.h"
#include "CSimplex.h"

void Cinkes::CEPA::Run(CInternalContactInfo* a_Contact, CSimplex& a_Simplex)
{

	Algorithm(a_Contact, a_Simplex);
}

void Cinkes::CEPA::Algorithm(CInternalContactInfo* a_Contact, const CSimplex& a_Simplex)
{
	//the tetrahedron from GJK, the faces contain every triangle that are on it by the vertex indices
	std::vector<CVector3> polytope = { a_Simplex[0],a_Simplex[1],a_Simplex[2],a_Simplex[3] };
	std::vector<size_t> faces{
		0,1,2,
		0,3,1,
		0,2,3,
		1,3,2
	};

	std::pair<std::vector<CFaceData>, size_t> temp = GetFaceNormals(polytope, faces);

	std::vector<CFaceData>& normals = temp.first;
	size_t minFace = temp.second;

	CVector3 minNormal;
	CScalar minDistance = std::numeric_limits<CScalar>::max();

	while(minDistance == std::numeric_limits<CScalar>::max())  // NOLINT(clang-diagnostic-float-equal)
	{
		minNormal = normals[minFace].m_Normal;
		minDistance = normals[minFace].m_Distance;

		CVector3 A = a_Contact->m_First->GetTransform().getBasis() * 
			(a_Contact->m_First->GetCollisionShape()->Support(a_Contact->m_First->GetTransform().getBasis().Transpose() * minNormal))
			 + a_Contact->m_First->GetTransform().getOrigin();
		CVector3 B = a_Contact->m_Second->GetTransform().getBasis() * 
			(a_Contact->m_Second->GetCollisionShape()->Support(a_Contact->m_Second->GetTransform().getBasis().Transpose() * 
				(minNormal * (-1)))) + a_Contact->m_Second->GetTransform().getOrigin();
		CVector3 support = A - B;
		CScalar distance = minNormal.Dot(support);

		if(CUtils::Abs(distance - minDistance) > static_cast<CScalar>(0.001))
		{
			minDistance = std::numeric_limits<CScalar>::max();

			std::vector<std::pair<size_t, size_t>> unique;

			for(size_t i = 0; i < normals.size(); i++)
			{
				if(normals[i].m_Normal.Dot(support) > 0)
				{
					size_t face = i * 3;

					AddUniqueEdge(unique, faces, face, face + static_cast<size_t>(1));
					AddUniqueEdge(unique, faces, face + static_cast<size_t>(1), face + static_cast<size_t>(2));
					AddUniqueEdge(unique, faces, face + static_cast<size_t>(2), face);

					faces[face + 2] = faces.back(); faces.pop_back();
					faces[face + 1] = faces.back(); faces.pop_back();
					faces[face] = faces.back(); faces.pop_back();

					normals[i] = normals.back(); normals.pop_back();

					i--;
				}
			}
			std::vector<size_t> newFaces;
			for (const auto& i : unique)
			{
				newFaces.push_back(i.first);
				newFaces.push_back(i.second);
				newFaces.push_back(polytope.size());  // NOLINT(clang-diagnostic-shorten-64-to-32)
			}
			polytope.push_back(support);

			std::pair<std::vector<Cinkes::CFaceData>, size_t> newStuff = GetFaceNormals(polytope, newFaces);

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
	int index = minFace * 3;
	a_Contact->m_Normal = minNormal;

	a_Contact->m_PenetrationDepth = minDistance + 0.001f;
	a_Contact->m_Simplex = a_Simplex;
}

std::pair<std::vector<Cinkes::CFaceData>, size_t> Cinkes::CEPA::GetFaceNormals(const std::vector<CVector3>& a_Polytope, const std::vector<size_t>& a_Faces)
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

	return std::pair<std::vector<CFaceData>, size_t>(normals,minTriangle);
}

void Cinkes::CEPA::AddUniqueEdge(std::vector<std::pair<size_t, size_t>>& a_Edges, const std::vector<size_t>& a_Faces, size_t a_A, size_t a_B)
{
	//Actual return value: std::vector<std::pair<unsigned, unsigned>>::iterator
	auto reverse = std::find(a_Edges.begin(), a_Edges.end(),
		std::make_pair(a_Faces[a_B], a_Faces[a_A]));
	auto duplicate = std::find(a_Edges.begin(), a_Edges.end(),
		std::make_pair(a_Faces[a_A], a_Faces[a_B]));
	if(reverse != a_Edges.end())
	{
		a_Edges.erase(reverse);
	}
	else if (duplicate != a_Edges.end())
	{
		a_Edges.erase(duplicate);
	}
	else
	{
		a_Edges.emplace_back(a_Faces[a_A], a_Faces[a_B]);
	}
}
