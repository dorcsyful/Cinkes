#include "CBody.h"


Cinkes::CBody& Cinkes::CBody::operator=(CBody&& a_Rhs) noexcept
{
	return *this;
}

Cinkes::CBody& Cinkes::CBody::operator=(const CBody& a_Rhs)
{
	return *this;
}

bool Cinkes::CBody::AddGenerator(CForceGenerator* a_Generator)
{
	if(std::find(m_ForceGenerators.begin(),m_ForceGenerators.end(),a_Generator) != m_ForceGenerators.end())
	{
		m_ForceGenerators.push_back(a_Generator);
		return true;
	}
	return false;
}

void Cinkes::CBody::AddForce(const CVector3& a_ForceToAdd)
{
	m_Force += a_ForceToAdd;
}

unsigned Cinkes::CBody::HasForceGenerator(EGENERATOR_TYPE a_Type)
{
	for (int i = 0; i < static_cast<int>(m_ForceGenerators.size()); ++i)
	{
		if (m_ForceGenerators[i]->GetType() == a_Type) { return i; }
	}
    return -1;
}

unsigned Cinkes::CBody::HasForceGenerator(CForceGenerator* a_Generator)
{
	auto i = std::find(m_ForceGenerators.begin(), m_ForceGenerators.end(), a_Generator);
	if(i != m_ForceGenerators.end()) 
	{
		return static_cast<unsigned>(std::distance(m_ForceGenerators.begin(), i));
	}
	return -1;
}

bool Cinkes::CBody::RemoveGeneratorByIndex(unsigned a_Index)
{
	if(a_Index < m_ForceGenerators.size())
	{
		m_ForceGenerators.erase(std::find(m_ForceGenerators.begin(), m_ForceGenerators.end(), m_ForceGenerators[a_Index]));
		return true;
	}
	return false;
}

bool Cinkes::CBody::RemoveGeneratorByType(EGENERATOR_TYPE a_Type)
{
	for (int i = static_cast<int>(m_ForceGenerators.size()) - 1; i >= 0; --i)
	{
		if(m_ForceGenerators[i]->GetType() == a_Type)
		{
			m_ForceGenerators.erase(std::find(m_ForceGenerators.begin(), m_ForceGenerators.end(), m_ForceGenerators[i]));
			return true;
		}
	}
	return false;
}

bool Cinkes::CBody::RemoveGeneratorByValue(CForceGenerator* a_Generator)
{
	if(m_ForceGenerators.erase(std::find(m_ForceGenerators.begin(), m_ForceGenerators.end(), a_Generator)) != m_ForceGenerators.end())
	{
		return true;
	}
	return false;
}
