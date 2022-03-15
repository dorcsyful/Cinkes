#include "CForceGeneratorRegistry.h"
#include "CPhysicsWorld.h"
#include "CRigidBody.h"
bool Cinkes::CForceGeneratorRegistry::AddForceGenerator(const std::shared_ptr<CForceGenerator>& a_Generator, bool a_AddToAll)
{
	for (const auto& element : m_ForceGenerators)
	{
        if (element->GetType() == a_Generator->GetType()) { return false; }
	}
    m_ForceGenerators.push_back(a_Generator);
    return true;
}

bool Cinkes::CForceGeneratorRegistry::RemoveGeneratorByIndex(unsigned a_Index)
{
    if (m_ForceGenerators.size() <= a_Index) { return false; }

	m_ForceGenerators.erase(std::find(m_ForceGenerators.begin(),m_ForceGenerators.end(),m_ForceGenerators[a_Index]));

    return true;
}

bool Cinkes::CForceGeneratorRegistry::RemoveByType(EGENERATOR_TYPE a_Type)
{
    return false;
}

bool Cinkes::CForceGeneratorRegistry::RemoveByValue(CForceGenerator* a_Generator)
{
    return false;
}

Cinkes::CForceGenerator* Cinkes::CForceGeneratorRegistry::GetGeneratorByType(EGENERATOR_TYPE a_Type)
{
    CForceGenerator* returnValue = nullptr;
    for (const auto& element : m_ForceGenerators)
    {
	    if(element->GetType() == a_Type)
	    {
            returnValue = element.get();
            break;
	    }
    }
    return returnValue;
}

std::vector<std::shared_ptr<Cinkes::CForceGenerator>> Cinkes::CForceGeneratorRegistry::GetGeneratorsThatContain(const CRigidBody* a_RigidBody)
{
    std::vector<std::shared_ptr<CForceGenerator>> generators;
	for (const auto& element : m_ForceGenerators)
	{
		if(element->IsInGenerator(a_RigidBody))
		{
            generators.push_back(element);
		}
	}
    return generators;
}

void Cinkes::CForceGeneratorRegistry::UpdateGenerators()
{
	for (const auto& element : m_ForceGenerators)
	{
		for (auto object : element->m_Objects)
		{
            element->UpdateForce(object);
		}
	}
}