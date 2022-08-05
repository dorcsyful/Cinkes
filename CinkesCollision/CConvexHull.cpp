#include "CConvexHull.h"
#include "CVector3.h"
#include <cassert>
Cinkes::CConvexHull::CConvexHull(const CConvexHull& a_Rhs)
{
	m_Vertices = a_Rhs.m_Vertices;
}

Cinkes::CConvexHull::CConvexHull(CConvexHull&& a_Rhs) noexcept
{
	m_Vertices = a_Rhs.m_Vertices;
}

Cinkes::CConvexHull& Cinkes::CConvexHull::operator=(CConvexHull&& a_Rhs)
{
	m_Vertices = a_Rhs.m_Vertices;
	return *this;
}

Cinkes::CConvexHull& Cinkes::CConvexHull::operator=(const CConvexHull& a_Rhs)
{
	m_Vertices = a_Rhs.m_Vertices;
	return *this;
}

Cinkes::CVector3 Cinkes::CConvexHull::Support(const CVector3& a_V)
{
	int index = -1;
	CScalar largest = -INFINITY;
	for (int i = 0; i < m_Vertices.size(); i++) {
		CScalar temp = a_V.Dot(m_Vertices[i].coords);
		if (temp > largest) {
			largest = temp;
			index = i;
		}
	}
	assert(index != -1, "Index is wrong in support point calculation");
	return m_Vertices[index].coords;
}
