#include "pch.h"
#include "CConvexHull.h"

#include <map>
#include <algorithm>
Cinkes::CConvexHull::~CConvexHull()
{
	for (int i = static_cast<int>(m_Vertices.size()) - 1; i >= 0; i--)
	{
		delete m_Vertices[i];
		m_Vertices[i] = nullptr;
	}
}

void Cinkes::CConvexHull::BuildHull(const std::vector<float>& a_Vertices, const std::vector<unsigned int>& a_Indices, 
									const std::vector<int>& a_Triangles)
{
	std::map<unsigned int, CVertex*> indexed;
	unsigned int counter = 0;
	while(counter < a_Vertices.size() - 1)
	{
		CVector3 temp = CVector3(a_Vertices[counter], a_Vertices[counter + 1], a_Vertices[counter + 2]);
		m_Vertices.push_back(new CVertex());
		m_Vertices[m_Vertices.size() - 1]->m_Position = temp;
		m_Vertices[m_Vertices.size() - 1]->m_Index = a_Indices[counter];
		indexed.insert({ a_Indices[counter],m_Vertices[m_Vertices.size() - 1] });
		counter += 3;
	}

	for(unsigned int i = 0; i < a_Triangles.size(); i += 3)
	{
		if (std::find(indexed[a_Triangles[i]]->m_Adjacent.begin(), indexed[a_Triangles[i]]->m_Adjacent.end(), i + 1) == indexed[a_Triangles[i]]->m_Adjacent.end())
		{
			indexed[a_Triangles[i]]->m_Adjacent.push_back(i + 1);
		}
		if (std::find(indexed[a_Triangles[i]]->m_Adjacent.begin(), indexed[a_Triangles[i]]->m_Adjacent.end(), i + 2) == indexed[a_Triangles[i]]->m_Adjacent.end())
		{
			indexed[a_Triangles[i]]->m_Adjacent.push_back(i + 2);
		}
	}
}
