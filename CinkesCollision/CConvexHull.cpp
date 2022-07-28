#include "pch.h"
#include "CConvexHull.h"

#include <map>
#include <algorithm>

#include "../CinkesMath/CTransform.h"


Cinkes::CConvexHull::~CConvexHull()
{
	for (int i = static_cast<int>(m_Vertices.size()) - 1; i >= 0; i--)
	{
		m_Vertices[i] = nullptr;
	}
}

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

void Cinkes::CConvexHull::BuildHull(const std::vector<float>& a_Vertices, const std::vector<unsigned int>& a_Indices, 
									const std::vector<int>& a_Triangles)
{

}
