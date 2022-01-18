#include "CTriangleShape.h"

#include <memory>

inline int circ_next(int i) { return (i + 1) % 3; }
inline int circ_prev(int i) { return (i + 2) % 3; }

Cinkes::CTriangle* Cinkes::CTriangleStorage::newTriangle(const CVector3* a_Vertices, int a_A, int a_B, int a_C)
{
	CTriangle* newTriangle = nullptr;
	if (m_Free != 100)
	{
		newTriangle = &m_Triangles[m_Free++];
		new (newTriangle) CTriangle(a_A, a_B, a_C);
		if (!newTriangle->ComputeClosest(a_Vertices))
		{
			--m_Free;
			newTriangle = nullptr;
		}
	}

	return newTriangle;
}

bool Cinkes::CEdge::silhouette(const CVector3* a_Vertices, unsigned a_Index, CTriangleStorage& a_Storage) const
{
	if (!m_Triangle->isObsolete())
	{
		if (!m_Triangle->isVisibleFrom(a_Vertices, a_Index))
		{
			CTriangle* triangle = a_Storage.newTriangle(a_Vertices, a_Index, getTarget(), getSource());

			if (triangle)
			{
				Half_Link(CEdge(triangle, 1), *this);
				return true;
			}

			return false;
		}
		else
		{
			m_Triangle->setObsolete(true); // Triangle is visible 

			int backup = a_Storage.getFree();

			if (!m_Triangle->getAdjascentEdge(circ_next(m_Index)).silhouette(a_Vertices, a_Index, a_Storage))
			{
				m_Triangle->setObsolete(false);

				CTriangle* triangle = a_Storage.newTriangle(a_Vertices, a_Index, getTarget(), getSource());

				if (triangle)
				{
					Half_Link(CEdge(triangle, 1), *this);
					return true;
				}

				return false;
			}
			else if (!m_Triangle->getAdjascentEdge(circ_prev(m_Index)).silhouette(a_Vertices, a_Index, a_Storage))
			{
				m_Triangle->setObsolete(false);

				a_Storage.setFree(backup);

				CTriangle* triangle = a_Storage.newTriangle(a_Vertices, a_Index, getTarget(), getSource());

				if (triangle)
				{
					Half_Link(CEdge(triangle, 1), *this);
					return true;
				}

				return false;
			}
		}
	}

	return true;
}

unsigned Cinkes::CEdge::getSource() const
{
	return (*m_Triangle)[m_Index];
}

unsigned Cinkes::CEdge::getTarget() const
{
	return (*m_Triangle)[circ_next(m_Index)];
}

bool Cinkes::Link(const CEdge& a_Edge1, const CEdge& a_Edge2)
{
	bool ok = a_Edge1.getSource() == a_Edge2.getTarget() && a_Edge1.getTarget() == a_Edge2.getSource();
	if (ok)
	{
		a_Edge1.getTriangle()->getAdjascentEdge(a_Edge1.getIndex())= a_Edge2;
		a_Edge2.getTriangle()->getAdjascentEdge(a_Edge2.getIndex()) = a_Edge1;
	}
	return ok;
}

void Cinkes::Half_Link(const CEdge& a_Edge1, const CEdge& a_Edge2)
{
	a_Edge1.getTriangle()->getAdjascentEdge(a_Edge1.getIndex()) = a_Edge2;
}

bool Cinkes::CTriangle::ComputeClosest(const CVector3* verts)
{
	const CVector3& p0 = verts[m_Indices[0]];

	CVector3 v1 = verts[m_Indices[1]] - p0;
	CVector3 v2 = verts[m_Indices[2]] - p0;
	CScalar v1dv1 = v1.Length2();
	CScalar v1dv2 = v1.Dot(v2);
	CScalar v2dv2 = v2.Length2();
	CScalar p0dv1 = p0.Dot(v1);
	CScalar p0dv2 = p0.Dot(v2);

	m_Determinant = v1dv1 * v2dv2 - v1dv2 * v1dv2; // non-negative
	m_Lambda1 = p0dv2 * v1dv2 - p0dv1 * v2dv2;
	m_Lambda2 = p0dv1 * v1dv2 - p0dv2 * v1dv1;

	if (m_Determinant > static_cast<CScalar>(0.0))
	{
		m_Closest = p0 + (v1  * m_Lambda1 + v2 * m_Lambda2) / m_Determinant;
		m_DistanceSqrd = m_Closest.Length2();

		return true;
	}

	return false;
}

bool Cinkes::CTriangle::isClosestInternal() const
{
	return m_Lambda1 >= CScalar(0.0) &&
		m_Lambda2 >= CScalar(0.0) &&
		m_Lambda1 + m_Lambda2 <= m_Determinant;
}

bool Cinkes::CTriangle::isVisibleFrom(const CVector3* a_Vertices, unsigned a_Index) const
{
	CVector3 lever = a_Vertices[a_Index] - m_Closest;
	return m_Closest.Dot(lever) > static_cast<CScalar>(0.0);
}

Cinkes::CVector3 Cinkes::CTriangle::getClosestPoint(const CVector3* a_Points) const
{
	const CVector3& p0 = a_Points[m_Indices[0]];

	return p0 + ( (a_Points[m_Indices[1]] - p0) * m_Lambda1 +
					(a_Points[m_Indices[2]] - p0) * m_Lambda2 ) / m_Determinant;
}

bool Cinkes::CTriangle::silhouette(const CVector3* a_Vertices, unsigned a_Index, CTriangleStorage& a_TriangleStorage)
{
	int first = a_TriangleStorage.getFree();

	setObsolete(true);

	bool result = m_AdjascentEdges[0].silhouette(a_Vertices, a_Index, a_TriangleStorage) &&
		m_AdjascentEdges[1].silhouette(a_Vertices, a_Index, a_TriangleStorage) &&
		m_AdjascentEdges[2].silhouette(a_Vertices, a_Index, a_TriangleStorage);

	if (result)
	{
		int i, j;
		for (i = first, j = a_TriangleStorage.getFree() - 1; i != a_TriangleStorage.getFree(); j = i++)
		{
			CTriangle* triangle = &a_TriangleStorage[i];
			Half_Link(triangle->getAdjascentEdge(1), CEdge(triangle, 1));
			if (!Link(CEdge(triangle, 0), CEdge(&a_TriangleStorage[j], 2)))
			{
				return false;
			}
		}
	}

	return result;
}
