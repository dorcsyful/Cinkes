#include "pch.h"
#include "CConvexHull.h"

#include <map>
#include <algorithm>


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
	unsigned int counter = 0;
	while(counter < a_Vertices.size() - 1)
	{
		CVector3 temp = CVector3(a_Vertices[counter], a_Vertices[counter + 1], a_Vertices[counter + 2]);
		m_Vertices.insert({ a_Indices[counter],std::make_shared<CVertex>() });
		m_Vertices[a_Indices[counter]]->m_Position = temp;
		m_Vertices[a_Indices[counter]]->m_Index = a_Indices[counter];
		counter += 3;
	}

	for(unsigned int i = 0; i < a_Triangles.size(); i += 3)
	{
		if (std::find(m_Vertices[a_Triangles[i]]->m_Adjacent.begin(), m_Vertices[a_Triangles[i]]->m_Adjacent.end(), i + 1) == m_Vertices[a_Triangles[i]]->m_Adjacent.end())
		{
			m_Vertices[a_Triangles[i]]->m_Adjacent.push_back(i + 1);
		}
		if (std::find(m_Vertices[a_Triangles[i]]->m_Adjacent.begin(), m_Vertices[a_Triangles[i]]->m_Adjacent.end(), i + 2) == m_Vertices[a_Triangles[i]]->m_Adjacent.end())
		{
			m_Vertices[a_Triangles[i]]->m_Adjacent.push_back(i + 2);
		}
	}
}

Cinkes::CVector3 Cinkes::CConvexHull::Support(const CVector3& a_V)
{
	CVertex* base = m_Vertices[0].get();
	bool best = false;
	while(!best)
	{
		best = true;
		for(auto current : base->m_Adjacent)
		{
			if(m_Vertices[current]->m_Position.Dot(a_V) > base->m_Position.Dot(a_V))
			{
				best = false;
				base = m_Vertices[current].get();
			}
		}
	}

	return base->m_Position;
}
