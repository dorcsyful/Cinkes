#include "pch.h"
#include "CCollisionWorld.h"
#include "CCollisionObject.h"
Cinkes::CCollisionWorld::~CCollisionWorld()
{

}

Cinkes::CCollisionWorld::CCollisionWorld(const CCollisionWorld& a_Rhs)
{
	for(auto object : a_Rhs.m_Objects)
	{
		m_Objects.push_back(object);
	}
}

Cinkes::CCollisionWorld::CCollisionWorld(CCollisionWorld&& a_Rhs) noexcept
{
		for (auto object : a_Rhs.m_Objects)
		{
			m_Objects.push_back(object);
		}
}

Cinkes::CCollisionWorld& Cinkes::CCollisionWorld::operator=(CCollisionWorld&& a_Rhs) noexcept
{
	for (auto object : a_Rhs.m_Objects)
	{
		m_Objects.push_back(object);
	}
	return *this;
}

Cinkes::CCollisionWorld& Cinkes::CCollisionWorld::operator=(const CCollisionWorld& a_Rhs)
{
	for (auto object : a_Rhs.m_Objects)
	{
		m_Objects.push_back(object);
	}
	return *this;
}

bool Cinkes::CCollisionWorld::AddObject(const std::shared_ptr<CCollisionObject>& a_Object)
{

	auto size = m_Objects.size();
	m_Objects.push_back(a_Object);
	if(size == m_Objects.size() - 1)
	{
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
}
