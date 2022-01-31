#include "CForceGenerator.h"

bool Cinkes::CForceGenerator::AddObject(void* a_Object)
{
    if (std::find(m_Objects.begin(), m_Objects.end(), a_Object) == m_Objects.end())
    {
        m_Objects.push_back(a_Object);
        return true;
    }
    return false;
}

bool Cinkes::CForceGenerator::RemoveObjectByValue(const void* a_Object)
{
    auto it = std::find(m_Objects.begin(), m_Objects.end(), a_Object);
    if(it != m_Objects.end())
    {
        m_Objects.erase(it);
        return true;
    }
    return false;
}

bool Cinkes::CForceGenerator::IsInGenerator(const void* a_Object)
{
    if(std::find(m_Objects.begin(), m_Objects.end(), a_Object) != m_Objects.end())
    {
        return true;
    }
    return false;
}
