#include "CForceGeneratorRegistry.h"

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
    //if (m_ForceGenerators.size() <= a_Index) { return false; }

    //for (auto& element : m_CollisionWorld->GetAllRigidBodies())
    //{
    //    element->RemoveGeneratorByValue(m_ForceGenerators[a_Index].get());
    //}

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
