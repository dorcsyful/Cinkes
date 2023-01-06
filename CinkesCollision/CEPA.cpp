#include "CEPA.h"

#include <functional>

#include "CCollisionObject.h"
#include "CCollisionShape.h"
#include "CInternalContactInfo.h"
#include "../CinkesMath/CUtils.h"
#include "CSimplex.h"
#include "CConvexHull.h"


bool IsConvex(std::vector<Cinkes::CVector3>& points, std::vector<size_t>& triangles, float threshold = 0.001)
{
using namespace Cinkes;
	for (unsigned long i = 0; i < triangles.size() / 3; i++)
	{
		Cinkes::CVector3 Atmp = points[triangles[i * 3 + 0]];
		Cinkes::CVector3 Btmp = points[triangles[i * 3 + 1]];
		Cinkes::CVector3 Ctmp = points[triangles[i * 3 + 2]];

		Cinkes::CVector3 A(Atmp[0], Atmp[1], Atmp[2]);
		Cinkes::CVector3 B(Btmp[0], Btmp[1], Btmp[2]);
		Cinkes::CVector3 C(Ctmp[0], Ctmp[1], Ctmp[2]);
		B -= A;
		C -= A;

		Cinkes::CVector3 BCNorm = B.Cross(C);
		BCNorm.Normalize();

		float checkPoint = Cinkes::CVector3(points[0][0] - A[0], points[0][1] - A[1], points[0][2] - A[2]).Dot(BCNorm);

		for (unsigned long j = 0; j < points.size(); j++)
		{
			float dist = Cinkes::CVector3(points[j][0] - A[0], points[j][1] - A[1], points[j][2] - A[2]).Dot(BCNorm);

			if ((std::abs(checkPoint) > threshold) && (std::abs(dist) > threshold) && (checkPoint * dist < 0))
			{
				return false;
			}
		}
	}

	return true;
}


void Cinkes::CEPA::Run(CInternalContactInfo* a_Contact, CSimplex& a_Simplex)
{

	Algorithm(a_Contact, a_Simplex);
}

void Cinkes::CEPA::Algorithm(CInternalContactInfo* a_Contact, const CSimplex& a_Simplex)
{
	//support function data
	CCollisionObject* obj1 = a_Contact->m_First.get();
	CCollisionShape* obj1_shape = obj1->GetCollisionShape().get();
	CMat3x3 obj1_rotation = obj1->GetTransform().getBasis();
	CVector3 obj1_location = obj1->GetTransform().getOrigin();

	CCollisionObject* obj2 = a_Contact->m_Second.get();
	CCollisionShape* obj2_shape = obj2->GetCollisionShape().get();
	CMat3x3 obj2_rotation = obj2->GetTransform().getBasis();
	CVector3 obj2_location = obj2->GetTransform().getOrigin();


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
	size_t min_face = temp.second;

	CVector3 min_normal;
	CScalar min_distance = std::numeric_limits<CScalar>::max();

	while(min_distance == std::numeric_limits<CScalar>::max())  // NOLINT(clang-diagnostic-float-equal)
	{
		min_normal = normals[min_face].m_Normal;
		min_distance = normals[min_face].m_Distance;

		CVector3 A = obj1_rotation * obj1_shape->Support(obj1_rotation.Transpose() * min_normal) + obj1_location;
		CVector3 B = obj2_rotation * obj2_shape->Support(obj2_rotation.Transpose() * (min_normal * -1)) + obj2_location;
		CVector3 support = A - B;
		CScalar distance = min_normal.Dot(support);

		if(CUtils::Abs(distance - min_distance) > static_cast<CScalar>(0.001))
		{
			min_distance = std::numeric_limits<CScalar>::max();

			std::vector<std::pair<size_t, size_t>> unique;

			for(size_t i = 0; i < normals.size(); i++)
			{
				float dot = normals[i].m_Normal.Dot(support);
				if(dot > 0)
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
			std::vector<size_t> new_faces;
			for (const auto& i : unique)
			{
				new_faces.push_back(i.first);
				new_faces.push_back(i.second);
				new_faces.push_back(polytope.size());  // NOLINT(clang-diagnostic-shorten-64-to-32)
			}
			polytope.push_back(support);

			std::pair<std::vector<Cinkes::CFaceData>, size_t> new_stuff = GetFaceNormals(polytope, new_faces);

			CScalar old_min_distance = std::numeric_limits<CScalar>::max();
			for (unsigned i = 0; i < normals.size(); i++) {
				if (normals[i].m_Distance < old_min_distance) {
					old_min_distance = normals[i].m_Distance;
					min_face = i;
				}
			}

			if (new_stuff.first[new_stuff.second].m_Distance < old_min_distance) {
				min_face = new_stuff.second + normals.size();  // NOLINT(clang-diagnostic-shorten-64-to-32)
			}

			faces.insert(faces.end(), new_faces.begin(), new_faces.end());
			normals.insert(normals.end(), new_stuff.first.begin(), new_stuff.first.end());
		}
	}
	
	a_Contact->m_Normal = min_normal;
	if (IsConvex(polytope, faces)) {
	a_Contact->m_PenetrationDepth = min_distance + 0.001f;
	a_Contact->m_Simplex = a_Simplex;
	}

}

std::pair<std::vector<Cinkes::CFaceData>, size_t> Cinkes::CEPA::GetFaceNormals(const std::vector<CVector3>& a_Polytope, const std::vector<size_t>& a_Faces)
{
	std::vector<CFaceData> normals;
	unsigned int min_triangle = 0;
	CScalar min_distance = std::numeric_limits<CScalar>::max();

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

		if(distance < min_distance)
		{
			min_triangle = i / 3;
			min_distance = distance;
		}
	}

	return std::pair<std::vector<CFaceData>, size_t>(normals,min_triangle);
}

void Cinkes::CEPA::AddUniqueEdge(std::vector<std::pair<size_t, size_t>>& a_Edges, const std::vector<size_t>& a_Faces, size_t a_A, size_t a_B)
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
