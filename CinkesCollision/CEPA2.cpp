#include "CEPA.h"

#include <algorithm>
#include <corecrt_math_defines.h>
#include <functional>
#include <iostream>

#include "CCollisionObject.h"
#include "CCollisionShape.h"
#include "CContactInfo.h"
#include "../CinkesMath/CUtils.h"
#include "CSimplex.h"
#include "CTriangleShape.h"
#include "../CinkesMath/CQuaternion.h"
#include "../CinkesMath/CMat3x3.h"



void Cinkes::CEPA::Run(std::shared_ptr<CContactInfo> a_Contact, CSimplex& a_Simplex)
{
	for(int i = 0; i < a_Simplex.Size(); i++)
	{
		m_PBuf[i] = a_Simplex.getALocal(i);
		m_QBuf[i] = a_Simplex.getBLocal(i);
		m_YBuf[i] = a_Simplex.getWorld(i);
	}

	Algorithm(a_Contact, a_Simplex);
}

bool Cinkes::CEPA::Algorithm(std::shared_ptr<CContactInfo> a_Contact, const CSimplex& a_Simplex)
{

	unsigned short numVertices = a_Simplex.Size();
	num_triangles = 0;
	m_triangleStore.clear();
	switch (numVertices)  // NOLINT(hicpp-multiway-paths-covered)
	{
	case 1:
		// Impossible but still good to be here
		a_Contact->m_ContactPoints.clear();
		return false;
	case 2:
	{
		// We have a line segment

		CVector3 dir = m_YBuf[1] - m_YBuf[0];

		dir.Normalize();


		static const CScalar sin_60 = sqrt(CScalar(3.0)) * CScalar(0.5);

		CQuaternion rot(dir[0] * sin_60, dir[1] * sin_60, dir[2] * sin_60, CScalar(0.5));
		CMat3x3 rot_mat = CMat3x3(rot.GetAxis(),rot.GetAngle());

		CVector3 aux1 = dir.Cross(SmallestAxis(dir));
		CVector3 aux2 = rot_mat * aux1;
		CVector3 aux3 = rot_mat * aux2;

		m_PBuf[2] = a_Contact->m_First->GetCollisionShape()->Support(aux1, a_Contact->m_First->GetTransform());
		m_QBuf[2] = a_Contact->m_Second->GetCollisionShape()->Support(aux1 * -1, a_Contact->m_Second->GetTransform());
		m_YBuf[2] = m_PBuf[2] - m_QBuf[2];

		m_PBuf[3] = a_Contact->m_First->GetCollisionShape()->Support(aux2, a_Contact->m_First->GetTransform());
		m_QBuf[3] = a_Contact->m_Second->GetCollisionShape()->Support(aux2 * -1, a_Contact->m_Second->GetTransform());
		m_YBuf[3] = m_PBuf[3] - m_QBuf[3];

		m_PBuf[4] = a_Contact->m_First->GetCollisionShape()->Support(aux3, a_Contact->m_First->GetTransform());
		m_QBuf[4] = a_Contact->m_Second->GetCollisionShape()->Support(aux3 * -1, a_Contact->m_Second->GetTransform());
		m_YBuf[4] = m_PBuf[4] - m_QBuf[4];

		if (OriginInTetrahedron(m_YBuf[0], m_YBuf[2], m_YBuf[3], m_YBuf[4]) == 0)
		{
			m_PBuf[1] = m_PBuf[4];
			m_QBuf[1] = m_QBuf[4];
			m_YBuf[1] = m_YBuf[4];
		}
		else if (OriginInTetrahedron(m_YBuf[1], m_YBuf[2], m_YBuf[3], m_YBuf[4]) == 0)
		{
			m_PBuf[0] = m_PBuf[4];
			m_QBuf[0] = m_QBuf[4];
			m_YBuf[0] = m_YBuf[4];
		}
		else
		{
			// Origin not in initial polytope
			return false;
		}

		numVertices = 4;
	}
	case 4:  // NOLINT(clang-diagnostic-implicit-fallthrough)
	{
		int bad_vertex = OriginInTetrahedron(m_YBuf[0], m_YBuf[1], m_YBuf[2], m_YBuf[3]);

		if (bad_vertex == 0)
		{
			CTriangle* f0 = m_triangleStore.newTriangle(m_YBuf, 0, 1, 2);
			CTriangle* f1 = m_triangleStore.newTriangle(m_YBuf, 0, 3, 1);
			CTriangle* f2 = m_triangleStore.newTriangle(m_YBuf, 0, 2, 3);
			CTriangle* f3 = m_triangleStore.newTriangle(m_YBuf, 1, 3, 2);

			if (!(f0 && f0->getDist2() > static_cast<CScalar>(0.0) &&
				f1 && f1->getDist2() > static_cast<CScalar>(0.0) &&
				f2 && f2->getDist2() > static_cast<CScalar>(0.0) &&
				f3 && f3->getDist2() > static_cast<CScalar>(0.0)))
			{
				return false;
			}

			Link(CEdge(f0, 0), CEdge(f1, 2));
			Link(CEdge(f0, 1), CEdge(f3, 2));
			Link(CEdge(f0, 2), CEdge(f2, 0));
			Link(CEdge(f1, 0), CEdge(f2, 2));
			Link(CEdge(f1, 1), CEdge(f3, 0));
			Link(CEdge(f2, 1), CEdge(f3, 1));

			AddCandidate(f0, INFINITY);
			AddCandidate(f1, INFINITY);
			AddCandidate(f2, INFINITY);
			AddCandidate(f3, INFINITY);
			break;
		}

		if (bad_vertex < 4)
		{
			m_PBuf[bad_vertex - 1] = m_PBuf[4];
			m_QBuf[bad_vertex - 1] = m_QBuf[4];
			m_YBuf[bad_vertex - 1] = m_YBuf[4];

		}

		numVertices = 3;

	}
	case 3:  // NOLINT(clang-diagnostic-implicit-fallthrough)
	{
		// We have a triangle inside the Minkowski sum containing
		// the origin. First blow it up.

		CVector3 v1 = m_YBuf[1] - m_YBuf[0];
		CVector3 v2 = m_YBuf[2] - m_YBuf[0];
		CVector3 vv = v1.Cross(v2);

		m_PBuf[3] = a_Contact->m_First->GetCollisionShape()->Support(vv, a_Contact->m_First->GetTransform());
		m_QBuf[3] = a_Contact->m_Second->GetCollisionShape()->Support(vv * -1, a_Contact->m_Second->GetTransform());
		m_YBuf[3] = m_PBuf[3] - m_QBuf[3];
		m_PBuf[4] = a_Contact->m_First->GetCollisionShape()->Support(vv * -1, a_Contact->m_First->GetTransform());
		m_QBuf[4] = a_Contact->m_Second->GetCollisionShape()->Support(vv, a_Contact->m_Second->GetTransform());
		m_YBuf[4] = m_PBuf[4] - m_QBuf[4];

		CTriangle* f0 = m_triangleStore.newTriangle(m_YBuf, 0, 1, 3);
		CTriangle* f1 = m_triangleStore.newTriangle(m_YBuf, 1, 2, 3);
		CTriangle* f2 = m_triangleStore.newTriangle(m_YBuf, 2, 0, 3);
		CTriangle* f3 = m_triangleStore.newTriangle(m_YBuf, 0, 2, 4);
		CTriangle* f4 = m_triangleStore.newTriangle(m_YBuf, 2, 1, 4);
		CTriangle* f5 = m_triangleStore.newTriangle(m_YBuf, 1, 0, 4);

		if (!(f0 && f0->getDist2() > static_cast<CScalar>(0.0) &&
			f1 && f1->getDist2() > static_cast<CScalar>(0.0) &&
			f2 && f2->getDist2() > static_cast<CScalar>(0.0) &&
			f3 && f3->getDist2() > static_cast<CScalar>(0.0) &&
			f4 && f4->getDist2() > static_cast<CScalar>(0.0) &&
			f5 && f5->getDist2() > static_cast<CScalar>(0.0)))
		{
			return false;
		}

		Link(CEdge(f0, 1), CEdge(f1, 2));
		Link(CEdge(f1, 1), CEdge(f2, 2));
		Link(CEdge(f2, 1), CEdge(f0, 2));

		Link(CEdge(f0, 0), CEdge(f5, 0));
		Link(CEdge(f1, 0), CEdge(f4, 0));
		Link(CEdge(f2, 0), CEdge(f3, 0));

		Link(CEdge(f3, 1), CEdge(f4, 2));
		Link(CEdge(f4, 1), CEdge(f5, 2));
		Link(CEdge(f5, 1), CEdge(f3, 2));

		AddCandidate(f0, INFINITY);
		AddCandidate(f1, INFINITY);
		AddCandidate(f2, INFINITY);
		AddCandidate(f3, INFINITY);
		AddCandidate(f4, INFINITY);
		AddCandidate(f5, INFINITY);

		numVertices = 5;
	}
	break;
	default: ;
	}


	if (num_triangles == 0)
	{
		return false;
	}

	// at least one triangle on the heap.	

	CTriangle* triangle = nullptr;

	CScalar upper_bound2 = INFINITY;

	do
	{
		triangle = triangleHeap[0];
		std::pop_heap(&triangleHeap[0], &triangleHeap[num_triangles], m_TriangleComp);
		--num_triangles;

		if (!triangle->isObsolete())
		{
			if (numVertices == MaxSupportPoints)
			{
				break;
			}

			m_PBuf[numVertices] = a_Contact->m_First->GetCollisionShape()->Support(triangle->getClosest(), a_Contact->m_First->GetTransform());
			m_QBuf[numVertices] = a_Contact->m_Second->GetCollisionShape()->Support(triangle->getClosest() * -1, a_Contact->m_Second->GetTransform());
			m_YBuf[numVertices] = m_PBuf[numVertices] - m_QBuf[numVertices];

			int index = numVertices++;
			CScalar far_dist = m_YBuf[index].Dot(triangle->getClosest());

			CScalar far_dist2 = far_dist * far_dist / triangle->getDist2();
			upper_bound2 = std::min(upper_bound2, far_dist2);

			CScalar error = far_dist - triangle->getDist2();
			if (error <= std::max( FLT_EPSILON * 4 * far_dist2, FLT_EPSILON * 4)
				|| m_YBuf[index] == m_YBuf[(*triangle)[0]]
				|| m_YBuf[index] == m_YBuf[(*triangle)[1]]
				|| m_YBuf[index] == m_YBuf[(*triangle)[2]]
				)
			{
				break;
			}

			// Compute the silhouette cast by the new vertex
			// Note that the new vertex is on the positive side
			// of the current triangle, so the current triangle will
			// not be in the convex hull. Start local search
			// from this triangle.

			int i = m_triangleStore.getFree();

			if (!triangle->silhouette(m_YBuf, index, m_triangleStore))
			{
				break;
			}

			while (i != m_triangleStore.getFree())
			{
				CTriangle* newTriangle = &m_triangleStore[i];
				//assert(triangle->getDist2() <= newTriangle->getDist2());

				AddCandidate(newTriangle, upper_bound2);

				++i;
			}
		}
	} while (num_triangles > 0 && triangleHeap[0]->getDist2() <= upper_bound2);


	CVector3 v = triangle->getClosest();
	std::cout << "Collision point? " << v[0] << " " << v[1] << " " << v[2] << std::endl;

	std::cout << "Length? " << v.Length() << std::endl;
	CVector3 pa = triangle->getClosestPoint(m_PBuf);
	CVector3 pb = triangle->getClosestPoint(m_QBuf);
	std::cout << "Collision point? " << pa[0] << " " << pa[1] << " " << pa[2] << std::endl;
	std::cout << "Collision point? " << pb[0] << " " << pb[1] << " " << pb[2] << std::endl;
	return true;
}

void Cinkes::CEPA::BlowUp(CSimplex& a_Simplex, const std::shared_ptr<CContactInfo>& a_Contact)
{
	CVector3 d = a_Simplex.getWorld(1) - a_Simplex.getWorld(0);
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
		a_Simplex.Push_FrontWorld(CVector3());
		vector = d.Cross(axis);
		CMat3x3 rotation = CMat3x3(d, static_cast<CScalar>(M_PI * 0.3));

		for(unsigned i = 0; i < 6; i++)
		{
			a_Simplex.getWorld(a_Simplex.Size() - 1) = (CSOSupport(a_Contact.get(), vector));    // NOLINT(bugprone-narrowing-conversions, cppcoreguidelines-narrowing-conversions)
			if (a_Simplex.getWorld(2).Length2() > epsilon2) { break; }
			vector = rotation * vector;
		}
	}

	if(a_Simplex.Size() == 3)
	{
		a_Simplex.Push_FrontWorld(CVector3());
		CVector3 v1 = a_Simplex.getWorld(1) - a_Simplex.getWorld(0);
		CVector3 v2 = a_Simplex.getWorld(2) - a_Simplex.getWorld(0);
		vector = v1.Cross(v2);
		a_Simplex.getWorld(a_Simplex.Size() - 1) = CSOSupport(a_Contact.get(), vector);  // NOLINT(bugprone-narrowing-conversions, cppcoreguidelines-narrowing-conversions)

		if(a_Simplex.getWorld(3).Length2() < epsilon2)
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

inline void Cinkes::CEPA::AddCandidate(CTriangle* a_Triangle, CScalar a_Upper2) const
{
	if (a_Triangle->isClosestInternal() && a_Triangle->getDist2() <= a_Upper2)
	{
		triangleHeap[num_triangles++] = a_Triangle;
		std::push_heap(&triangleHeap[0], &triangleHeap[num_triangles], m_TriangleComp);
	}
}

int Cinkes::CEPA::OriginInTetrahedron(const CVector3& a_P0, const CVector3& a_P1, const CVector3& a_P2, const CVector3& a_P3)
{
	CVector3 normal0 = (a_P1 - a_P0).Cross(a_P2 - a_P0);
	if ((normal0.Dot(a_P0) > CScalar(0.0)) == (normal0.Dot(a_P3) > CScalar(0.0)))
	{
		return 4;
	}

	CVector3 normal1 = (a_P3 - a_P1).Cross(a_P2 - a_P1);
	if ((normal1.Dot(a_P1) > CScalar(0.0)) == (normal1.Dot(a_P0) > CScalar(0.0)))
	{
		return 1;
	}

	CVector3 normal2 = (a_P3 - a_P2).Cross( a_P0 - a_P2);
	if (normal2.Dot(a_P2) > CScalar(0.0) == normal2.Dot(a_P1) > CScalar(0.0))
	{
		return 2;
	}

	CVector3 normal3 = (a_P1 - a_P3).Cross(a_P0 - a_P3);
	if (normal3.Dot(a_P3) > CScalar(0.0) == (normal3.Dot(a_P2) > CScalar(0.0)))
	{
		return 3;
	}

	return 0;
}

void Cinkes::CEPA::GetBaryCentric(const CVector3& a_Point, const CVector3& a_TriangleX, const CVector3& a_TriangleY, const CVector3& a_TriangleZ, CVector3& a_Out_Barycentric)
{
	CVector3 v0 = a_TriangleY - a_TriangleX;
	CVector3 v1 = a_TriangleZ - a_TriangleX;
	CVector3 v2 = a_Point - a_TriangleX;

	CScalar d00 = v0.Dot(v0);
	CScalar d01 = v0.Dot(v1);
	CScalar d11 = v1.Dot(v1);
	CScalar d20 = v2.Dot(v0);
	CScalar d21 = v2.Dot(v1);

	CScalar denom = d00 * d11 - d01 * d01;
	a_Out_Barycentric[0] = (d11 * d20 - d01 * d21) / denom;
	a_Out_Barycentric[1] = (d00 * d21 - d01 * d20) / denom;
	a_Out_Barycentric[2] = 1.0f - a_Out_Barycentric[0] - a_Out_Barycentric[1];
}

void Cinkes::CEPA::ProjectToTriangle(CVector3& a_Out_Point, const CVector3& a_TriangleX, const CVector3& a_TriangleY, const CVector3& a_TriangleZ)
{
	// u=P2−P1
	CVector3 u = a_TriangleY - a_TriangleX;
	// v=P3−P1
	CVector3 v = a_TriangleZ - a_TriangleX;
	// n=u×v
	CVector3 n = u.Cross(v);
	// w=P−P1
	CVector3 w = CVector3(0,0,0) - a_TriangleX;
	// Barycentric coordinates of the projection P′of P onto T:
	// γ=[(u×w)⋅n]/n²
	float gamma = u.Cross(w).Dot(n) / n.Dot(n);
	// β=[(w×v)⋅n]/n²
	float beta = w.Cross(v).Dot(n) / n.Dot(n);
	float alpha = 1 - gamma - beta;
	// The point P′ lies inside T if:
	a_Out_Point = CVector3(a_TriangleX * alpha + a_TriangleY * beta + a_TriangleZ * gamma);
}	
