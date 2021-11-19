#include "pch.h"
#include "CCollisionWorld.h"
#include "CCollisionObject.h"
#include "CBVH.h"
#include "CGJKAlgorithm.h"
Cinkes::CCollisionWorld::CCollisionWorld()
{
	m_BVH = std::make_unique<CBVH>(m_Objects);
	m_GJK = std::make_unique<CGJKAlgorithm>();
	m_ShouldUpdate = false;
}
Cinkes::CCollisionWorld::CCollisionWorld(const CCollisionWorld& a_Rhs)
{
	m_ShouldUpdate = true;
	for(const auto& object : a_Rhs.m_Objects)
	{
		m_Objects.push_back(object);
	}
	m_BVH = std::make_unique<CBVH>(m_Objects);
	m_GJK = std::make_unique<CGJKAlgorithm>();

}

Cinkes::CCollisionWorld::CCollisionWorld(CCollisionWorld&& a_Rhs) noexcept
{
	m_ShouldUpdate = true;
	for (const auto& object : a_Rhs.m_Objects)
	{
		m_Objects.push_back(object);
	}
	m_BVH = std::make_unique<CBVH>(m_Objects);
	m_GJK = std::make_unique<CGJKAlgorithm>();

}

Cinkes::CCollisionWorld& Cinkes::CCollisionWorld::operator=(CCollisionWorld&& a_Rhs) noexcept
{
	if (this == &a_Rhs) { return *this; }
	m_Objects.reserve(a_Rhs.m_Objects.capacity());
	for (const auto& object : a_Rhs.m_Objects)
	{
		m_Objects.push_back(object);
	}
	m_BVH = std::make_unique<CBVH>(m_Objects);
	m_GJK = std::make_unique<CGJKAlgorithm>();

	return *this;
}

Cinkes::CCollisionWorld& Cinkes::CCollisionWorld::operator=(const CCollisionWorld& a_Rhs)
{
	for (const auto& object : a_Rhs.m_Objects)
	{
		m_Objects.push_back(object);
	}
	m_BVH = std::make_unique<CBVH>(m_Objects);
	m_GJK = std::make_unique<CGJKAlgorithm>();

	return *this;
}

bool Cinkes::CCollisionWorld::AddObject(const std::shared_ptr<CCollisionObject>& a_Object)
{

	auto size = m_Objects.size();
	m_Objects.push_back(a_Object);
	if(size == m_Objects.size() - 1)
	{
		//TODO: find a better way to update objects inside the BVH class
		m_BVH->m_AABBs.push_back(m_BVH->CreateAABB(a_Object));
		return true;
	}

	return false;
}

bool Cinkes::CCollisionWorld::RemoveObject(const std::shared_ptr<CCollisionObject>& a_Object)
{
	auto removed = std::remove(m_Objects.begin(), m_Objects.end(), a_Object);

	if (removed == m_Objects.end())
	{
		return true;
	}
	return false;
}

bool Cinkes::CCollisionWorld::RemoveObjectByIndex(int a_Index)
{
	auto size = m_Objects.size();
	m_Objects.erase(m_Objects.begin() + a_Index);
	if(size -1 ==m_Objects.size())
	{
		return true;
	}
	return false;
}

void Cinkes::CCollisionWorld::RunCollision(CScalar a_T)
{
	m_BVH->Update();
	for (auto& element : m_BVH->m_Contacts)
	{
		if(!(m_GJK->Algorithm(element->m_First.get(), element->m_Second.get())))
		{
			element->m_PassedNarrowphase = false;
		}
		else { element->m_PassedNarrowphase = true; }
	}
}
